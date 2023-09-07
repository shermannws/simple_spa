#include "SuchThatClause.h"

SuchThatClause::SuchThatClause() = default;

void SuchThatClause::setType(RelationshipType t) {
    this->type = t;
}

void SuchThatClause::setLeftRef(Ref& ref) {
    this->left_ref = ref;
}

void SuchThatClause::setRightRef(Ref& ref) {
    this->right_ref = ref;
}

RelationshipType SuchThatClause::getType() {
    return this->type;
}

Ref SuchThatClause::getLeftRef() {
    return this->left_ref;
}

Ref SuchThatClause::getRightRef() {
    return this->right_ref;
}