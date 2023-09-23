#pragma once

#include <memory>

#include "Clause.h"

class PatternClause :  public Clause {
private:
    ExpressionSpec secondParam;
    Synonym syn;

public:
    PatternClause();
    void setSecondParam(ExpressionSpec& expr);
    ExpressionSpec& getSecondParam();
    void setSyn(Synonym synonym);
    Synonym getSyn();
};
