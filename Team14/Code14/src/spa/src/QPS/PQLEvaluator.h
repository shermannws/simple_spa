#pragma once

#include <list>
#include <string>

#include "Result.h"
#include "Query.h"
#include "ClauseHandler.h"
#include "./PKB/PkbReader.h"
#include "QPSTypes.h"

class PQLEvaluator {
private:
    std::shared_ptr<PkbReader> pkbReader;
    std::shared_ptr<ClauseHandler> clauseHandler;
    std::vector<Entity> getAll(const EntityPtr& queryEntity);

public:
    explicit PQLEvaluator(std::shared_ptr<PkbReader> pkbReader);
    Result evaluate(Query&);
    ResultList formatResult(Query& query, Result& result); // TODO: to set as private in the future
    Result getCombined(Result& r1, Result& r2);

    Result join(Result& r1, Result& r2);
    std::unordered_map<int, int> getCommonColumns(Result& r1, Result& r2);
    SynonymMap buildSynIndices(Result& r1, Result& r2);
    std::vector<Synonym> getHeader(SynonymMap);
    bool isMatch(const std::vector<Entity>& row1, const std::vector<Entity>& row2, const std::unordered_map<int, int>& commons);
};