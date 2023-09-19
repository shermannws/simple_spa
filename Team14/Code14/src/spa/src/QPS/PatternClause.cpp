#include "PatternClause.h"

PatternClause::PatternClause() : Clause() {};

void PatternClause::setSecondParam(Ref& ref) {
    secondParam = ref;
}

Ref& PatternClause::getSecondParam() {
    return secondParam;
}

void PatternClause::setEntity(std::shared_ptr<QueryEntity> ent) {
    entity = ent;
}

std::shared_ptr<QueryEntity> PatternClause::getEntity() {
    return entity;
};