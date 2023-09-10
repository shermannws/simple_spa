#pragma once

#include <string>

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
    bool isDesignEntity(std::shared_ptr<Token> token);

public:
    explicit PQLParser(const std::string& str);
    Query parse();
};
