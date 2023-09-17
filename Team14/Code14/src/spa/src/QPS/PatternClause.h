#pragma once

#include <memory>

#include "Clause.h"

class PatternClause :  public Clause {
private:
    ExpressionSpec secondParam;
    EntityPtr entity;

public:
    PatternClause();
    void setSecondParam(ExpressionSpec & expr);
    ExpressionSpec getSecondParam();
    void setEntity(EntityPtr ent);
    EntityPtr getEntity();
};
