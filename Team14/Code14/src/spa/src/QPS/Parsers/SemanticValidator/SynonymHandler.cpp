#include "SynonymHandler.h"
#include "QPS/Exceptions/SemanticException.h"

void SynonymHandler::handle(const Query &query, std::shared_ptr<Clause> clause) {
    Ref &leftRef = clause->getFirstParam();
    // TODO: REMOVE LOD IN GETREP() & REMOVE DRY
    if (leftRef.isRootType(RootType::Synonym)) {
        std::shared_ptr<QueryEntity> entity = query.getEntity(leftRef.getRep());
        if (!entity) { throw SemanticException("Invalid LHS, undeclared synonym found"); }
        QueryEntityType entityType = entity->getType();
        leftRef.setEntityType(entityType);
    }

    auto suchThat = std::dynamic_pointer_cast<SuchThatClause>(clause);
    if (suchThat) {
        Ref &rightRef = suchThat->getSecondParam();
        if (rightRef.isRootType(RootType::Synonym)) {
            std::shared_ptr<QueryEntity> entity = query.getEntity(rightRef.getRep());
            if (!entity) { throw SemanticException("Invalid RHS, undeclared synonym found"); }
            QueryEntityType entityType = entity->getType();
            rightRef.setEntityType(entityType);
        }
        return SemanticValHandler::handle(query, clause);
    }

    auto pattern = std::dynamic_pointer_cast<PatternClause>(clause);
    if (pattern) {
        // validate Entity Synonym declared
        EntityPtr entity = query.getEntity(pattern->getSyn());
        if (!entity) { throw SemanticException("Undeclared synonym in pattern clause entity"); }
        return SemanticValHandler::handle(query, clause);
    }

    auto with = std::dynamic_pointer_cast<WithClause>(clause);
    if (with) {
        if (leftRef.isRootType(RootType::AttrRef)) {
            std::shared_ptr<QueryEntity> entity = query.getEntity(leftRef.getRep());
            if (!entity) { throw SemanticException("Invalid LHS, undeclared synonym found"); }
            QueryEntityType entityType = entity->getType();
            leftRef.setEntityType(entityType);
        }

        Ref &rightRef = with->getSecondParam();
        if (rightRef.isRootType(RootType::AttrRef)) {
            std::shared_ptr<QueryEntity> entity = query.getEntity(rightRef.getRep());
            if (!entity) { throw SemanticException("Invalid RHS, undeclared synonym found"); }
            QueryEntityType entityType = entity->getType();
            rightRef.setEntityType(entityType);
        }
        return SemanticValHandler::handle(query, clause);
    }

    return SemanticValHandler::handle(query, clause);
}