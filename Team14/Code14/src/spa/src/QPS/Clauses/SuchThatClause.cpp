#include "SuchThatClause.h"
#include "QPS/Exceptions/SyntaxException.h"
#include "QPS/QPSUtil.h"

SuchThatClause::SuchThatClause() = default;

SuchThatClause::SuchThatClause(const std::shared_ptr<Token>& absToken) {
    StringRep rep = absToken->getRep();
    if (QPSUtil::repClauseTypeMap.find(rep) == QPSUtil::repClauseTypeMap.end()) {
        throw SyntaxException("Invalid token, abstraction expected");
    }
    this->setType(QPSUtil::repClauseTypeMap[rep]);
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