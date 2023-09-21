
#include <string>
#include <stdexcept>
#include <stack>

#include "PQLParser.h"
#include "Tokenizer.h"
#include "SuchThatClause.h"
#include "QPS/SemanticValHandler/SynonymHandler.h"
#include "QPS/SemanticValHandler/StmtrefStmtrefHandler.h"
#include "QPS/SemanticValHandler/StmtrefEntrefHandler.h"
#include "QPSUtil.h"


PQLParser::PQLParser(const std::string& PQLQuery) : tokenizer(std::make_shared<Tokenizer>(PQLQuery)){}

Query PQLParser::parse() {
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

        std::shared_ptr<Token> synonym = tokenizer->popToken();
        if (!synonym->isIdent()) {
            if (synonym->isToken(TokenType::Empty)) {
                throw std::runtime_error("Expected synonym but found none");
            }
            throw std::runtime_error("Invalid synonym '" + synonym->getRep() + "'");
        }
        EntityPtr newEntity = std::make_shared<QueryEntity>(designEntity, synonym->getRep());
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
            newEntity = std::make_shared<QueryEntity>(designEntity, synonym->getRep());
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
    std::shared_ptr<SuchThatClause> clause = std::make_shared<SuchThatClause>(absToken);
    validateSuchThatSyntax(clause);
    validateSuchThatSemantics(query, clause);
    query.addSuchThat(clause);
}

void PQLParser::validateSuchThatSyntax(const std::shared_ptr<SuchThatClause>& clause) {
    std::shared_ptr<Token> next = tokenizer->popToken();
    if (!next->isToken(TokenType::Lparenthesis)) {
        throw std::runtime_error("No left parenthesis");
    }

    Ref leftRef = extractRef();
    clause->setFirstParam(leftRef);

    next = tokenizer->popToken();
    if (!next->isToken(TokenType::Comma)) {
        throw std::runtime_error("No comma");
    }

    Ref rightRef = extractRef();
    clause->setSecondParam(rightRef);

    next = tokenizer->popToken();
    if (!next->isToken(TokenType::Rparenthesis)) {
        throw std::runtime_error("No right parenthesis");
    }

    validateSuchThatRefType(clause);
}

void PQLParser::validateSuchThatRefType(const std::shared_ptr<SuchThatClause>& clause) {
    ClauseType type = clause->getType();
    Ref& leftRef = clause->getFirstParam();
    Ref& rightRef = clause->getSecondParam();
    RootType leftRootType = leftRef.getRootType();
    RootType rightRootType = rightRef.getRootType();

    switch (type) {
        case ClauseType::Uses:
        case ClauseType::Modifies:
            // check right
            if (!QPSUtil::isRootOfEntref(rightRootType)) {
                throw std::runtime_error("Invalid RHS, entRef expected");
            }
            break;
        case ClauseType::Follows:
        case ClauseType::FollowsStar:
        case ClauseType::Parent:
        case ClauseType::ParentStar:
            // check left
            if (!QPSUtil::isRootOfStmtref(leftRootType)) {
                throw std::runtime_error("Invalid LHS, stmtRef expected");
            }
            // check right
            if (!QPSUtil::isRootOfStmtref(rightRootType)) {
                throw std::runtime_error("Invalid RHS, stmtRef expected");
            }
            break;
        default:
            throw std::runtime_error("Invalid ClauseType in Such That Clause");
    }
}

// TODO: generalise this to cater both such that & pattern clauses
void PQLParser::validateSuchThatSemantics(Query& query, const std::shared_ptr<SuchThatClause>& clause) {
    std::shared_ptr<SynonymHandler> synonymHandler = std::make_shared<SynonymHandler>();
    std::shared_ptr<StmtrefStmtrefHandler> stmtrefHandler = std::make_shared<StmtrefStmtrefHandler>();
    std::shared_ptr<StmtrefEntrefHandler> stmtEntHandler = std::make_shared<StmtrefEntrefHandler>();
    synonymHandler->setNext(stmtrefHandler)->setNext(stmtEntHandler);
    synonymHandler->handle(query, clause);
}

void PQLParser::processPatternClause(Query& query) {
    std::shared_ptr<Token> patternToken = tokenizer->peekToken();
    try {
        expect(patternToken->isToken("pattern"), "No pattern");
    } catch (...) {
        return;
    }

    std::shared_ptr<PatternClause> clause = std::make_shared<PatternClause>();

    std::shared_ptr<Token> patternSyn = tokenizer->popToken();
    clause->setSyn(patternSyn->getRep());

    std::shared_ptr<Token> next = tokenizer->popToken();
    if (!next->isToken(TokenType::Lparenthesis)) {
        throw std::runtime_error("Expected Lparenthesis");
    }

    Ref firstParam = extractRef();
    clause->setFirstParam(firstParam);

    next = tokenizer->popToken();
    if (!next->isToken(TokenType::Comma)) {
        throw std::runtime_error("Expected comma ");
    }

    try {
        ExpressionSpec secondParam = extractExpressionSpec();
        clause->setSecondParam(secondParam);
    } catch (...) {
        throw std::runtime_error("INVALID EXPRESSION SPEC ");
    }

    next = tokenizer->popToken();
    expect(next->isToken(TokenType::Rparenthesis), "Expected right parenthesis");

    validatePatternSemantics(query, clause);
    query.addPattern(clause);
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

// Expr spec methods
ExpressionSpec PQLParser::extractExpressionSpec() {
    std::shared_ptr<Token> curr = tokenizer->peekToken();
    if (curr->isToken(TokenType::Underscore)) { // WILDCARD OR PARTIAL MATCH
        tokenizer->popToken();
        curr = tokenizer->peekToken();
        if (!curr->isToken(TokenType::Quote)) { //WILDCARD
            return {ExpressionSpecType::Wildcard, ""};
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
    std::vector<std::shared_ptr<Token>> tokens;

    curr = tokenizer->popToken();
    while (!curr->isToken(TokenType::Quote)) {
        tokens.push_back(curr);
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
    if (!validateExprSyntax(tokens)) {
        throw std::runtime_error("Invalid Expression Spec from VALIDATE");
    }
    return expression.top();
}

bool PQLParser::validateExprSyntax(std::vector<std::shared_ptr<Token>>& input) {
    size_t currIndex = 0;
    return isExpr(input, currIndex) && currIndex == input.size();
}

bool PQLParser::isExpr(std::vector<std::shared_ptr<Token>>& input, size_t& index) {
    if (index >= input.size()) {
        return false;
    }
    if(isTerm(input, index)) {
        while (index < input.size()
               && (input[index]->isToken(TokenType::Plus)
                   || input[index]->isToken(TokenType::Minus))) {
            index++;
            if (!isTerm(input, index)) {
                return false;
            }
        }
        return true;
    }
    return false;
}

bool PQLParser::isTerm(std::vector<std::shared_ptr<Token>>& input, size_t& index) {
    if (index >= input.size()) {
        return false;
    }
    if (isFactor(input, index)) {
        while (index < input.size()
               && (input[index]->isToken(TokenType::Asterisk)
                   || input[index]->isToken(TokenType::Slash)
                   || input[index]->isToken(TokenType::Percent))) {
            index++;
            if (!isFactor(input, index)) {
                return false;
            }
        }
        return true;
    }
    return false;
}

bool PQLParser::isFactor(std::vector<std::shared_ptr<Token>>& input, size_t& index) {
    if (index >= input.size()) {
        return false;
    }
    if (input[index]->isIdent() || input[index]->isInteger()) {
        index++;
        return true;
    }
    if (input[index]->isToken(TokenType::Lparenthesis)) {
        index++;
        bool hasValidExpr = isExpr(input, index);
        if (hasValidExpr && index < input.size()) {
            bool hasRParenthesis = input[index]->isToken(TokenType::Rparenthesis);
            index++;
            return hasRParenthesis;
        }
    }
    return false;
}

void PQLParser::validatePatternSemantics(Query& query, std::shared_ptr<PatternClause>& clause) {
    EntityPtr entity = query.getEntity(clause->getSyn());
    if (!entity) {
        throw std::runtime_error("Undeclared synonym in pattern clause");
    } else if (entity->getType() != QueryEntityType::Assign) {
        throw std::runtime_error("Unsupported pattern clause, expected an assign synonym");
    }
    clause->setType(ClauseType::Assign);

    // if firstParam is Synonym, check type is Variable and is declared in query
    Ref firstParam = clause->getFirstParam();
    RefType type = RefType::EntRef;
    clause->getFirstParam().setType(type);
    if (firstParam.getRootType() == RootType::Synonym) {
        EntityPtr var = query.getEntity(firstParam.getRep());
        if (var->getType() != QueryEntityType::Variable) {
            throw std::runtime_error("Unsupported first param in pattern clause, expected a variable synonym");
        }
        if (!var) {
            throw std::runtime_error("Undeclared synonym in pattern clause");
        }
    }
    QueryEntityType entType = QueryEntityType::Variable;
    clause->getFirstParam().setEntityType(entType);
}

