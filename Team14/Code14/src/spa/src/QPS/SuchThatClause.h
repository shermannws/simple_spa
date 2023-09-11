#pragma once

#include "QueryEntity.h"
#include "Clause.h"
#include "Ref.h"
#include <string>

class SuchThatClause {
private:
    ClauseType type;
    Ref leftRef;
    Ref rightRef;

public:
    SuchThatClause();
    void setType(ClauseType type);
    ClauseType getType();
    void setLeftRef(Ref& ref);
    void setRightRef(Ref& ref);
    Ref getLeftRef();
    Ref getRightRef();

};
