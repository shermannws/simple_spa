#pragma once

#include "Clause.h"

class PatternClause :  public Clause {
private:
    Ref secondParam; //TODO support expression spec
    std::shared_ptr<QueryEntity> entity;

public:
    PatternClause();
    void setSecondParam(Ref& ref);
    Ref getSecondParam();
    void setEntity(std::shared_ptr<QueryEntity> ent);
    std::shared_ptr<QueryEntity> getEntity();
};
