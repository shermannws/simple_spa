#pragma once

#include <string>
#include <list>

#include "./PKB/PkbReader.h"
#include "PQLParser.h"
#include "PQLEvaluator.h"

class Qps{
public:
    void process(std::string& query, std::list<std::string> &results, std::shared_ptr<PkbReader> pkbReader);
};