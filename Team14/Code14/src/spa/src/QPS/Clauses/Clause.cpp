#include "Clause.h"

Clause::Clause() : negation(false) {}

void Clause::setType(ClauseType clauseType) { type = clauseType; }

ClauseType Clause::getType() { return type; }

void Clause::setNegation(bool isNegated) { negation = isNegated; }

bool Clause::isNegation() { return negation; }

void Clause::setFirstParam(Ref &ref) { firstParam = ref; }

Ref &Clause::getFirstParam() { return firstParam; }