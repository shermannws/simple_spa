#pragma once

#include <string>

#include "Query.h"
#include "Tokenizer.h"
#include "Entity.h"

class PQLParser {
public:
    explicit PQLParser(const std::string& str);
    Query parse();

private:
    std::shared_ptr<Tokenizer> tokenizer;
    void processDeclarations(Query& query);
    void processSelectClause(Query& query);
    //void processSuchThatClause(Query& query);
    //void processPatternClause(Query& query);
};
