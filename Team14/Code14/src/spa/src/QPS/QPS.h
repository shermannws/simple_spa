#pragma once

#include "PKB/Pkb.h"
#include <list>

class QPS {
public:
    static void evaluate(std::shared_ptr<PkbReader> pkbReader, std::string& query, std::list<std::string>& results);
};