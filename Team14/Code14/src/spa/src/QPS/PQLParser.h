#pragma once

#include <string>
#include <utility>

#include "Query.h"
#include "Tokenizer.h"
#include "QueryEntity.h"
#include "ExprSpecParser.h"

class PQLParser {
private:
    std::shared_ptr<Tokenizer> tokenizer;
    std::shared_ptr<ExprSpecParser> exprSpecParser;

    void processDeclarations(Query& query);
    void processSelectClause(Query& query);
    void processSuchThatClause(Query& query);
    void processPatternClause(Query& query);
    std::shared_ptr<Token> expect(bool isToken, const std::string& errorMsg);
    Ref extractRef();
    void validateSuchThatSyntax(std::shared_ptr<SuchThatClause> clause);
    void validateSuchThatSemantics(Query& query, const std::shared_ptr<SuchThatClause> clause);
    void validateSuchThatRefType(const std::shared_ptr<SuchThatClause> clause);
    void validatePatternSyntax(std::shared_ptr<PatternClause> clause);
    void validatePatternSemantics(Query& query, const std::shared_ptr<PatternClause> clause);

public:
    explicit PQLParser(const std::string& PQLQuery);
    Query parse();
};
