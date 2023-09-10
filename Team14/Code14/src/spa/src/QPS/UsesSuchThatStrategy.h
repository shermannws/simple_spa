#pragma once

#include "Strategy.h"

class UsesSuchThatStrategy : public Strategy {
public:
    Result evaluateClause(Query& query, std::shared_ptr<PkbReader> pkbReader) const override;
};
