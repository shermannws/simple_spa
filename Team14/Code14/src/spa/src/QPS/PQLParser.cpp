
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
    processPatternClause(query);

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
    SuchThatClause clause;
    validateSuchThatSyntax(clause);
    validateSuchThatSemantics(query, clause);
    query.addSuchThat(clause);
}

void PQLParser::validateSuchThatSyntax(SuchThatClause& clause) {
    std::shared_ptr<Token> absToken = tokenizer->popToken();

    clause = SuchThatClause(absToken);
    std::shared_ptr<Token> next = tokenizer->popToken();
    if (!next->isToken(TokenType::Lparenthesis)) {
        throw std::runtime_error("No left parenthesis");
    }

    Ref leftRef = extractRef();
    clause.setFirstParam(leftRef);

    next = tokenizer->popToken();
    if (!next->isToken(TokenType::Comma)) {
        throw std::runtime_error("No comma");
    }

    Ref rightRef = extractRef();
    clause.setSecondParam(rightRef);

    next = tokenizer->popToken();
    if (!next->isToken(TokenType::Rparenthesis)) {
        throw std::runtime_error("No right parenthesis");
    }

    validateSuchThatRefType(clause);
}

void PQLParser::validateSuchThatRefType(SuchThatClause& clause) {
    ClauseType type = clause.getType();
    Ref& leftRef = clause.getFirstParam();
    Ref& rightRef = clause.getSecondParam();
    RootType leftRootType = leftRef.getRootType();
    RootType rightRootType = rightRef.getRootType();
    RefType leftType = RefType::Invalid;
    RefType rightType = RefType::Invalid;

    // TODO: to refactor checks of entRef and stmtRef to Utils?
    switch (type) {
        case ClauseType::Uses:
        case ClauseType::Modifies:
            // check right
            if (rightRootType == RootType::Synonym || rightRootType == RootType::Wildcard
                || rightRootType == RootType::Ident) {
                rightType = RefType::EntRef;
            } else {
                throw std::runtime_error("Invalid RHS, entRef expected");
            }
            break;
        case ClauseType::Follows:
        case ClauseType::FollowsStar:
        case ClauseType::Parent:
        case ClauseType::ParentStar:
            // check left
            if (leftRootType == RootType::Synonym || leftRootType == RootType::Wildcard
                || leftRootType == RootType::Integer) {
                leftType = RefType::StmtRef;
            } else {
                throw std::runtime_error("Invalid LHS, stmtRef expected");
            }

            // check right
            if (rightRootType == RootType::Synonym || rightRootType == RootType::Wildcard
                || rightRootType == RootType::Integer) {
                rightType = RefType::StmtRef;
            } else {
                throw std::runtime_error("Invalid RHS, stmtRef expected");
            }
            break;
        default:
            throw std::runtime_error("Invalid ClauseType in Such That Clause");
    }


    leftRef.setType(leftType);
    rightRef.setType(rightType);
}

void PQLParser::validateSuchThatSemantics(Query& query, SuchThatClause& clause) {
    ClauseType type = clause.getType();
    Ref& leftRef = clause.getFirstParam();
    RootType leftRootType = leftRef.getRootType();
    Ref& rightRef = clause.getSecondParam();
    RootType rightRootType = rightRef.getRootType();

    // check whether synonyms are declared
    if (leftRootType == RootType::Synonym) {
        std::shared_ptr<QueryEntity> entity = query.getEntity(leftRef.getRep());
        if (!entity) {
            throw std::runtime_error("Invalid LHS, undeclared synonym found");
        }
        QueryEntityType entityType = entity->getType();
        leftRef.setEntityType(entityType);
    }
    if (rightRootType == RootType::Synonym) {
        std::shared_ptr<QueryEntity> entity = query.getEntity(rightRef.getRep());
        if (!entity) {
            throw std::runtime_error("Invalid RHS, undeclared synonym found");
        }
        QueryEntityType entityType = entity->getType();
        rightRef.setEntityType(entityType);
    }


    // check wildcard & entity type
    if (type == ClauseType::Uses) {
        if (leftRootType == RootType::Wildcard) {
            throw std::runtime_error("Invalid Uses LHS, wildcard found");
        }

        if (leftRootType == RootType::Synonym) {
            std::shared_ptr<QueryEntity> entity = query.getEntity(leftRef.getRep());
            QueryEntityType entityType = entity->getType();
            if (!isOfUsesEntityType(entityType)) {
                throw std::runtime_error("Invalid Uses LHS, invalid entity type found");
            }

            if (entityType == QueryEntityType::Procedure) {
                RefType leftRefType = RefType::EntRef;
                leftRef.setType(leftRefType);
            } else {
                RefType leftRefType = RefType::StmtRef;
                leftRef.setType(leftRefType);
            }

        } else if (leftRootType == RootType::Integer) {
            RefType leftRefType = RefType::StmtRef;
            leftRef.setType(leftRefType);
        } else if (leftRootType == RootType::Ident) {
            RefType leftRefType = RefType::EntRef;
            leftRef.setType(leftRefType);
        }

        if (rightRootType == RootType::Synonym) {
            std::shared_ptr<QueryEntity> entity = query.getEntity(rightRef.getRep());
            QueryEntityType entityType = entity->getType();
            if (entityType != QueryEntityType::Variable) {
                throw std::runtime_error("Invalid Uses RHS, non-variable found");
            }
        }
    } else if (type == ClauseType::Modifies) {
        if (leftRootType == RootType::Wildcard) {
            throw std::runtime_error("Invalid Modifies LHS, wildcard found");
        }

        if (leftRootType == RootType::Synonym) {
            std::shared_ptr<QueryEntity> entity = query.getEntity(leftRef.getRep());
            QueryEntityType entityType = entity->getType();
            if (!isOfModifiesEntityType(entityType)) {
                throw std::runtime_error("Invalid Modifies LHS, invalid entity type found");
            }

            if (entityType == QueryEntityType::Procedure) {
                RefType leftRefType = RefType::EntRef;
                leftRef.setType(leftRefType);
            } else {
                RefType leftRefType = RefType::StmtRef;
                leftRef.setType(leftRefType);
            }

        } else if (leftRootType == RootType::Integer) {
            RefType leftRefType = RefType::StmtRef;
            leftRef.setType(leftRefType);
        } else if (leftRootType == RootType::Ident) {
            RefType leftRefType = RefType::EntRef;
            leftRef.setType(leftRefType);
        }

        if (rightRootType == RootType::Synonym) {
            std::shared_ptr<QueryEntity> entity = query.getEntity(rightRef.getRep());
            QueryEntityType entityType = entity->getType();
            if (entityType != QueryEntityType::Variable) {
                throw std::runtime_error("Invalid Modifies RHS, non-variable found");
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
            std::shared_ptr<QueryEntity> entity = query.getEntity(rightRef.getRep());
            QueryEntityType entityType = entity->getType();
            if (!isOfStmtType(entityType)) {
                throw std::runtime_error("Invalid Follows* RHS, non-statement found");
            }
        }
    } else if (type == ClauseType::Parent) {
        if (leftRootType == RootType::Synonym) {
            std::shared_ptr<QueryEntity> entity = query.getEntity(leftRef.getRep());
            QueryEntityType entityType = entity->getType();
            if (!isOfStmtType(entityType)) {
                throw std::runtime_error("Invalid Parent LHS, non-statement found");
            }
        }

        if (rightRootType == RootType::Synonym) {
            std::shared_ptr<QueryEntity> entity = query.getEntity(rightRef.getRep());
            QueryEntityType entityType = entity->getType();
            if (!isOfStmtType(entityType)) {
                throw std::runtime_error("Invalid Parent RHS, non-statement found");
            }
        }

    } else if (type == ClauseType::ParentStar) {
        if (leftRootType == RootType::Synonym) {
            std::shared_ptr<QueryEntity> entity = query.getEntity(leftRef.getRep());
            QueryEntityType entityType = entity->getType();
            if (!isOfStmtType(entityType)) {
                throw std::runtime_error("Invalid Parent* LHS, non-statement found");
            }
        }

        if (rightRootType == RootType::Synonym) {
            std::shared_ptr<QueryEntity> entity = query.getEntity(rightRef.getRep());
            QueryEntityType entityType = entity->getType();
            if (!isOfStmtType(entityType)) {
                throw std::runtime_error("Invalid Parent* RHS, non-statement found");
            }
        }
    }
}

void PQLParser::processPatternClause(Query& query) {
    std::shared_ptr<Token> patternToken = tokenizer->peekToken();
    try {
        expect(patternToken->isToken("pattern"), "No pattern");
    } catch (...) {
        return;
    }

    std::shared_ptr<Token> patternSyn = tokenizer->popToken();
    std::shared_ptr<QueryEntity> entity = query.getEntity(patternSyn->getRep());
    if (!entity) {
        throw std::runtime_error("Undeclared synonym in pattern clause");
    } else if (entity->getType() != QueryEntityType::Assign) {
        throw std::runtime_error("Unsupported pattern clause, expected an assignment");
    }

    std::shared_ptr<Token> next = tokenizer->popToken();
    if (!next->isToken(TokenType::Lparenthesis)) {
        throw std::runtime_error("Expected Lparenthesis");
    }

    next = tokenizer->popToken();
    if (!next->isToken(TokenType::Underscore)) {
        throw std::runtime_error("Expected wildcard as first arg");
    }

    next = tokenizer->popToken();
    if (!next->isToken(TokenType::Comma)) {
        throw std::runtime_error("Expected comma ");
    }

    next = tokenizer->popToken();
    if (!next->isToken(TokenType::Underscore)) {
        throw std::runtime_error("Expected wildcard as second arg");
    }

    Ref wildcard;
    std::string rep = next->getRep();
    RefType ent = RefType::EntRef;
    RootType root = RootType::Wildcard;
    wildcard.setRep(rep);
    wildcard.setRootType(root);
    wildcard.setType(ent);

    next = tokenizer->popToken();
    expect(next->isToken(TokenType::Rparenthesis), "Expected right parenthesis");

    PatternClause clause;
    clause.setType(ClauseType::Assign);
    clause.setEntity(entity);
    clause.setFirstParam(wildcard);
    clause.setSecondParam(wildcard);
    query.addPattern(clause);
}

bool PQLParser::isOfStmtType(QueryEntityType entityType) {
    return entityType == QueryEntityType::Stmt || entityType == QueryEntityType::Assign
           || entityType == QueryEntityType::Print || entityType == QueryEntityType::If
           || entityType == QueryEntityType::While || entityType == QueryEntityType::Call
           || entityType == QueryEntityType::Read;
}

bool PQLParser::isOfUsesEntityType(QueryEntityType entityType) {
    return entityType == QueryEntityType::Stmt || entityType == QueryEntityType::Assign
           || entityType == QueryEntityType::Print || entityType == QueryEntityType::If
           || entityType == QueryEntityType::While || entityType == QueryEntityType::Call
           || entityType == QueryEntityType::Procedure;
}

bool PQLParser::isOfModifiesEntityType(QueryEntityType entityType) {
    return entityType == QueryEntityType::Stmt || entityType == QueryEntityType::Assign
           || entityType == QueryEntityType::Read || entityType == QueryEntityType::If
           || entityType == QueryEntityType::While || entityType == QueryEntityType::Call
           || entityType == QueryEntityType::Procedure;
}

Ref PQLParser::extractRef() {
    Ref ref;
    RootType rootType;
    std::string refString;
    std::shared_ptr<Token> curr = tokenizer->peekToken();
    if (curr->isInteger()) { // INTEGER
        refString = tokenizer->popToken()->getRep();
        rootType = RootType::Integer;
    } else if (curr->isToken(TokenType::Quote)) { // IDENTITY
        tokenizer->popToken();
        std::shared_ptr<Token> syn = tokenizer->peekToken();
        expect(syn->isIdent(), "Identity invalid");
        std::string right_quote = tokenizer->peekToken()->getRep();
        expect(tokenizer->peekToken()->isToken(TokenType::Quote), "No right quote");

        refString = syn->getRep();
        rootType = RootType::Ident;
    } else if (curr->isToken(TokenType::Underscore)) { // WILDCARD
        refString = tokenizer->popToken()->getRep();
        rootType = RootType::Wildcard;
    } else if (curr->isToken(TokenType::Word) && curr->isIdent()) { // SYNONYM
        refString = tokenizer->popToken()->getRep();
        rootType = RootType::Synonym;
    } else {
        throw std::runtime_error("Invalid stmtRef");
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
