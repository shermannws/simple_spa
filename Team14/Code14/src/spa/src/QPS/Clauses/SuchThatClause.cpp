#include "SuchThatClause.h"
#include "QPS/Exceptions/SyntaxException.h"
#include "QPS/Evaluators/Strategies/UsesSuchThatStrategy.h"
#include "QPS/Evaluators/Strategies/ModifiesSuchThatStrategy.h"
#include "QPS/Evaluators/Strategies/FollowsSuchThatStrategy.h"
#include "QPS/Evaluators/Strategies/FollowsStarSuchThatStrategy.h"
#include "QPS/Evaluators/Strategies/ParentSuchThatStrategy.h"
#include "QPS/Evaluators/Strategies/ParentStarSuchThatStrategy.h"

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
