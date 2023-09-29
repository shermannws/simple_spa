#include "PatternClause.h"
#include "QPS/Evaluators/Strategies/AssignPatternStrategy.h"

#include <utility>

PatternClause::PatternClause() : Clause() {};

void PatternClause::setSecondParam(ExpressionSpec & expr) {
    secondParam = expr;
}

ExpressionSpec& PatternClause::getSecondParam() {
    return secondParam;
}

void PatternClause::setSyn(Synonym synonym) {
    syn = synonym;
}

Synonym PatternClause::getSyn() {
    return syn;
}

std::shared_ptr<Strategy> PatternClause::createStrategy() {
    if (type == ClauseType::Assign) {
        return std::make_shared<AssignPatternStrategy>(AssignPatternStrategy());
    }
    return nullptr;
}