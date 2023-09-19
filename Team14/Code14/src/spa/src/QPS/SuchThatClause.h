#pragma once

#include "QueryEntity.h"
#include "Clause.h"
#include "Ref.h"
#include "Token.h"
#include <string>


class SuchThatClause : public Clause {
private:
    Ref secondParam;

public:
    SuchThatClause();
    explicit SuchThatClause(const std::shared_ptr<Token>& token);
    void setSecondParam(Ref& ref);
    Ref& getSecondParam();

};
