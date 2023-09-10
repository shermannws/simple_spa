#pragma once

#include "Strategy.h"

class FollowsSuchThatStrategy : public Strategy {
public:
    Result evaluateClause(Query& query, std::shared_ptr<PkbReader> pkbReader) const override;
};
