#pragma once

#include "QueryEntity.h"
#include "Clause.h"
#include "Ref.h"
#include <string>

class SuchThatClause : public Clause {
private:
    Ref secondParam;

public:
    SuchThatClause();
    void setSecondParam(Ref& ref);
    Ref getSecondParam();

};
