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
    Ref extractStmtRef(Query& query);
    Ref extractEntRef(Query& query);
    void processSuchThatBody(Query& query, SuchThatClause& clause);
    void processSuchThatLeft(Query &query, SuchThatClause& clause);
    void processSuchThatRight(Query &query, SuchThatClause& clause);
    void validateSuchThatSemantics(Query &query, SuchThatClause& clause);
    bool isOfStmtType(QueryEntityType entityType);
public:
    explicit PQLParser(const std::string& PQLQuery);
    Query parse();
};