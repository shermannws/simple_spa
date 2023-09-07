#pragma once

#include <string>
#include <utility>

#include "Query.h"
#include "Tokenizer.h"

class PQLParser {
private:
    std::shared_ptr<Tokenizer> tokenizer;
    void processDeclarations(Query& query);
    void processSelectClause(Query& query);
    void processSuchThatClause(Query& query);
//    void processPatternClause(Query& query);
    std::shared_ptr<Token> expect(bool isToken, const std::string& error_msg);
    Ref extractStmtRef();
    Ref extractEntRef();
    void processSuchThatBody(Query& query, SuchThatClause& clause);
    void processSuchThatLeft(Query &query, SuchThatClause &clause);
    void processSuchThatRight(Query &query, SuchThatClause &clause);
    void validateSuchThatSemantics(Query &query, SuchThatClause &clause);

public:
    explicit PQLParser(const std::string& str);
    Query parse();
};
