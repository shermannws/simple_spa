#include "SuchThatClause.h"
#include "QPS/Exceptions/SyntaxException.h"
#include "QPS/QPSUtil.h"

SuchThatClause::SuchThatClause() = default;

SuchThatClause::SuchThatClause(const std::shared_ptr<Token> &absToken) {
    StringRep rep = absToken->getRep();
    if (QPSUtil::repClauseTypeMap.find(rep) == QPSUtil::repClauseTypeMap.end()) {
        throw SyntaxException("Invalid token, abstraction expected");
    }
    this->setType(QPSUtil::repClauseTypeMap[rep]);
}

void SuchThatClause::setSecondParam(Ref &ref) { secondParam = ref; }

Ref &SuchThatClause::getSecondParam() { return secondParam; }

std::vector<Synonym> SuchThatClause::getSynonyms() const {
    std::vector<Synonym> synonyms;
    if (firstParam.getRootType() == RootType::Synonym) { synonyms.push_back(firstParam.getRep()); }
    // only add RHS synonym if it is different from LHS
    if (secondParam.getRootType() == RootType::Synonym && !(firstParam == secondParam)) {
        synonyms.push_back(secondParam.getRep());
    }
    return synonyms;
}

bool SuchThatClause::isEqual(const Clause &other) const {
    const auto &otherST = dynamic_cast<const SuchThatClause &>(other);
    return (secondParam == otherST.secondParam);
}