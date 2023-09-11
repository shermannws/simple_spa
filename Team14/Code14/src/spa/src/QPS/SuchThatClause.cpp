#include "SuchThatClause.h"

SuchThatClause::SuchThatClause() {};

void SuchThatClause::setSecondParam(Ref& ref) {
    secondParam = ref;
}

Ref SuchThatClause::getSecondParam() {
    return secondParam;
}
