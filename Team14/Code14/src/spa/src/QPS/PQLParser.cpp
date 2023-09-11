
#include <string>
#include <stdexcept>

#include "PQLParser.h"
#include "Tokenizer.h"
#include "SuchThatClause.h"


PQLParser::PQLParser(const std::string& str) : tokenizer(std::make_shared<Tokenizer>(str)){}

Query PQLParser::parse(){
    Query query = Query();
    processDeclarations(query);
    processSelectClause(query);
    processSuchThatClause(query);

    expect(tokenizer->peekToken()->isToken(TokenType::Empty), "Invalid query syntax");
    return query;
}

void PQLParser::processDeclarations(Query& query) {
    while(tokenizer->peekToken()->isDesignEntity()) {
        std::shared_ptr<Token> designEntity = tokenizer->popToken();
        QueryEntityType currentType;
        if (designEntity->isToken("procedure")) {
            currentType = QueryEntityType::Procedure;
        } else if (designEntity->isToken("stmt")) {
            currentType = QueryEntityType::Stmt;
        } else if (designEntity->isToken("read")) {
            currentType = QueryEntityType::Read;
        } else if (designEntity->isToken("print")) {
            currentType = QueryEntityType::Print;
        } else if (designEntity->isToken("assign")) {
            currentType = QueryEntityType::Assign;
        } else if (designEntity->isToken("call")) {
            currentType = QueryEntityType::Call;
        } else if (designEntity->isToken("while")) {
            currentType = QueryEntityType::While;
        } else if (designEntity->isToken("if")) {
            currentType = QueryEntityType::If;
        } else if (designEntity->isToken("variable")) {
            currentType = QueryEntityType::Variable;
        } else if (designEntity->isToken("constant")) {
            currentType = QueryEntityType::Constant;
        }

        std::shared_ptr<Token> synonym = tokenizer->popToken();
        if (!synonym->isIdent()) {
            if (synonym->isToken(TokenType::Empty)) {
                throw std::runtime_error("Expected synonym but found none");
            }
            throw std::runtime_error("Invalid synonym '" + synonym->getRep() + "'");
        }
        std::shared_ptr<QueryEntity> newEntity = std::make_shared<QueryEntity>(currentType, synonym->getRep());
        query.addDeclaration(newEntity);

        while(tokenizer->peekToken()->isToken(TokenType::Comma)) {
            tokenizer->popToken(); //consume comma
            synonym = tokenizer->popToken();
            if (!synonym->isIdent()) {
                if (synonym->isToken(TokenType::Empty)) {
                    throw std::runtime_error("Expected synonym but found none");
                }
                throw std::runtime_error("Invalid synonym '" + synonym->getRep() + "'");
            }
            newEntity = std::make_shared<QueryEntity>(currentType, synonym->getRep());
            query.addDeclaration(newEntity);
        }

        // consume semicolon
        std::shared_ptr<Token> endToken = tokenizer->popToken();
        if (!endToken->isToken(TokenType::Semicolon)) {
            throw std::runtime_error("Expected ; but found '" + endToken->getRep() + + "'");
        }
    }

    // if no design entity return err
    if (!query.hasDeclarations()) {
        throw std::runtime_error("Expected a declaration but found none");
    }
}

void PQLParser::processSelectClause(Query& query) {
    std::shared_ptr<Token> next = tokenizer->popToken();
    if (!next->isToken("Select")) {
        throw std::runtime_error("Expected Select clause but found '" + next->getRep() + "'");
    }
    next = tokenizer->popToken();

    if (next->isToken(TokenType::Empty)) {
        throw std::runtime_error("Expected synonym but found none");
    }

    std::shared_ptr<QueryEntity> entity = query.getEntity(next->getRep());
    if (!entity) {
        throw std::runtime_error("Undeclared synonym in Select clause");
    }
    query.addSelect(entity);

    // TODO support for multiple synonyms
}

void PQLParser::processSuchThatClause(Query& query) {
    // handle optional
    std::shared_ptr<Token> suchThatToken = tokenizer->peekToken();
    try {
        expect(suchThatToken->isToken("such that"), "No such that");
    } catch (...) {
        return;
    }

    std::shared_ptr<Token> absToken = tokenizer->popToken();

    SuchThatClause clause;
    if (absToken->isToken("Uses")) {
        clause.setType(ClauseType::Uses);
    } else if (absToken->isToken("Follows")) {
        clause.setType(ClauseType::Follows);
    } else if (absToken->isToken("Follows*")){
        clause.setType(ClauseType::FollowsStar);
    } else {
        throw std::runtime_error("Invalid token, abstraction expected");
    }

    processSuchThatBody(query, clause);
    validateSuchThatSemantics(query, clause);
    query.addSuchThat(clause);

    // TODO: handle multiple "such that" and here recursively
}

void PQLParser::validateSuchThatSemantics(Query& query, SuchThatClause& clause) {
    // TODO: check Uses (done) & modifies cannot be wildcard
    // TODO: check each entity is appropriate for the RelationshipType

    ClauseType type = clause.getType();
    Ref leftRef = clause.getFirstParam();
    RootType leftRootType = leftRef.getRootType();
    Ref rightRef = clause.getSecondParam();
    RootType rightRootType = rightRef.getRootType();

    // check wildcard & entity type
    if (type == ClauseType::Uses) {
        if (leftRootType == RootType::Wildcard) {
            throw std::runtime_error("Invalid Uses LHS, wildcard found");
        }

        if (leftRootType == RootType::Synonym) {
            std::shared_ptr<QueryEntity> entity = query.getEntity(leftRef.getRep());
            QueryEntityType entityType = entity->getType();
            if (entityType != QueryEntityType::Stmt && entityType != QueryEntityType::Assign
                && entityType != QueryEntityType::Print && entityType != QueryEntityType::If
                && entityType != QueryEntityType::While && entityType != QueryEntityType::Procedure
                && entityType != QueryEntityType::Call) {
                throw std::runtime_error("Invalid Uses LHS, invalid entity type found");
            }
        }

        if (rightRootType == RootType::Synonym) {
            std::shared_ptr<QueryEntity> entity = query.getEntity(rightRef.getRep());
            QueryEntityType entityType = entity->getType();
            if (entityType != QueryEntityType::Variable) {
                throw std::runtime_error("Invalid Uses RHS, non-variable found");
            }
        }

    } else if (type == ClauseType::Follows) {
        if (leftRootType == RootType::Synonym) {
            std::shared_ptr<QueryEntity> entity = query.getEntity(leftRef.getRep());
            QueryEntityType entityType = entity->getType();
            if (!isOfStmtType(entityType)) {
                throw std::runtime_error("Invalid Follows LHS, non-statement found");
            }
        }

        if (rightRootType == RootType::Synonym) {
            std::shared_ptr<QueryEntity> entity = query.getEntity(rightRef.getRep());
            QueryEntityType entityType = entity->getType();
            if (!isOfStmtType(entityType)) {
                throw std::runtime_error("Invalid Follows RHS, non-statement found");
            }
        }

    } else if (type == ClauseType::FollowsStar) {
        if (leftRootType == RootType::Synonym) {
            std::shared_ptr<QueryEntity> entity = query.getEntity(leftRef.getRep());
            QueryEntityType entityType = entity->getType();
            if (!isOfStmtType(entityType)) {
                throw std::runtime_error("Invalid Follows* LHS, non-statement found");
            }
        }

        if (rightRootType == RootType::Synonym) {
            std::shared_ptr<QueryEntity> entity = query.getEntity(leftRef.getRep());
            QueryEntityType entityType = entity->getType();
            if (!isOfStmtType(entityType)) {
                throw std::runtime_error("Invalid Follows* RHS, non-statement found");
            }
        }
    }
}

bool PQLParser::isOfStmtType(QueryEntityType entityType) {
    return entityType == QueryEntityType::Stmt || entityType == QueryEntityType::Assign
           || entityType == QueryEntityType::Print || entityType == QueryEntityType::If
           || entityType == QueryEntityType::While || entityType == QueryEntityType::Call
           || entityType == QueryEntityType::Read;
}

void PQLParser::processSuchThatBody(Query& query, SuchThatClause& clause) {
    expect(tokenizer->peekToken()->isToken(TokenType::Lparenthesis), "No left parenthesis");
    processSuchThatLeft(query, clause);
    expect(tokenizer->peekToken()->isToken(TokenType::Comma), "No comma");
    processSuchThatRight(query, clause);
    expect(tokenizer->peekToken()->isToken(TokenType::Rparenthesis), "No right parenthesis");
}

void PQLParser::processSuchThatLeft(Query &query, SuchThatClause &clause) {
    // TODO: handle more relationships
    ClauseType type = clause.getType();
    Ref ref;

    // validate if synonyms

    if (type == ClauseType::Uses) {
        std::shared_ptr<Token> next = tokenizer->peekToken();
        if (next->isIdent()) {
            std::shared_ptr<QueryEntity> entity = query.getEntity(next->getRep());
            if (!entity) {
                throw std::runtime_error("Invalid Uses LHS, undeclared synonym found");
            }

            if (entity->getType() == QueryEntityType::Procedure) {
                ref = extractEntRef(query);
            } else {
                ref = extractStmtRef(query);
            }

        } else {
            try {
                ref = extractStmtRef(query);
            } catch (...) {
                ref = extractEntRef(query);
            }
        }
    } else if (type == ClauseType::Follows) {
        ref = extractStmtRef(query);
    } else if (type == ClauseType::FollowsStar) {
        ref = extractStmtRef(query);
    } else {
        throw std::runtime_error("Invalid Relationship Type in left such that clause");
    }

    clause.setFirstParam(ref);
}

void PQLParser::processSuchThatRight(Query &query, SuchThatClause &clause) {
    ClauseType type = clause.getType();
    Ref ref;
    if (type == ClauseType::Uses) {
        ref = extractEntRef(query);
    } else if (type == ClauseType::Follows) {
        ref = extractStmtRef(query);
    } else if (type == ClauseType::FollowsStar) {
        ref = extractStmtRef(query);
    } else {
        throw std::runtime_error("Invalid Relationship Type in left such that clause");
    }

    clause.setSecondParam(ref);
}

Ref PQLParser::extractStmtRef(Query& query) {
    Ref ref;
    RefType type = RefType::StmtRef;
    ref.setType(type);
    RootType rootType;

    std::string refString;
    std::shared_ptr<Token> curr = tokenizer->peekToken();
    if (curr->isInteger()) { // INTEGER
        refString = tokenizer->popToken()->getRep();
        rootType = RootType::Integer;
    } else if (curr->isToken(TokenType::Underscore)) { // WILDCARD
        refString = tokenizer->popToken()->getRep();
        rootType = RootType::Wildcard;
    } else if (curr->isToken(TokenType::Word) && curr->isIdent()) { // SYNONYM
        refString = tokenizer->popToken()->getRep();
        rootType = RootType::Synonym;

        // check that synonyms are declared
        std::shared_ptr<QueryEntity> entity = query.getEntity(refString);
        if (!entity) {
            throw std::runtime_error("Undeclared synonym found");
        }
        QueryEntityType entityType = entity->getType();
        ref.setEntityType(entityType);

    } else {
        throw std::runtime_error("Invalid stmtRef");
    }

    ref.setRep(refString);
    ref.setRootType(rootType);
    return ref;
}

Ref PQLParser::extractEntRef(Query& query) {
    Ref ref;
    RefType type = RefType::EntRef;
    ref.setType(type);
    RootType rootType;

    std::string refString;
    std::shared_ptr<Token> curr = tokenizer->peekToken();
    if (curr->isToken(TokenType::Quote)) { // IDENTITY
        tokenizer->popToken();
        std::shared_ptr<Token> syn = tokenizer->peekToken();
        expect(syn->isIdent(), "Identity invalid");
        std::string right_quote = tokenizer->peekToken()->getRep();
        expect(tokenizer->peekToken()->isToken(TokenType::Quote), "No right quote");

        refString = "\"" + syn->getRep() + "\"";
        rootType = RootType::Ident;
    } else if (curr->isToken(TokenType::Underscore)) { // WILDCARD
        refString = tokenizer->popToken()->getRep();
        rootType = RootType::Wildcard;
    } else if (curr->isToken(TokenType::Word) && curr->isIdent()) { // SYNONYM
        refString = tokenizer->popToken()->getRep();
        rootType = RootType::Synonym;

        // check that synonyms are declared
        std::shared_ptr<QueryEntity> entity = query.getEntity(refString);
        if (!entity) {
            throw std::runtime_error("Undeclared synonym found");
        }
        QueryEntityType entityType = entity->getType();
        ref.setEntityType(entityType);
    } else {
        throw std::runtime_error("Invalid entRef");
    }

    ref.setRep(refString);
    ref.setRootType(rootType);
    return ref;
}

std::shared_ptr<Token> PQLParser::expect(bool isToken, const std::string& errorMsg) {
    if (!isToken) {
        throw std::runtime_error(errorMsg);
    }
    return tokenizer->popToken();
}
