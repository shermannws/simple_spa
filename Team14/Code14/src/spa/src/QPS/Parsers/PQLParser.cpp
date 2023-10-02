
#include <string>
#include <stack>

#include "PQLParser.h"
#include "Tokenizer.h"
#include "QPS/Clauses/SuchThatClause.h"
#include "SemanticValHandlers/SynonymHandler.h"
#include "SemanticValHandlers/StmtrefStmtrefHandler.h"
#include "SemanticValHandlers/StmtrefEntrefHandler.h"
#include "SemanticValHandlers/EntrefExprSpecHandler.h"
#include "QPS/Exceptions/SyntaxException.h"
#include "QPS/Exceptions/SemanticException.h"
#include "QPS/Parsers/SemanticValHandlers/EntrefEntrefHandler.h"


PQLParser::PQLParser(const std::string& PQLQuery) {
    tokenizer = std::make_shared<Tokenizer>(PQLQuery);
    exprSpecParser = std::make_shared<ExprSpecParser>(tokenizer);
}

Query PQLParser::parse() {
    std::vector<std::shared_ptr<QueryEntity>> entities = processDeclarations();
    Synonym select = processSelectClause();
    std::shared_ptr<SuchThatClause> stClause = processSuchThatClause();
    std::shared_ptr<PatternClause> pClause = processPatternClause();
    std::shared_ptr<Token> endOfQuery = tokenizer->peekToken();
    expect(endOfQuery->isToken(TokenType::Empty), "Invalid query syntax");

    Query query = Query();
    validateDeclarations(query, entities);
    validateSelectSemantics(query, select);
    validateSuchThatSemantics(query, stClause);
    validatePatternSemantics(query, pClause);

    return query;
}

std::vector<std::shared_ptr<QueryEntity>> PQLParser::processDeclarations() {
    std::vector<std::shared_ptr<QueryEntity>> entities;
    while(tokenizer->peekToken()->isDesignEntity()) {
        std::shared_ptr<Token> designEntity = tokenizer->popToken();
        EntityPtr newEntity = extractQueryEntity(designEntity);
        entities.push_back(newEntity);

        while(tokenizer->peekToken()->isToken(TokenType::Comma)) {
            tokenizer->popToken(); //consume comma
            newEntity = extractQueryEntity(designEntity);
            entities.push_back(newEntity);
        }

        std::shared_ptr<Token> endToken = tokenizer->popToken(); // consume semicolon
        if (!endToken->isToken(TokenType::Semicolon)) {
            throw SyntaxException("Expected ; but found '" + endToken->getRep() + + "'");
        }
    }

    if (entities.empty()) {
        throw SyntaxException("Expected a declaration but found none");
    }
    return entities;
}

Synonym PQLParser::processSelectClause() {
    std::shared_ptr<Token> next = tokenizer->popToken();
    if (!next->isToken("Select")) {
        throw SyntaxException("Expected Select clause but found '" + next->getRep() + "'");
    }
    next = tokenizer->popToken();

    if (!next->isIdent()) {
        throw SyntaxException("Invalid synonym syntax");
    }

    return next->getRep();
}

std::shared_ptr<SuchThatClause> PQLParser::processSuchThatClause() {
    // handle optional
    std::shared_ptr<Token> suchThatToken = tokenizer->peekToken();
    if (!suchThatToken->isToken("such that")) {
        return nullptr;
    }
    tokenizer->popToken();
    std::shared_ptr<Token> absToken = tokenizer->popToken();
    std::shared_ptr<SuchThatClause> clause = std::make_shared<SuchThatClause>(absToken);
    validateSuchThatSyntax(clause);
    return clause;
}

std::shared_ptr<PatternClause> PQLParser::processPatternClause() {
    std::shared_ptr<Token> patternToken = tokenizer->peekToken();
    if (!patternToken->isToken("pattern")) {
        return nullptr;
    }
    tokenizer->popToken();
    std::shared_ptr<PatternClause> clause = std::make_shared<PatternClause>();
    validatePatternSyntax(clause);
    return clause;
}

void PQLParser::validateDeclarations(Query& query, const std::vector<std::shared_ptr<QueryEntity>>& entities) {
    for (auto & entity : entities) {
        Synonym currSynonym = entity->getSynonym();
        if (query.getEntity(currSynonym)){
            throw SemanticException("Trying to redeclare a synonym");
        }
        query.addDeclaration(entity);
    }
}

void PQLParser::validateSelectSemantics(Query& query, const Synonym& syn) {
    EntityPtr entity = query.getEntity(syn);
    if (!entity) {
        throw SemanticException("Undeclared synonym in Select clause");
    }
    query.addSelect(entity);
}

void PQLParser::validateSuchThatSyntax(std::shared_ptr<SuchThatClause> clause) {
    std::shared_ptr<Token> next = tokenizer->popToken();
    if (!next->isToken(TokenType::Lparenthesis)) {
        throw SyntaxException("No left parenthesis");
    }

    Ref leftRef = extractRef();
    clause->setFirstParam(leftRef);

    next = tokenizer->popToken();
    if (!next->isToken(TokenType::Comma)) {
        throw SyntaxException("No comma");
    }

    Ref rightRef = extractRef();
    clause->setSecondParam(rightRef);

    next = tokenizer->popToken();
    if (!next->isToken(TokenType::Rparenthesis)) {
        throw SyntaxException("No right parenthesis");
    }

    validateSuchThatRefType(clause);
}

void PQLParser::validateSuchThatRefType(const std::shared_ptr<SuchThatClause> clause) {
    ClauseType type = clause->getType();
    Ref& leftRef = clause->getFirstParam();
    Ref& rightRef = clause->getSecondParam();

    switch (type) {
        case ClauseType::Uses:
        case ClauseType::Modifies:
            // check right
            if (!rightRef.isOfEntRef()) {
                throw SyntaxException("Invalid RHS entRef");
            }
            break;
        case ClauseType::Follows:
        case ClauseType::FollowsStar:
        case ClauseType::Parent:
        case ClauseType::ParentStar:
            // check left
            if (!leftRef.isOfStmtRef()) {
                throw SyntaxException("Invalid LHS, stmtRef expected");
            }
            // check right
            if (!rightRef.isOfStmtRef()) {
                throw SyntaxException("Invalid RHS, stmtRef expected");
            }
            break;
        default:
            throw SyntaxException("Invalid ClauseType in Such That Clause");
    }
}

void PQLParser::validateSuchThatSemantics(Query& query, const std::shared_ptr<SuchThatClause> clause) {
    if (!clause) {
        return;
    }
    std::shared_ptr<SynonymHandler> synonymHandler = std::make_shared<SynonymHandler>();
    std::shared_ptr<StmtrefStmtrefHandler> stmtrefHandler = std::make_shared<StmtrefStmtrefHandler>();
    std::shared_ptr<StmtrefEntrefHandler> stmtEntHandler = std::make_shared<StmtrefEntrefHandler>();
    std::shared_ptr<EntrefEntrefHandler> entrefHandler = std::make_shared<EntrefEntrefHandler>();
    synonymHandler->setNext(stmtrefHandler)->setNext(stmtEntHandler)->setNext(entrefHandler);
    synonymHandler->handle(query, clause);
    query.addSuchThat(clause);
}

std::shared_ptr<Token> PQLParser::expect(bool isToken, const std::string& errorMsg) {
    if (!isToken) {
        throw SyntaxException(errorMsg);
    }
    return tokenizer->popToken();
}

std::shared_ptr<QueryEntity> PQLParser::extractQueryEntity(std::shared_ptr<Token> entityType) {
    std::shared_ptr<Token> synonym = tokenizer->popToken();
    if (!synonym->isIdent()) {
        throw SyntaxException("Invalid synonym");
    }
    EntityPtr newEntity = std::make_shared<QueryEntity>(entityType, synonym->getRep());
    return newEntity;
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
        throw SyntaxException("Invalid Ref");
    }

    ref.setRep(refString);
    ref.setRootType(rootType);
    return ref;
}

void PQLParser::validatePatternSyntax(std::shared_ptr<PatternClause> clause) {
    std::shared_ptr<Token> patternSyn = tokenizer->popToken();
    if (!patternSyn->isIdent()) {
        throw SyntaxException("Invalid synonym syntax");
    }
    clause->setSyn(patternSyn->getRep());

    std::shared_ptr<Token> next = tokenizer->popToken();
    if (!next->isToken(TokenType::Lparenthesis)) {
        throw SyntaxException("Expected Lparenthesis");
    }

    Ref firstParam = extractRef();
    if (firstParam.getRootType() == RootType::Integer) {
        throw SyntaxException("Invalid entRef");
    }
    clause->setFirstParam(firstParam);

    next = tokenizer->popToken();
    if (!next->isToken(TokenType::Comma)) {
        throw SyntaxException("Expected comma ");
    }

    try {
        ExpressionSpec secondParam = exprSpecParser->extractExpressionSpec();
        clause->setSecondParam(secondParam);
    } catch (...) {
        throw SyntaxException("Invalid expression spec syntax");
    }

    next = tokenizer->popToken();
    if (!next->isToken(TokenType::Rparenthesis)) {
        throw SyntaxException("expected right parenthesis");
    }
}

void PQLParser::validatePatternSemantics(Query& query, const std::shared_ptr<PatternClause> clause) {
    if (!clause) {
        return;
    }
    std::shared_ptr<SynonymHandler> synonymHandler = std::make_shared<SynonymHandler>();
    std::shared_ptr<EntrefExprSpecHandler> EntExprHandler = std::make_shared<EntrefExprSpecHandler>();
    synonymHandler->setNext(EntExprHandler);
    synonymHandler->handle(query, clause);
    query.addPattern(clause);
}
