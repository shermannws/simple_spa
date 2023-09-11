#pragma once

#include "QueryEntity.h"
#include "Ref.h"
#include <string>

enum class ClauseType {
    Uses,
    Follows,
    FollowsStar,
    If,
    Invalid
};

class Clause {
private:
    ClauseType type;
    Ref firstParam;

public:
    explicit Clause();
    virtual ~Clause() = default;

    void setType(ClauseType type);

    ClauseType getType();

    void setFirstParam(Ref& ref);
    Ref getFirstParam();
};

