#include "PatternClause.h"

PatternClause::PatternClause() : Clause() {};

void PatternClause::setSecondParam(ExpressionSpec & expr) {
    secondParam = expr;
}

ExpressionSpec PatternClause::getSecondParam() {
    return secondParam;
}

void PatternClause::setEntity(EntityPtr ent) {
    entity = ent;
}

EntityPtr PatternClause::getEntity() {
    return entity;
};