#include "PatternClause.h"

#include <utility>

PatternClause::PatternClause() : Clause() {
    this->setType(ClauseType::Assign);
};

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

bool PatternClause::operator==(const Clause& other) const {
    try {
        const auto& otherPattern = dynamic_cast<const PatternClause&>(other);
        return (type == otherPattern.type) &&
               (firstParam == otherPattern.firstParam) &&
               (secondParam==otherPattern.secondParam) &&
               (syn == otherPattern.syn);
    } catch (std::bad_cast& e) {
       return false;
    }
}
