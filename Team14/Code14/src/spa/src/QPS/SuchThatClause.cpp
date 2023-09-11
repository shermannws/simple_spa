#include "SuchThatClause.h"

SuchThatClause::SuchThatClause() = default;

void SuchThatClause::setType(ClauseType t) {
    type = t;
}

void SuchThatClause::setLeftRef(Ref& ref) {
    leftRef = ref;
}

void SuchThatClause::setRightRef(Ref& ref) {
    rightRef = ref;
}

ClauseType SuchThatClause::getType() {
    return type;
}

Ref SuchThatClause::getLeftRef() {
    return leftRef;
}

Ref SuchThatClause::getRightRef() {
    return rightRef;
}