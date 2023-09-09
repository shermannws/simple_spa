#pragma once

#include <string>

#include "Query.h"

class PQLParser {
private:
    std::string pql;
    void processDeclarations(Query& query);
    void processSelectClause(Query& query);
    void processSuchThatClause(Query& query);
    void processPatternClause(Query& query);

public:
    explicit PQLParser(const std::string& str) : pql(str) {}
    Query parse();
};
