
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
    std::shared_ptr<Token> such_that_token = tokenizer->peekToken();
    try {
        expect(such_that_token->isToken("such that"), "No such that");
    } catch (...) {
        return;
    }

    std::shared_ptr<Token> abs_token = tokenizer->popToken();

    SuchThatClause clause;
    if (abs_token->isToken("Uses")) {
        clause.setType(RelationshipType::Uses);
    } else if (abs_token->isToken("Follows")) {
        clause.setType(RelationshipType::Follows);
    } else if (abs_token->isToken("Follows*")){
        clause.setType(RelationshipType::FollowsStar);
    } else {
        throw std::runtime_error("Token does not match any abstraction");
    }

    processSuchThatBody(query, clause);
    query.addSuchThatClause(clause);

    // TODO: semantic validation of such that clause
    validateSuchThatSemantics(query, clause);

    // TODO: handle multiple "such that" and here recursively
}

void PQLParser::validateSuchThatSemantics(Query& query, SuchThatClause& clause) {
    // TODO: check Uses (done) & modifies cannot be wildcard
    // TODO: check each entity is appropriate for the RelationshipType
    // TODO: check synonyms are declared
    RelationshipType type = clause.getType();
    Ref left_ref = clause.getLeftRef();
    RefType left_type = left_ref.getType();
    RootType left_root_type = left_ref.getRootType();
    Ref right_ref = clause.getRightRef();
    RefType right_type = right_ref.getType();
    RootType right_root_type = right_ref.getRootType();

    // check synonyms are declared
    if (left_root_type == RootType::Synonym) {
        std::shared_ptr<Entity> entity = query.getEntity(left_ref.getRep());
        if (!entity) {
            throw std::runtime_error("Invalid LHS, undeclared synonym found");
        }
    }

    if (right_root_type == RootType::Synonym) {
        std::shared_ptr<Entity> entity = query.getEntity(right_ref.getRep());
        if (!entity) {
            throw std::runtime_error("Invalid RHS, undeclared synonym found");
        }
    }

    // check wildcard & entity type
    if (type == RelationshipType::Uses) {
        if (left_root_type == RootType::Wildcard) {
            throw std::runtime_error("Invalid Uses LHS, wildcard found");
        }
        if (left_root_type == RootType::Synonym) {
            std::shared_ptr<Entity> entity = query.getEntity(left_ref.getRep());
            EntityType entity_type = entity->getType();
            if (entity_type != EntityType::Stmt && entity_type != EntityType::Assign
                && entity_type != EntityType::Print && entity_type != EntityType::If
                && entity_type != EntityType::While && entity_type != EntityType::Procedure
                && entity_type != EntityType::Call) {
                throw std::runtime_error("Invalid Uses LHS, invalid entity type found");
            }
        }

        if (right_root_type == RootType::Synonym) {
            std::shared_ptr<Entity> entity = query.getEntity(right_ref.getRep());
            EntityType entity_type = entity->getType();
            if (entity_type != EntityType::Variable) {
                throw std::runtime_error("Invalid Uses RHS, non-variable found");
            }

        }

    } else if (type == RelationshipType::Follows) {
        if (left_root_type == RootType::Synonym) {
            std::shared_ptr<Entity> entity = query.getEntity(left_ref.getRep());
            EntityType entity_type = entity->getType();
            if (entity_type != EntityType::Stmt && entity_type != EntityType::Assign
                && entity_type != EntityType::Print && entity_type != EntityType::If
                && entity_type != EntityType::While && entity_type != EntityType::Procedure
                && entity_type != EntityType::Call && entity_type != EntityType::Read) {
                throw std::runtime_error("Invalid Follows LHS, non-statement found");
            }
        }

        if (right_root_type == RootType::Synonym) {
            std::shared_ptr<Entity> entity = query.getEntity(right_ref.getRep());
            EntityType entity_type = entity->getType();
            if (entity_type != EntityType::Stmt && entity_type != EntityType::Assign
                && entity_type != EntityType::Print && entity_type != EntityType::If
                && entity_type != EntityType::While && entity_type != EntityType::Procedure
                && entity_type != EntityType::Call && entity_type != EntityType::Read) {
                throw std::runtime_error("Invalid Follows RHS, non-statement found");
            }
        }

    } else if (type == RelationshipType::FollowsStar) {
        if (left_root_type == RootType::Synonym) {
            std::shared_ptr<Entity> entity = query.getEntity(left_ref.getRep());
            EntityType entity_type = entity->getType();
            if (entity_type != EntityType::Stmt && entity_type != EntityType::Assign
                && entity_type != EntityType::Print && entity_type != EntityType::If
                && entity_type != EntityType::While && entity_type != EntityType::Procedure
                && entity_type != EntityType::Call && entity_type != EntityType::Read) {
                throw std::runtime_error("Invalid Follows* LHS, non-statement found");
            }
        }

        if (right_root_type == RootType::Synonym) {
            std::shared_ptr<Entity> entity = query.getEntity(left_ref.getRep());
            EntityType entity_type = entity->getType();
            if (entity_type != EntityType::Stmt && entity_type != EntityType::Assign
                && entity_type != EntityType::Print && entity_type != EntityType::If
                && entity_type != EntityType::While && entity_type != EntityType::Procedure
                && entity_type != EntityType::Call && entity_type != EntityType::Read) {
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
    if (type == RelationshipType::Uses) {
        // TODO: how to check IF STMT OR REF
        std::shared_ptr<Token> next = tokenizer->peekToken();
        if (next->isIdent()) {
            std::shared_ptr<Entity> entity = query.getEntity(next->getRep());
            if (!entity) {
                throw std::runtime_error("Invalid Uses LHS");
            }

            if (entity->getType() == EntityType::Procedure) {
                ref = extractEntRef();
            } else {
                ref = extractStmtRef();
            }

        } else {
            try {
                ref = extractStmtRef();
            } catch (...) {
                ref = extractEntRef();
            }
        }
    } else if (type == RelationshipType::Follows) {
        ref = extractStmtRef();
    } else if (type == RelationshipType::FollowsStar) {
        ref = extractStmtRef();
    } else {
        throw std::runtime_error("Invalid Relationship Type in left such that clause");
    }

    clause.setLeftRef(ref);
}

void PQLParser::processSuchThatRight(Query &query, SuchThatClause &clause) {
    RelationshipType type = clause.getType();
    Ref ref;
    if (type == RelationshipType::Uses) {
        ref = extractEntRef();
    } else if (type == RelationshipType::Follows) {
        ref = extractStmtRef();
    } else if (type == RelationshipType::FollowsStar) {
        ref = extractStmtRef();
    } else {
        throw std::runtime_error("Invalid Relationship Type in left such that clause");
    }

    clause.setRightRef(ref);
}

Ref PQLParser::extractStmtRef() {
    Ref ref;
    RefType type = RefType::StmtRef;
    ref.setType(type);
    RootType root_type;

    std::string ref_string;
    std::shared_ptr<Token> curr = tokenizer->peekToken();
    if (curr->isInteger()) { // INTEGER
        ref_string = tokenizer->popToken()->getRep();
        root_type = RootType::Integer;
    } else if (curr->isToken(TokenType::Underscore)) { // WILDCARD
        ref_string = tokenizer->popToken()->getRep();
        root_type = RootType::Wildcard;
    } else if (curr->isToken(TokenType::Word) && curr->isIdent()) { // SYNONYM
        ref_string = tokenizer->popToken()->getRep();
        root_type = RootType::Synonym;
    } else {
        throw std::runtime_error("Invalid stmtRef");
    }

    ref.setRep(ref_string);
    ref.setRootType(root_type);
    return ref;
}

Ref PQLParser::extractEntRef() {
    Ref ref;
    RefType type = RefType::EntRef;
    ref.setType(type);
    RootType root_type;

    std::string ref_string;
    std::shared_ptr<Token> curr = tokenizer->peekToken();
    if (curr->isToken(TokenType::Quote)) { // IDENTITY
        tokenizer->popToken();
        std::shared_ptr<Token> syn = tokenizer->popToken();
        expect(syn->isIdent(), "Identity invalid");
        expect(tokenizer->peekToken()->isToken(TokenType::Quote), "No right quote");

        ref_string = "\"" + syn->getRep() + "\"";
        root_type = RootType::Ident;
    } else if (curr->isToken(TokenType::Underscore)) { // WILDCARD
        ref_string = tokenizer->popToken()->getRep();
        root_type = RootType::Wildcard;
    } else if (curr->isToken(TokenType::Word) && curr->isIdent()) { // SYNONYM
        ref_string = tokenizer->popToken()->getRep();
        root_type = RootType::Synonym;
    } else {
        throw std::runtime_error("Invalid entRef");
    }

    ref.setRep(ref_string);
    ref.setRootType(root_type);
    return ref;
}

std::shared_ptr<Token> PQLParser::expect(bool isToken, const std::string& error_msg) {
    if (!isToken) {
        throw std::runtime_error(error_msg);
    }
    return tokenizer->popToken();
}
