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
    } else if (absToken->isToken("Calls")) {
        this->setType(ClauseType::Calls);
    } else if (absToken->isToken("Calls*")) {
        this->setType(ClauseType::CallsStar);
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