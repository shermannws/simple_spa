#include "Clause.h"

Clause::Clause() {}

void Clause::setType(ClauseType clauseType) { type = clauseType; }

ClauseType Clause::getType() { return type; }

void Clause::setFirstParam(Ref &ref) { firstParam = ref; }

Ref &Clause::getFirstParam() { return firstParam; }