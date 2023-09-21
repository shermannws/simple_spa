#pragma once

#include <string>
#include <utility>

#include "Query.h"
#include "Tokenizer.h"
#include "QueryEntity.h"

class PQLParser {
private:
    std::shared_ptr<Tokenizer> tokenizer;
    void processDeclarations(Query& query);
    void processSelectClause(Query& query);
    void processSuchThatClause(Query& query);
    void processPatternClause(Query& query);
    std::shared_ptr<Token> expect(bool isToken, const std::string& errorMsg);
    Ref extractRef();
    void validateSuchThatSyntax(std::shared_ptr<SuchThatClause>& clause);
    void validateSuchThatSemantics(Query& query, const std::shared_ptr<SuchThatClause>& clause);
    void validateSuchThatRefType(const std::shared_ptr<SuchThatClause>& clause);
    void validatePatternSyntax(std::shared_ptr<PatternClause>& clause);
    void validatePatternSemantics(Query& query, const std::shared_ptr<PatternClause>& clause);

    //Expr spec methods
    Expression extractExpression();
    ExpressionSpec extractExpressionSpec();
    bool validateExprSyntax(std::vector<std::shared_ptr<Token>>& input);
    bool isExpr(std::vector<std::shared_ptr<Token>>& input, size_t& index);
    bool isTerm(std::vector<std::shared_ptr<Token>>& input, size_t& index);
    bool isFactor(std::vector<std::shared_ptr<Token>>& input, size_t& index);
public:
    explicit PQLParser(const std::string& PQLQuery);
    Query parse();
};
