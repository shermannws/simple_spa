#pragma once

#include "Result.h"
#include "Query.h"
#include "ClauseHandler.h"
#include "./PKB/PkbReader.h"

class PQLEvaluator {
private:
    std::shared_ptr<PkbReader> pkbReader;
    std::shared_ptr<ClauseHandler> clauseHandler;

    std::shared_ptr<std::vector<std::shared_ptr<Entity>>> getAll(std::shared_ptr<QueryEntity> queryEntity);

public:
    explicit PQLEvaluator(std::shared_ptr<PkbReader> pkbReader);
    Result Evaluate(Query&);
};