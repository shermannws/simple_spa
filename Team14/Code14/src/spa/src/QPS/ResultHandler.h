#pragma once

#include <list>
#include <string>

#include "Result.h"
#include "Query.h"

class ResultHandler {
private:
    Result join(Result& r1, Result& r2);
    std::unordered_map<int, int> getCommonColumns(Result& r1, Result& r2);
    SynonymMap buildSynIndices(Result& r1, Result& r2);
    std::vector<Synonym> getHeader(SynonymMap);
    bool isMatch(const std::vector<Entity>& row1, const std::vector<Entity>& row2, const std::unordered_map<int, int>& commons);

public:
    explicit ResultHandler();
    Result getCombined(Result& r1, Result& r2);
};


