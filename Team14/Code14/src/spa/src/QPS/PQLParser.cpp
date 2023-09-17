
#include <string>
#include <stdexcept>
#include <stack>

#include "PQLParser.h"
#include "Tokenizer.h"
#include "SuchThatClause.h"


PQLParser::PQLParser(const std::string& PQLQuery) : tokenizer(std::make_shared<Tokenizer>(PQLQuery)){}

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
        EntityPtr newEntity = std::make_shared<QueryEntity>(currentType, synonym->getRep());
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

    EntityPtr entity = query.getEntity(next->getRep());
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
    } else if (absToken->isToken("Modifies")) {
        clause.setType(ClauseType::Modifies);
    } else if (absToken->isToken("Follows")) {
        clause.setType(ClauseType::Follows);
    } else if (absToken->isToken("Follows*")) {
        clause.setType(ClauseType::FollowsStar);
    } else if (absToken->isToken("Parent")) {
        clause.setType(ClauseType::Parent);
    } else if (absToken->isToken("Parent*")) {
        clause.setType(ClauseType::ParentStar);
    } else {
        throw std::runtime_error("Invalid token, abstraction expected");
    }

    processSuchThatBody(query, clause);
    validateSuchThatSemantics(query, clause);
    query.addSuchThat(clause);

    // TODO: handle multiple "such that" and here recursively
}

void PQLParser::processPatternClause(Query& query) {
    std::shared_ptr<Token> patternToken = tokenizer->peekToken(); //TODO use expect func
    try {
        expect(patternToken->isToken("pattern"), "No pattern");
    } catch (...) {
        return;
    }

    std::shared_ptr<Token> patternSyn = tokenizer->popToken();
    EntityPtr entity = query.getEntity(patternSyn->getRep());
    if (!entity) {
        throw std::runtime_error("Undeclared synonym in pattern clause");
    } else if (entity->getType() != QueryEntityType::Assign) {
        throw std::runtime_error("Unsupported pattern clause, expected an assignment");
    }
    PatternClause clause;
    clause.setType(ClauseType::Assign);
    clause.setEntity(entity);

    std::shared_ptr<Token> next = tokenizer->popToken();
    if (!next->isToken(TokenType::Lparenthesis)) {
        throw std::runtime_error("Expected Lparenthesis");
    }

    Ref firstParam = extractEntRef(query);
    clause.setFirstParam(firstParam);

    next = tokenizer->popToken();
    if (!next->isToken(TokenType::Comma)) {
        throw std::runtime_error("Expected comma ");
    }

    try {
        ExpressionSpec secondParam = extractExpressionSpec();
        clause.setSecondParam(secondParam);
    } catch (...) {
        throw std::runtime_error("INVALID EXPRESSION SPEC ");
    }

    next = tokenizer->popToken();
    expect(next->isToken(TokenType::Rparenthesis), "Expected right parenthesis");

    query.addPattern(clause);
}

void PQLParser::validateSuchThatSemantics(Query& query, SuchThatClause& clause) {
    // TODO: refactor checks/error messages and prevent DRY

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
            EntityPtr entity = query.getEntity(leftRef.getRep());
            QueryEntityType entityType = entity->getType();
            if (!isOfUsesEntityType(entityType)) {
                throw std::runtime_error("Invalid Uses LHS, invalid entity type found");
            }
        }

        if (rightRootType == RootType::Synonym) {
            EntityPtr entity = query.getEntity(rightRef.getRep());
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
            EntityPtr entity = query.getEntity(leftRef.getRep());
            QueryEntityType entityType = entity->getType();
            if (!isOfModifiesEntityType(entityType)) {
                throw std::runtime_error("Invalid Modifies LHS, invalid entity type found");
            }
        }

        if (rightRootType == RootType::Synonym) {
            EntityPtr entity = query.getEntity(rightRef.getRep());
            QueryEntityType entityType = entity->getType();
            if (entityType != QueryEntityType::Variable) {
                throw std::runtime_error("Invalid Modifies RHS, non-variable found");
            }
        }
    } else if (type == ClauseType::Follows) {
        if (leftRootType == RootType::Synonym) {
            EntityPtr entity = query.getEntity(leftRef.getRep());
            QueryEntityType entityType = entity->getType();
            if (!isOfStmtType(entityType)) {
                throw std::runtime_error("Invalid Follows LHS, non-statement found");
            }
        }

        if (rightRootType == RootType::Synonym) {
            EntityPtr entity = query.getEntity(rightRef.getRep());
            QueryEntityType entityType = entity->getType();
            if (!isOfStmtType(entityType)) {
                throw std::runtime_error("Invalid Follows RHS, non-statement found");
            }
        }

    } else if (type == ClauseType::FollowsStar) {
        if (leftRootType == RootType::Synonym) {
            EntityPtr entity = query.getEntity(leftRef.getRep());
            QueryEntityType entityType = entity->getType();
            if (!isOfStmtType(entityType)) {
                throw std::runtime_error("Invalid Follows* LHS, non-statement found");
            }
        }

        if (rightRootType == RootType::Synonym) {
            EntityPtr entity = query.getEntity(rightRef.getRep());
            QueryEntityType entityType = entity->getType();
            if (!isOfStmtType(entityType)) {
                throw std::runtime_error("Invalid Follows* RHS, non-statement found");
            }
        }
    } else if (type == ClauseType::Parent) {
        if (leftRootType == RootType::Synonym) {
            EntityPtr entity = query.getEntity(leftRef.getRep());
            QueryEntityType entityType = entity->getType();
            if (!isOfStmtType(entityType)) {
                throw std::runtime_error("Invalid Parent LHS, non-statement found");
            }
        }

        if (rightRootType == RootType::Synonym) {
            EntityPtr entity = query.getEntity(rightRef.getRep());
            QueryEntityType entityType = entity->getType();
            if (!isOfStmtType(entityType)) {
                throw std::runtime_error("Invalid Parent RHS, non-statement found");
            }
        }

    } else if (type == ClauseType::ParentStar) {
        if (leftRootType == RootType::Synonym) {
            EntityPtr entity = query.getEntity(leftRef.getRep());
            QueryEntityType entityType = entity->getType();
            if (!isOfStmtType(entityType)) {
                throw std::runtime_error("Invalid Parent* LHS, non-statement found");
            }
        }

        if (rightRootType == RootType::Synonym) {
            EntityPtr entity = query.getEntity(rightRef.getRep());
            QueryEntityType entityType = entity->getType();
            if (!isOfStmtType(entityType)) {
                throw std::runtime_error("Invalid Parent* RHS, non-statement found");
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

void PQLParser::processSuchThatBody(Query& query, SuchThatClause& clause) {
    expect(tokenizer->peekToken()->isToken(TokenType::Lparenthesis), "No left parenthesis");
    processSuchThatLeft(query, clause);
    expect(tokenizer->peekToken()->isToken(TokenType::Comma), "No comma");
    processSuchThatRight(query, clause);
    expect(tokenizer->peekToken()->isToken(TokenType::Rparenthesis), "No right parenthesis");
}

void PQLParser::processSuchThatLeft(Query &query, SuchThatClause &clause) {
    // TODO: refactor and prevent DRY
    ClauseType type = clause.getType();
    Ref ref;

    // validate if synonyms

    if (type == ClauseType::Uses) {
        std::shared_ptr<Token> next = tokenizer->peekToken();
        if (next->isIdent()) {
            EntityPtr entity = query.getEntity(next->getRep());
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
    } else if (type == ClauseType::Modifies) {
        std::shared_ptr<Token> next = tokenizer->peekToken();
        if (next->isIdent()) {
            EntityPtr entity = query.getEntity(next->getRep());
            if (!entity) {
                throw std::runtime_error("Invalid Modifies LHS, undeclared synonym found");
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
    } else if (type == ClauseType::Follows || type == ClauseType::FollowsStar
               || type == ClauseType::Parent || type == ClauseType::ParentStar) {
        ref = extractStmtRef(query);
    } else {
        throw std::runtime_error("Invalid Relationship Type in left such that clause");
    }

    clause.setFirstParam(ref);
}

void PQLParser::processSuchThatRight(Query &query, SuchThatClause &clause) {
    ClauseType type = clause.getType();
    Ref ref;
    if (type == ClauseType::Uses || type == ClauseType::Modifies) {
        ref = extractEntRef(query);
    } else if (type == ClauseType::Follows || type == ClauseType::FollowsStar
               || type == ClauseType::Parent || type == ClauseType::ParentStar) {
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
        EntityPtr entity = query.getEntity(refString);
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

        refString = syn->getRep();
        rootType = RootType::Ident;
    } else if (curr->isToken(TokenType::Underscore)) { // WILDCARD
        refString = tokenizer->popToken()->getRep();
        rootType = RootType::Wildcard;
    } else if (curr->isToken(TokenType::Word) && curr->isIdent()) { // SYNONYM
        refString = tokenizer->popToken()->getRep();
        rootType = RootType::Synonym;

        // check that synonyms are declared
        EntityPtr entity = query.getEntity(refString);
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

ExpressionSpec PQLParser::extractExpressionSpec() {
    std::shared_ptr<Token> curr = tokenizer->peekToken();
    if (curr->isToken(TokenType::Underscore)) { // WILDCARD OR PARTIAL MATCH
        tokenizer->popToken();
        curr = tokenizer->peekToken();
        if (!curr->isToken(TokenType::Quote)) { //WILDCARD
            return {ExpressionSpecType::WildCard, ""};
        } else {
            Expression expr = extractExpression();
            curr = tokenizer->popToken(); //consume expected trailing underscore
            if (!curr->isToken(TokenType::Underscore)) {
                throw std::runtime_error("Invalid Expression Spec, missing trailing _");
            }
            return {ExpressionSpecType::PartialMatch,expr};
        }
    } else if (curr->isToken(TokenType::Quote)) { // EXACT MATCH
        Expression expr = extractExpression();
        return {ExpressionSpecType::ExactMatch,expr};
    } else {
        throw std::runtime_error("Invalid Expression Spec");
    }
}

Expression PQLParser::extractExpression() {
    std::shared_ptr<Token> curr = tokenizer->peekToken(); // consume Quote
    expect (curr->isToken(TokenType::Quote), "Invalid expression spec");

    std::stack<std::shared_ptr<Token>> operators;
    std::stack<std::string> expression;
    std::string rawInput;

    curr = tokenizer->popToken();
    while (!curr->isToken(TokenType::Quote)) {
        rawInput += curr->getRep();
        if (curr->isOperand()) {
            expression.push("(" + curr->getRep() + ")");
        } else if (curr->isToken(TokenType::Lparenthesis)) {
            operators.push(curr);
        } else if (curr->isOperator()) {
            while (!operators.empty()
                    && !operators.top()->isToken(TokenType::Lparenthesis)
                    && operators.top()->precedes(curr)) {
                if (expression.size() < 2) {
                    throw std::runtime_error("not enough factors");
                }
                auto rightOperand = expression.top();
                expression.pop();
                auto leftOperand = expression.top();
                expression.pop();
                expression.push("(" + leftOperand + operators.top()->getRep() + rightOperand + ")");
                operators.pop();
            }
            operators.push(curr);
        } else if (curr->isToken(TokenType::Rparenthesis)) {
            while (!operators.empty() && !operators.top()->isToken(TokenType::Lparenthesis)) {
                if (expression.size() < 2) {
                    throw std::runtime_error("not enough factors");
                }
                auto rightOperand = expression.top();
                expression.pop();
                auto leftOperand = expression.top();
                expression.pop();
                expression.push("(" + leftOperand + operators.top()->getRep() + rightOperand + ")");
                operators.pop();
            }
            if (!operators.top()->isToken(TokenType::Lparenthesis)){ // pop Lparentheses
                throw std::runtime_error("Invalid expression spec");
            }
            operators.pop();
        } else { //unexpected token
            throw std::runtime_error("Invalid expression spec");
        }
        curr = tokenizer->popToken();
    }
    while(!operators.empty()) {
        if (expression.size() < 2) {
            throw std::runtime_error("not enough factors");
        }
        auto rightOperand = expression.top();
        expression.pop();
        auto leftOperand = expression.top();
        expression.pop();
        expression.push("(" + leftOperand + operators.top()->getRep() + rightOperand + ")");
        operators.pop();
    }

    if (expression.empty() || expression.size() > 1) { // empty expression OR too many factors e.g "x y"
        throw std::runtime_error("Invalid Expression Spec");
    }

    // TODO validate rawInput (handle cases like "xy+")
    return expression.top();
}

std::shared_ptr<Token> PQLParser::expect(bool isToken, const std::string& errorMsg) {
    if (!isToken) {
        throw std::runtime_error(errorMsg);
    }
    return tokenizer->popToken();
}
