#include "SynonymHandler.h"
#include "QPS/Exceptions/SemanticException.h"
#include "QPS/QPSUtil.h"

void SynonymHandler::handle(const Query &query, std::shared_ptr<Clause> clause) {
    Ref &leftRef = clause->getFirstParam();
    RootType leftRootType = leftRef.getRootType();

    if (leftRootType == RootType::Synonym) { handleRefSyn(query, leftRef); }

    auto suchThat = std::dynamic_pointer_cast<SuchThatClause>(clause);
    if (suchThat) {
        Ref &rightRef = suchThat->getSecondParam();
        RootType rightRootType = rightRef.getRootType();
        if (rightRootType == RootType::Synonym) { handleRefSyn(query, rightRef); }
    }

    auto pattern = std::dynamic_pointer_cast<PatternClause>(clause);
    if (pattern) {
        // validate Entity Synonym declared
        EntityPtr entity = query.getEntity(pattern->getSyn());
        if (!entity) { throw SemanticException("Undeclared synonym in pattern clause entity"); }
        QueryEntityType entityType = entity->getType();
        if (QPSUtil::entityToClauseMap.find(entityType) == QPSUtil::entityToClauseMap.end()) {
            throw SemanticException("Unsupported pattern clause");
        }
        ClauseType clauseType = QPSUtil::entityToClauseMap[entityType];
        pattern->setType(clauseType);
    }

    return SemanticValHandler::handle(query, clause);
}

void SynonymHandler::handleRefSyn(const Query &query, Ref &ref) {
    std::shared_ptr<QueryEntity> entity = query.getEntity(ref.getRep());
    if (!entity) { throw SemanticException("Invalid ref synonym, undeclared synonym found"); }
    QueryEntityType entityType = entity->getType();
    ref.setEntityType(entityType);
}