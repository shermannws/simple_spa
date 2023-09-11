#pragma once

#include "Strategy.h"
#include "SuchThatClause.h"

class FollowsSuchThatStrategy : public Strategy {
public:
    Result evaluateClause(Clause& clause, std::shared_ptr<PkbReader> pkbReader) const override;
};
