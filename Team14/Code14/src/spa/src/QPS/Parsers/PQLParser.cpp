#include <stack>
#include <string>

#include "PQLParser.h"
#include "QPS/Clauses/SuchThatClause.h"
#include "QPS/Exceptions/SyntaxException.h"
#include "QPS/QPSUtil.h"
#include "SemanticValidator/PqlSemanticValidator.h"
#include "Tokenizer.h"

using processClausefunc = std::function<void(Query &query)>;

PQLParser::PQLParser(const std::string &PQLQuery) {
    tokenizer = std::make_shared<Tokenizer>(PQLQuery);
    exprSpecParser = std::make_shared<ExprSpecParser>(tokenizer);
}

Query PQLParser::parse() {
    Query query = Query();
    std::vector<Synonym> declarations = parseDeclarations(query);
    parseResultClause(query);
    parseClauses(query);

    PqlSemanticValidator semanticValidator = PqlSemanticValidator();
    semanticValidator.validateDeclarations(declarations);
    semanticValidator.validateResultClause(query);
    semanticValidator.validateConstraintClauses(query);
    return query;
}

std::vector<Synonym> PQLParser::parseDeclarations(Query &query) {
    std::vector<Synonym> synonyms;
    while (tokenizer->peekToken()->isDesignEntity()) {
        std::shared_ptr<Token> designEntity = tokenizer->peekToken();
        do {
            tokenizer->popToken();// consume designEntity or comma
            EntityPtr newEntity = extractQueryEntity(designEntity);
            query.addDeclaration(newEntity);
            synonyms.push_back(newEntity->getSynonym());
        } while (tokenizer->peekToken()->isToken(TokenType::Comma));

        std::shared_ptr<Token> endToken = tokenizer->popToken();// consume semicolon
        if (!endToken->isToken(TokenType::Semicolon)) {
            throw SyntaxException("Expected ; but found '" + endToken->getRep() + +"'");
        }
    }
    return synonyms;
}


void PQLParser::parseResultClause(Query &query) {
    std::unordered_map<TokenType, processClausefunc> resultExtractorMap{
            {TokenType::Word, [&](Query &query) { return processElem(query); }},
            {TokenType::Ltuple, [&](Query &query) { return processTuple(query); }}};

    std::shared_ptr<Token> next = tokenizer->popToken();
    if (!next->isToken("Select")) {
        throw SyntaxException("Expected Select clause but found '" + next->getRep() + "'");
    }

    next = tokenizer->peekToken();
    if (!next->isIdent() && !next->isToken(TokenType::Ltuple)) { throw SyntaxException("Invalid synonym syntax"); }

    resultExtractorMap[next->getType()](query);
}

void PQLParser::processTuple(Query &query) {
    query.setMultiTupleResult();
    tokenizer->popToken();// consume Ltuple
    processElem(query);   // expect non-empty list

    while (tokenizer->peekToken()->isToken(TokenType::Comma)) {
        tokenizer->popToken();// consume comma
        processElem(query);
    }

    auto rTuple = tokenizer->popToken();// consume Rtuple
    if (!rTuple->isToken(TokenType::Rtuple)) { throw SyntaxException("Expected closing tuple bracket"); }
}

void PQLParser::processElem(Query &query) {
    auto syn = tokenizer->popToken();// expect Syn
    if (!syn->isIdent()) { throw SyntaxException("invalid synonym in elem"); }

    auto next = tokenizer->peekToken();// check following token

    if (next->isToken(TokenType::Dot)) {
        tokenizer->popToken();                // consume dot
        auto attrName = tokenizer->popToken();// expect attrName
        if (!attrName->isAttrName()) { throw SyntaxException("invalid attrName found"); }
        Synonym elem = syn->getRep().append(".").append(attrName->getRep());
        query.addSelect(elem);
        return;
    }
    query.addSelect(syn->getRep());
}

void PQLParser::parseClauses(Query &query) {
    std::unordered_map<std::string, processClausefunc> clauseExtractorMap{
            {"such that", [&](Query &query) { return processSuchThatClause(query); }},
            {"pattern", [&](Query &query) { return processPatternClause(query); }},
            {"with", [&](Query &query) { return processWithClause(query); }}};

    while (!tokenizer->peekToken()->isToken(TokenType::Empty)) {
        std::string clauseConnector = tokenizer->peekToken()->getRep();
        if (clauseExtractorMap.find(clauseConnector) == clauseExtractorMap.end()) {// check if valid clause keyword
            throw SyntaxException("invalid clause connector");
        }

        do {
            tokenizer->popToken();// consume connector
            clauseExtractorMap[clauseConnector](query);
        } while (tokenizer->peekToken()->isToken("and"));
    }
}

void PQLParser::processSuchThatClause(Query &query) {
    std::shared_ptr<SuchThatClause> clause = extractSuchThatClause();
    query.addClause(clause);
}

void PQLParser::processPatternClause(Query &query) {
    std::shared_ptr<PatternClause> clause = extractPatternClause();
    query.addClause(clause);
}

void PQLParser::processWithClause(Query &query) {
    std::shared_ptr<WithClause> clause = extractWithClause();
    query.addClause(clause);
}

std::shared_ptr<SuchThatClause> PQLParser::extractSuchThatClause() {
    std::shared_ptr<Token> absToken = tokenizer->popToken();
    std::shared_ptr<SuchThatClause> clause = std::make_shared<SuchThatClause>(absToken);

    std::shared_ptr<Token> next = tokenizer->popToken();
    if (!next->isToken(TokenType::Lparenthesis)) { throw SyntaxException("No left parenthesis"); }

    Ref leftRef = extractRef();
    clause->setFirstParam(leftRef);

    next = tokenizer->popToken();
    if (!next->isToken(TokenType::Comma)) { throw SyntaxException("No comma"); }

    Ref rightRef = extractRef();
    clause->setSecondParam(rightRef);

    next = tokenizer->popToken();
    if (!next->isToken(TokenType::Rparenthesis)) { throw SyntaxException("No right parenthesis"); }

    validateSuchThatRefType(clause);
    return clause;
}

std::shared_ptr<PatternClause> PQLParser::extractPatternClause() {
    std::shared_ptr<PatternClause> clause = std::make_shared<PatternClause>();
    std::shared_ptr<Token> patternSyn = tokenizer->popToken();
    if (!patternSyn->isIdent()) { throw SyntaxException("Invalid synonym syntax"); }
    clause->setSyn(patternSyn->getRep());

    std::shared_ptr<Token> next = tokenizer->popToken();
    if (!next->isToken(TokenType::Lparenthesis)) { throw SyntaxException("Expected Lparenthesis"); }

    Ref firstParam = extractRef();
    if (firstParam.getRootType() == RootType::Integer) { throw SyntaxException("Invalid entRef"); }
    clause->setFirstParam(firstParam);

    next = tokenizer->popToken();
    if (!next->isToken(TokenType::Comma)) { throw SyntaxException("Expected comma "); }

    try {
        ExpressionSpec secondParam = exprSpecParser->extractExpressionSpec();
        clause->setSecondParam(secondParam);
    } catch (...) { throw SyntaxException("Invalid expression spec syntax"); }

    next = tokenizer->popToken();
    if (next->isToken(TokenType::Comma)) {
        next = tokenizer->popToken();
        if (!next->isToken(TokenType::Underscore)) {
            throw SyntaxException("Invalid pattern syntax, expected underscore");
        }
        next = tokenizer->popToken();
        clause->setThirdParam(true);
    }

    if (!next->isToken(TokenType::Rparenthesis)) { throw SyntaxException("Expected right parenthesis"); }

    validatePatternStructure(clause);
    return clause;
}

std::shared_ptr<WithClause> PQLParser::extractWithClause() {
    std::shared_ptr<WithClause> clause = std::make_shared<WithClause>();
    Ref leftRef = extractRef();
    clause->setFirstParam(leftRef);
    std::shared_ptr<Token> next = tokenizer->popToken();
    if (!next->isToken(TokenType::Equal)) { throw SyntaxException("No equal sign"); }
    Ref rightRef = extractRef();
    clause->setSecondParam(rightRef);
    validateWithRefType(leftRef, rightRef);
    return clause;
}

void PQLParser::validatePatternStructure(const std::shared_ptr<PatternClause> clause) {
    if (clause->hasThirdParam()) {
        ExpressionSpec spec = clause->getSecondParam();
        if (spec.first != ExpressionSpecType::Wildcard) {
            throw SyntaxException("Invalid pattern structure, wildcard as second param expected");
        }
    }
}

void PQLParser::validateSuchThatRefType(const std::shared_ptr<SuchThatClause> clause) {
    ClauseType type = clause->getType();
    Ref &leftRef = clause->getFirstParam();
    Ref &rightRef = clause->getSecondParam();

    switch (type) {
        case ClauseType::Uses:
        case ClauseType::Modifies:
            // check right
            if (!rightRef.isOfEntRef()) { throw SyntaxException("Invalid RHS entRef"); }
            break;
        case ClauseType::Follows:
        case ClauseType::FollowsStar:
        case ClauseType::Parent:
        case ClauseType::ParentStar:
        case ClauseType::Next:
        case ClauseType::NextStar:
            // check left
            if (!leftRef.isOfStmtRef()) { throw SyntaxException("Invalid LHS, stmtRef expected"); }
            // check right
            if (!rightRef.isOfStmtRef()) { throw SyntaxException("Invalid RHS, stmtRef expected"); }
            break;
        case ClauseType::Calls:
        case ClauseType::CallsStar:
            if (!leftRef.isOfEntRef()) { throw SyntaxException("Invalid LHS entRef"); }
            if (!rightRef.isOfEntRef()) { throw SyntaxException("Invalid RHS entRef"); }
            break;
        default:
            throw SyntaxException("Invalid ClauseType in Such That Clause");
    }
}

void PQLParser::validateWithRefType(Ref &leftRef, Ref &rightRef) {
    if (!leftRef.isOfWithRef()) { throw SyntaxException("Invalid LHS withRef"); }

    if (!rightRef.isOfWithRef()) { throw SyntaxException("Invalid RHS withRef"); }
}

std::shared_ptr<QueryEntity> PQLParser::extractQueryEntity(std::shared_ptr<Token> entityType) {
    std::shared_ptr<Token> synonym = tokenizer->popToken();
    if (!synonym->isIdent()) { throw SyntaxException("Invalid synonym"); }
    EntityPtr newEntity = std::make_shared<QueryEntity>(entityType, synonym->getRep());
    return newEntity;
}

Ref PQLParser::extractRef() {
    Ref ref;
    RootType rootType;
    std::string refString;
    std::shared_ptr<Token> curr = tokenizer->peekToken();
    if (curr->isInteger()) {// INTEGER
        refString = tokenizer->popToken()->getRep();
        rootType = RootType::Integer;
    } else if (curr->isToken(TokenType::Quote)) {// IDENTITY
        tokenizer->popToken();
        std::shared_ptr<Token> syn = tokenizer->peekToken();
        expect(syn->isIdent(), "Identity invalid");
        std::string right_quote = tokenizer->peekToken()->getRep();
        expect(tokenizer->peekToken()->isToken(TokenType::Quote), "No right quote");

        refString = syn->getRep();
        rootType = RootType::Ident;
    } else if (curr->isToken(TokenType::Underscore)) {// WILDCARD
        refString = tokenizer->popToken()->getRep();
        rootType = RootType::Wildcard;
    } else if (curr->isToken(TokenType::Word) && curr->isIdent()) {// SYNONYM
        refString = tokenizer->popToken()->getRep();
        curr = tokenizer->peekToken();
        if (curr->isToken(TokenType::Dot)) {
            tokenizer->popToken();// consume dot
            curr = expect(tokenizer->peekToken()->isAttrName(), "Invalid attrName");
            ref.setAttrName(curr->getRep());
            rootType = RootType::AttrRef;
        } else {
            rootType = RootType::Synonym;
        }
    } else {
        throw SyntaxException("Invalid Ref");
    }

    ref.setRep(refString);
    ref.setRootType(rootType);
    return ref;
}

std::shared_ptr<Token> PQLParser::expect(bool isToken, const std::string &errorMsg) {
    if (!isToken) { throw SyntaxException(errorMsg); }
    return tokenizer->popToken();
}
