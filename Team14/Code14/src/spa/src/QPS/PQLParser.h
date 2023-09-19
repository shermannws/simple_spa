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
    void validateSuchThatSyntax(SuchThatClause& clause);
    void validateSuchThatSemantics(Query& query, SuchThatClause& clause);
    void validateSuchThatRefType(SuchThatClause& clause);
    bool isOfStmtType(QueryEntityType entityType);
    bool isOfUsesEntityType(QueryEntityType entityType);
    bool isOfModifiesEntityType(QueryEntityType entityType);
public:
    explicit PQLParser(const std::string& str);
    Query parse();
};