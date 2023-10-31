#include "PatternClause.h"

#include <utility>

PatternClause::PatternClause() : Clause() { this->thirdParam = false; };

void PatternClause::setSecondParam(ExpressionSpec &expr) { secondParam = expr; }

ExpressionSpec &PatternClause::getSecondParam() { return secondParam; }

void PatternClause::setThirdParam(bool exists) { thirdParam = exists; }

bool PatternClause::hasThirdParam() const { return thirdParam; }

void PatternClause::setSyn(Synonym synonym) { syn = synonym; }

Synonym PatternClause::getSyn() { return syn; }

std::vector<Synonym> PatternClause::getSynonyms() const {
    std::vector<Synonym> synonyms = {syn};
    if (firstParam.getRootType() == RootType::Synonym && firstParam.getRep() != syn) {
        synonyms.push_back(firstParam.getRep());
    }
    return synonyms;
}

std::vector<QueryEntityType> PatternClause::getSynonymEntityTypes() const {
    std::vector<QueryEntityType> types = {QPSUtil::patternClauseToEntityMap[type]};
    if (firstParam.getRootType() == RootType::Synonym) { types.push_back(QueryEntityType::Variable); }
    return types;
}

bool PatternClause::operator==(const Clause &other) const {
    try {
        const auto &otherPattern = dynamic_cast<const PatternClause &>(other);
        return (type == otherPattern.type) && (negation == otherPattern.negation) &&
               (firstParam == otherPattern.firstParam) && (secondParam == otherPattern.secondParam) &&
               (syn == otherPattern.syn);
    } catch (std::bad_cast &e) { return false; }
}
