#pragma once

#include <string>
#include <utility>

#include "Query.h"
#include "Tokenizer.h"
#include "QueryEntity.h"
#include "ExprSpecParser.h"
#include "QPSTypes.h"

class PQLParser {
private:
    std::shared_ptr<Tokenizer> tokenizer;
    std::shared_ptr<ExprSpecParser> exprSpecParser;

    std::vector<std::shared_ptr<QueryEntity>> processDeclarations();
    Synonym processSelectClause(Query& query);
    std::shared_ptr<SuchThatClause> processSuchThatClause(Query& query);
    std::shared_ptr<PatternClause> processPatternClause(Query& query);

    void validateSuchThatSyntax(std::shared_ptr<SuchThatClause> clause);
    void validateSuchThatRefType(const std::shared_ptr<SuchThatClause> clause);
    void validatePatternSyntax(std::shared_ptr<PatternClause> clause);

    void validateDeclarations(Query& query, const std::vector<std::shared_ptr<QueryEntity>>& entities);
    void validateSelectSemantics(Query& query, const Synonym& syn);
    void validateSuchThatSemantics(Query& query, const std::shared_ptr<SuchThatClause> clause);
    void validatePatternSemantics(Query& query, const std::shared_ptr<PatternClause> clause);

    std::shared_ptr<Token> expect(bool isToken, const std::string& errorMsg);
    Ref extractRef();
    std::shared_ptr<QueryEntity> extractQueryEntity(std::shared_ptr<Token> entityType);

public:
    explicit PQLParser(const std::string& PQLQuery);
    Query parse();
};
