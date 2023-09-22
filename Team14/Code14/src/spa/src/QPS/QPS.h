#pragma once

#include "PKB/Pkb.h"
#include <list>

class QPS {
private:
    std::shared_ptr<PkbReader> pkbReader;
public:
    explicit QPS(std::shared_ptr<PkbReader> pkbReader);
    void evaluate(std::string& query, std::list<std::string>& results);
};