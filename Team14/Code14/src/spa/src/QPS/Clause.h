#pragma once

#include "QueryEntity.h"
#include "Ref.h"
#include <string>

enum class ClauseType {
    UsesSuchThat,
    FollowsSuchThat,
    FollowsStarSuchThat,
    IfPattern,
};

class Clause {
private:
    ClauseType type;
    Ref firstParam;

public:
    explicit Clause();
    void setType(ClauseType type);
    ClauseType getType();
    void setFirstParam(Ref& ref);
    Ref getFirstParam();
};

