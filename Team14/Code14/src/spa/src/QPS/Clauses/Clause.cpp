#include "Clause.h"

Clause::Clause() : negation(false) {}

void Clause::setType(ClauseType clauseType) { type = clauseType; }

ClauseType Clause::getType() { return type; }

void Clause::setNegation(bool isNegated) { negation = isNegated; }

bool Clause::isNegation() { return negation; }

void Clause::setFirstParam(Ref &ref) { firstParam = ref; }

Ref &Clause::getFirstParam() { return firstParam; }

bool Clause::operator==(const Clause &other) const {
    return type == other.type && negation == other.negation && firstParam == other.firstParam && isEqual(other);
}

bool std::equal_to<std::shared_ptr<Clause>>::operator()(std::shared_ptr<Clause> const &lhs,
                                                        std::shared_ptr<Clause> const &rhs) const {
    return *lhs == *rhs;
}
