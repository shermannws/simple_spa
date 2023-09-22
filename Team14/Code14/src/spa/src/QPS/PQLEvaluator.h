#pragma once

#include <list>
#include <string>

#include "Result.h"
#include "Query.h"
#include "ClauseHandler.h"
#include "ResultHandler.h"
#include "./PKB/PkbReader.h"
#include "QPSTypes.h"

class PQLEvaluator {
private:
    std::shared_ptr<PkbReader> pkbReader;
    std::shared_ptr<ClauseHandler> clauseHandler;
    std::shared_ptr<ResultHandler> resultHandler;
    std::vector<Entity> getAll(const EntityPtr& queryEntity);

public:
    explicit PQLEvaluator(std::shared_ptr<PkbReader> pkbReader);
    Result evaluate(Query&);
    ResultList formatResult(Query& query, Result& result); // TODO: to set as private in the future
};