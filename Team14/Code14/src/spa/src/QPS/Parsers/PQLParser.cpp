#include <string>
#include <stack>

#include "PQLParser.h"
#include "Tokenizer.h"
#include "QPS/Clauses/SuchThatClause.h"
#include "SemanticValidator/PqlSemanticValidator.h"
#include "QPS/QPSUtil.h"
#include "QPS/Exceptions/SyntaxException.h"

using processClausefunc = std::function<void(Query& query)>;

PQLParser::PQLParser(const std::string& PQLQuery) {
    tokenizer = std::make_shared<Tokenizer>(PQLQuery);
    exprSpecParser = std::make_shared<ExprSpecParser>(tokenizer);
}

Query PQLParser::parse() {
    Query query = Query();
    std::vector<Synonym> declarations = parseDeclarations(query);
    Synonym select = parseResultClause(query);
    parseClauses(query);

    PqlSemanticValidator semanticValidator = PqlSemanticValidator();
    semanticValidator.validateDeclarations(declarations);
    semanticValidator.validateResultClause(query, select);
    semanticValidator.validateConstraintClauses(query);
    return query;
}

std::vector<Synonym> PQLParser::parseDeclarations(Query& query) {
    std::vector<Synonym> synonyms;
    while(tokenizer->peekToken()->isDesignEntity()) {
        std::shared_ptr<Token> designEntity = tokenizer->peekToken();
        do {
            tokenizer->popToken(); //consume designEntity or comma
            EntityPtr newEntity = extractQueryEntity(designEntity);
            query.addDeclaration(newEntity);
            synonyms.push_back(newEntity->getSynonym());
        } while (tokenizer->peekToken()->isToken(TokenType::Comma));

        std::shared_ptr<Token> endToken = tokenizer->popToken(); // consume semicolon
        if (!endToken->isToken(TokenType::Semicolon)) {
            throw SyntaxException("Expected ; but found '" + endToken->getRep() + + "'");
        }
    }
    return synonyms;
}

Synonym PQLParser::parseResultClause(Query& query) {
    std::shared_ptr<Token> next = tokenizer->popToken();
    if (!next->isToken("Select")) {
        throw SyntaxException("Expected Select clause but found '" + next->getRep() + "'");
    }

    next = tokenizer->popToken();
    if (!next->isIdent()) {
        throw SyntaxException("Invalid synonym syntax");
    }

    Synonym syn = next->getRep();
    query.addSelect(next->getRep());
    return syn;
}

void PQLParser::parseClauses(Query& query) {
    std::unordered_map<std::string, processClausefunc> clauseExtractorMap {
            {"such that",  [&] (Query& query) {return processSuchThatClause(query);}},
            {"pattern",  [&] (Query& query) {return processPatternClause(query);}}
    };

    while(!tokenizer->peekToken()->isToken(TokenType::Empty)) {
        std::string clauseConnector = tokenizer->peekToken()->getRep();
        if (clauseExtractorMap.find(clauseConnector) == clauseExtractorMap.end()) { //check if valid clause keyword
            throw SyntaxException("invalid clause connector");
        }

        do {
            tokenizer->popToken(); //consume connector
            clauseExtractorMap[clauseConnector](query);
        } while (tokenizer->peekToken()->isToken("and"));
    }
}

void PQLParser::processSuchThatClause(Query& query) {
    std::shared_ptr<SuchThatClause> clause = extractSuchThatClause();
    query.addClause(clause);
}

void PQLParser::processPatternClause(Query& query) {
    std::shared_ptr<PatternClause> clause = extractPatternClause();
    query.addClause(clause);
}

std::shared_ptr<SuchThatClause> PQLParser::extractSuchThatClause() {
    std::shared_ptr<Token> absToken = tokenizer->popToken();
    std::shared_ptr<SuchThatClause> clause = std::make_shared<SuchThatClause>(absToken);

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
    return clause;
}

std::shared_ptr<PatternClause> PQLParser::extractPatternClause() {
    std::shared_ptr<PatternClause> clause = std::make_shared<PatternClause>();
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
    return clause;
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
            // check left
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

std::shared_ptr<Token> PQLParser::expect(bool isToken, const std::string& errorMsg) {
    if (!isToken) {
        throw SyntaxException(errorMsg);
    }
    return tokenizer->popToken();
}
