
#pragma once

#include <list>
#include <string>
#include "Result.h"
#include "Query.h"

class QueryEvaluator {
//private:
//    std::list<std::string> formatResult(Query& query, Result& result);
public:
    QueryEvaluator();
    std::list<std::string> formatResult(Query& query, Result& result);
};
