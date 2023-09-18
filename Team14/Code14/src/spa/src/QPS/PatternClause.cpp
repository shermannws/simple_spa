#include "PatternClause.h"

PatternClause::PatternClause() : Clause() {};

void PatternClause::setSecondParam(ExpressionSpec & expr) {
    secondParam = expr;
}

ExpressionSpec PatternClause::getSecondParam() {
    return secondParam;
}

void PatternClause::setSyn(Synonym synonym) {
    syn = synonym;
}

Synonym PatternClause::getSyn() {
    return syn;
}