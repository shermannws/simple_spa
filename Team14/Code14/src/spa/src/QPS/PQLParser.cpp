
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
        EntityType currentType;
        if (designEntity->isToken("procedure")) {
            currentType = EntityType::Procedure;
        } else if (designEntity->isToken("stmt")) {
            currentType = EntityType::Stmt;
        } else if (designEntity->isToken("read")) {
            currentType = EntityType::Read;
        } else if (designEntity->isToken("print")) {
            currentType = EntityType::Print;
        } else if (designEntity->isToken("assign")) {
            currentType = EntityType::Assign;
        } else if (designEntity->isToken("call")) {
            currentType = EntityType::Call;
        } else if (designEntity->isToken("while")) {
            currentType = EntityType::While;
        } else if (designEntity->isToken("if")) {
            currentType = EntityType::If;
        } else if (designEntity->isToken("variable")) {
            currentType = EntityType::Variable;
        } else if (designEntity->isToken("constant")) {
            currentType = EntityType::Constant;
        }

        std::shared_ptr<Token> synonym = tokenizer->popToken();
        if (!synonym->isIdent()) {
            if (synonym->isToken(TokenType::Empty)) {
                throw std::runtime_error("Expected synonym but found none");
            }
            throw std::runtime_error("Invalid synonym '" + synonym->getRep() + "'");
        }
        std::shared_ptr<Entity> newEntity = std::make_shared<Entity>(currentType, synonym->getRep());
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
            newEntity = std::make_shared<Entity>(currentType, synonym->getRep());
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

    std::shared_ptr<Entity> entity = query.getEntity(next->getRep());
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
        clause.setType(RelationshipType::Uses);
    } else if (absToken->isToken("Follows")) {
        clause.setType(RelationshipType::Follows);
    } else if (absToken->isToken("Follows*")){
        clause.setType(RelationshipType::FollowsStar);
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

    RelationshipType type = clause.getType();
    Ref leftRef = clause.getLeftRef();
    RootType leftRootType = leftRef.getRootType();
    Ref rightRef = clause.getRightRef();
    RootType rightRootType = rightRef.getRootType();

//    // check that synonyms are declared
//    if (leftRootType == RootType::Synonym) {
//        std::shared_ptr<Entity> entity = query.getEntity(leftRef.getRep());
//        if (!entity) {
//            throw std::runtime_error("Invalid LHS, undeclared synonym found");
//        }
//    }
//
//    if (rightRootType == RootType::Synonym) {
//        std::shared_ptr<Entity> entity = query.getEntity(rightRef.getRep());
//        if (!entity) {
//            throw std::runtime_error("Invalid RHS, undeclared synonym found");
//        }
//    }

    // check wildcard & entity type
    if (type == RelationshipType::Uses) {
        if (leftRootType == RootType::Wildcard) {
            throw std::runtime_error("Invalid Uses LHS, wildcard found");
        }


        if (leftRootType == RootType::Synonym) {
            std::shared_ptr<Entity> entity = query.getEntity(leftRef.getRep());
            EntityType entityType = entity->getType();
            if (entityType != EntityType::Stmt && entityType != EntityType::Assign
                && entityType != EntityType::Print && entityType != EntityType::If
                && entityType != EntityType::While && entityType != EntityType::Procedure
                && entityType != EntityType::Call) {
                throw std::runtime_error("Invalid Uses LHS, invalid entity type found");
            }
        }

        if (rightRootType == RootType::Synonym) {
            std::shared_ptr<Entity> entity = query.getEntity(rightRef.getRep());
            EntityType entityType = entity->getType();
            if (entityType != EntityType::Variable) {
                throw std::runtime_error("Invalid Uses RHS, non-variable found");
            }
        }

    } else if (type == RelationshipType::Follows) {
        if (leftRootType == RootType::Synonym) {
            std::shared_ptr<Entity> entity = query.getEntity(leftRef.getRep());
            EntityType entityType = entity->getType();
            if (entityType != EntityType::Stmt && entityType != EntityType::Assign
                && entityType != EntityType::Print && entityType != EntityType::If
                && entityType != EntityType::While && entityType != EntityType::Call
                && entityType != EntityType::Read) {
                throw std::runtime_error("Invalid Follows LHS, non-statement found");
            }
        }

        if (rightRootType == RootType::Synonym) {
            std::shared_ptr<Entity> entity = query.getEntity(rightRef.getRep());
            EntityType entityType = entity->getType();
            if (entityType != EntityType::Stmt && entityType != EntityType::Assign
                && entityType != EntityType::Print && entityType != EntityType::If
                && entityType != EntityType::While && entityType != EntityType::Call
                && entityType != EntityType::Read) {
                throw std::runtime_error("Invalid Follows RHS, non-statement found");
            }
        }

    } else if (type == RelationshipType::FollowsStar) {
        if (leftRootType == RootType::Synonym) {
            std::shared_ptr<Entity> entity = query.getEntity(leftRef.getRep());
            EntityType entityType = entity->getType();
            if (entityType != EntityType::Stmt && entityType != EntityType::Assign
                && entityType != EntityType::Print && entityType != EntityType::If
                && entityType != EntityType::While && entityType != EntityType::Call
                && entityType != EntityType::Read) {
                throw std::runtime_error("Invalid Follows* LHS, non-statement found");
            }
        }

        if (rightRootType == RootType::Synonym) {
            std::shared_ptr<Entity> entity = query.getEntity(leftRef.getRep());
            EntityType entityType = entity->getType();
            if (entityType != EntityType::Stmt && entityType != EntityType::Assign
                && entityType != EntityType::Print && entityType != EntityType::If
                && entityType != EntityType::While && entityType != EntityType::Call
                && entityType != EntityType::Read) {
                throw std::runtime_error("Invalid Follows* RHS, non-statement found");
            }
        }
    }
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
    RelationshipType type = clause.getType();
    Ref ref;

    // validate if synonyms

    if (type == RelationshipType::Uses) {
        std::shared_ptr<Token> next = tokenizer->peekToken();
        if (next->isIdent()) {
            std::shared_ptr<Entity> entity = query.getEntity(next->getRep());
            if (!entity) {
                throw std::runtime_error("Invalid Uses LHS, undeclared synonym found");
            }

            if (entity->getType() == EntityType::Procedure) {
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
    } else if (type == RelationshipType::Follows) {
        ref = extractStmtRef(query);
    } else if (type == RelationshipType::FollowsStar) {
        ref = extractStmtRef(query);
    } else {
        throw std::runtime_error("Invalid Relationship Type in left such that clause");
    }

    clause.setLeftRef(ref);
}

void PQLParser::processSuchThatRight(Query &query, SuchThatClause &clause) {
    RelationshipType type = clause.getType();
    Ref ref;
    if (type == RelationshipType::Uses) {
        ref = extractEntRef(query);
    } else if (type == RelationshipType::Follows) {
        ref = extractStmtRef(query);
    } else if (type == RelationshipType::FollowsStar) {
        ref = extractStmtRef(query);
    } else {
        throw std::runtime_error("Invalid Relationship Type in left such that clause");
    }

    clause.setRightRef(ref);
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
        std::shared_ptr<Entity> entity = query.getEntity(refString);
        if (!entity) {
            throw std::runtime_error("Undeclared synonym found");
        }
        EntityType entityType = entity->getType();
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
        std::shared_ptr<Entity> entity = query.getEntity(refString);
        if (!entity) {
            throw std::runtime_error("Undeclared synonym found");
        }
        EntityType entityType = entity->getType();
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
