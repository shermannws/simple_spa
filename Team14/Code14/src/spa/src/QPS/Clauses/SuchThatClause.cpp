#include "SuchThatClause.h"
#include "QPS/Exceptions/SyntaxException.h"

SuchThatClause::SuchThatClause() = default;

SuchThatClause::SuchThatClause(const std::shared_ptr<Token>& absToken) {
    if (absToken->isToken("Uses")) {
        this->setType(ClauseType::Uses);
    } else if (absToken->isToken("Modifies")) {
        this->setType(ClauseType::Modifies);
    } else if (absToken->isToken("Follows")) {
        this->setType(ClauseType::Follows);
    } else if (absToken->isToken("Follows*")) {
        this->setType(ClauseType::FollowsStar);
    } else if (absToken->isToken("Parent")) {
        this->setType(ClauseType::Parent);
    } else if (absToken->isToken("Parent*")) {
        this->setType(ClauseType::ParentStar);
    } else {
        throw SyntaxException("Invalid token, abstraction expected");
    }
}

void SuchThatClause::setSecondParam(Ref& ref) {
    secondParam = ref;
}

Ref& SuchThatClause::getSecondParam() {
    return secondParam;
}

std::vector<Synonym> SuchThatClause::getSynonyms() const {
    std::vector<Synonym> synonyms;
    if (firstParam.getRootType() == RootType::Synonym) {
        synonyms.push_back(firstParam.getRep());
    }
    // only add RHS synonym if it is different from LHS
    if (secondParam.getRootType() == RootType::Synonym && !(firstParam == secondParam)) {
        synonyms.push_back(secondParam.getRep());
    }
    return synonyms;
}

bool SuchThatClause::operator==(const Clause& other) const {
    try {
        const auto& otherPattern = dynamic_cast<const SuchThatClause&>(other);
        return (type == otherPattern.type) &&
               (firstParam == otherPattern.firstParam) &&
               (secondParam==otherPattern.secondParam);
    } catch (std::bad_cast& e) {
        return false;
    }
}