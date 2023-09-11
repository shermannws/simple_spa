#pragma once

#include <list>
#include <string>
#include "Result.h"
#include "Query.h"

class PQLEvaluator {
public:
    PQLEvaluator();
    std::list<std::string> formatResult(Query& query, Result& result); // TODO: to set as private in the future
};
