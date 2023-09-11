#include "SuchThatClause.h"

SuchThatClause::SuchThatClause() = default;

void SuchThatClause::setType(RelationshipType t) {
    type = t;
}

void SuchThatClause::setLeftRef(Ref& ref) {
    leftRef = ref;
}

void SuchThatClause::setRightRef(Ref& ref) {
    rightRef = ref;
}

RelationshipType SuchThatClause::getType() {
    return type;
}

Ref SuchThatClause::getLeftRef() {
    return leftRef;
}

Ref SuchThatClause::getRightRef() {
    return rightRef;
}