#include "Clause.h"

Clause::Clause() {}

void Clause::setType(ClauseType type) {
    this->type = type;
}

ClauseType Clause::getType() {
   return type;
}

void Clause::setFirstParam(Ref& ref) {
    this->firstParam = ref;
}

Ref Clause::getFirstParam() {
    return firstParam;
}
