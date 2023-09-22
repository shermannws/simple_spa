
#include <string>
#include <stdexcept>
#include <stack>

#include "PQLParser.h"
#include "Tokenizer.h"
#include "SuchThatClause.h"
#include "QPS/SemanticValHandler/SynonymHandler.h"
#include "QPS/SemanticValHandler/StmtrefStmtrefHandler.h"
#include "QPS/SemanticValHandler/StmtrefEntrefHandler.h"
#include "QPS/SemanticValHandler/EntrefExprSpecHandler.h"
#include "QPSUtil.h"
#include "Exception/SyntaxException.h"
#include "Exception/SemanticException.h"


PQLParser::PQLParser(const std::string& PQLQuery) {
    tokenizer = std::make_shared<Tokenizer>(PQLQuery);
    exprSpecParser = std::make_shared<ExprSpecParser>(tokenizer);
}


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
                throw SyntaxException("Expected synonym but found none");
            }
            throw SyntaxException("Invalid synonym '" + synonym->getRep() + "'");
        }
        EntityPtr newEntity = std::make_shared<QueryEntity>(designEntity, synonym->getRep());
        query.addDeclaration(newEntity);

        while(tokenizer->peekToken()->isToken(TokenType::Comma)) {
            tokenizer->popToken(); //consume comma
            synonym = tokenizer->popToken();
            if (!synonym->isIdent()) {
                if (synonym->isToken(TokenType::Empty)) {
                    throw SyntaxException("Expected synonym but found none");
                }
                throw SyntaxException("Invalid synonym '" + synonym->getRep() + "'");
            }
            newEntity = std::make_shared<QueryEntity>(designEntity, synonym->getRep());
            query.addDeclaration(newEntity);
        }

        // consume semicolon
        std::shared_ptr<Token> endToken = tokenizer->popToken();
        if (!endToken->isToken(TokenType::Semicolon)) {
            throw SyntaxException("Expected ; but found '" + endToken->getRep() + + "'");
        }
    }

    // if no design entity return err
    if (!query.hasDeclarations()) {
        throw SyntaxException("Expected a declaration but found none");
    }
}

void PQLParser::processSelectClause(Query& query) {
    std::shared_ptr<Token> next = tokenizer->popToken();
    if (!next->isToken("Select")) {
        throw SyntaxException("Expected Select clause but found '" + next->getRep() + "'");
    }
    next = tokenizer->popToken();

    if (next->isToken(TokenType::Empty)) {
        throw SyntaxException("Expected synonym but found none");
    }

    EntityPtr entity = query.getEntity(next->getRep());
    if (!entity) {
        throw SemanticException("Undeclared synonym in Select clause");
    }
    query.addSelect(entity);

    // TODO support for multiple synonyms
}

void PQLParser::processSuchThatClause(Query& query) {
    // handle optional
    std::shared_ptr<Token> suchThatToken = tokenizer->peekToken();
    if (!suchThatToken->isToken("such that")) {
        return;
    }
    tokenizer->popToken();
    std::shared_ptr<Token> absToken = tokenizer->popToken();
    std::shared_ptr<SuchThatClause> clause = std::make_shared<SuchThatClause>(absToken);
    validateSuchThatSyntax(clause);
    validateSuchThatSemantics(query, clause);
    query.addSuchThat(clause);
}

void PQLParser::processPatternClause(Query& query) {
    std::shared_ptr<Token> patternToken = tokenizer->peekToken();
    if (!patternToken->isToken("pattern")) {
        return;
    }
    tokenizer->popToken();
    std::shared_ptr<PatternClause> clause = std::make_shared<PatternClause>();
    validatePatternSyntax(clause);
    validatePatternSemantics(query, clause);
    query.addPattern(clause);
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
    RootType leftRootType = leftRef.getRootType();
    RootType rightRootType = rightRef.getRootType();

    switch (type) {
        case ClauseType::Uses:
        case ClauseType::Modifies:
            // check left // TODO: TO DELETE ONCE PROCEDURE IS SUPPORTED
            if (!QPSUtil::isRootOfStmtref(leftRootType)) {
                throw SyntaxException("Invalid LHS stmtRef");
            }

            // check right
            if (!QPSUtil::isRootOfEntref(rightRootType)) {
                throw SyntaxException("Invalid RHS entRef");
            }
            break;
        case ClauseType::Follows:
        case ClauseType::FollowsStar:
        case ClauseType::Parent:
        case ClauseType::ParentStar:
            // check left
            if (!QPSUtil::isRootOfStmtref(leftRootType)) {
                throw SyntaxException("Invalid LHS, stmtRef expected");
            }
            // check right
            if (!QPSUtil::isRootOfStmtref(rightRootType)) {
                throw SyntaxException("Invalid RHS, stmtRef expected");
            }
            break;
        default:
            throw SyntaxException("Invalid ClauseType in Such That Clause");
    }
}

// TODO: generalise this to cater both such that & pattern clauses
void PQLParser::validateSuchThatSemantics(Query& query, const std::shared_ptr<SuchThatClause> clause) {
    std::shared_ptr<SynonymHandler> synonymHandler = std::make_shared<SynonymHandler>();
    std::shared_ptr<StmtrefStmtrefHandler> stmtrefHandler = std::make_shared<StmtrefStmtrefHandler>();
    std::shared_ptr<StmtrefEntrefHandler> stmtEntHandler = std::make_shared<StmtrefEntrefHandler>();
    synonymHandler->setNext(stmtrefHandler)->setNext(stmtEntHandler);
    synonymHandler->handle(query, clause);
}

std::shared_ptr<Token> PQLParser::expect(bool isToken, const std::string& errorMsg) {
    if (!isToken) {
        throw SyntaxException(errorMsg);
    }
    return tokenizer->popToken();
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
    clause->setSyn(patternSyn->getRep());

    std::shared_ptr<Token> next = tokenizer->popToken();
    if (!next->isToken(TokenType::Lparenthesis)) {
        throw SyntaxException("Expected Lparenthesis");
    }

    Ref firstParam = extractRef();
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
    std::shared_ptr<SynonymHandler> synonymHandler = std::make_shared<SynonymHandler>();
    std::shared_ptr<EntrefExprSpecHandler> EntExprHandler = std::make_shared<EntrefExprSpecHandler>();
    synonymHandler->setNext(EntExprHandler);
    synonymHandler->handle(query, clause);
}
