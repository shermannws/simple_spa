#pragma once

#include <list>
#include <string>

#include "Result.h"
#include "Query.h"
#include "ClauseHandler.h"
#include "./PKB/PkbReader.h"

class PQLEvaluator {
private:
    std::shared_ptr<PkbReader> pkbReader;
    std::shared_ptr<ClauseHandler> clauseHandler;
    std::vector<Entity> getAll(const std::shared_ptr<QueryEntity>& queryEntity);

public:
    explicit PQLEvaluator(std::shared_ptr<PkbReader> pkbReader);
    Result evaluate(Query&);
    std::list<std::string> formatResult(Query& query, Result& result); // TODO: to set as private in the future
};