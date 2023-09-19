#pragma once

#include "SynonymHandler.h"

void SynonymHandler::handle(Query &query, std::shared_ptr<Clause> clause) {
    Ref& leftRef = clause->getFirstParam();
    RootType leftRootType = leftRef.getRootType();

    if (leftRootType == RootType::Synonym) {
        std::shared_ptr<QueryEntity> entity = query.getEntity(leftRef.getRep());
        if (!entity) {
            throw std::runtime_error("Invalid LHS, undeclared synonym found");
        }
        QueryEntityType entityType = entity->getType();
        leftRef.setEntityType(entityType);
    }

    auto suchThat = std::dynamic_pointer_cast<SuchThatClause>(clause);
    if (suchThat) {
        Ref& rightRef = suchThat->getSecondParam();
        RootType rightRootType = rightRef.getRootType();
        if (rightRootType == RootType::Synonym) {
            std::shared_ptr<QueryEntity> entity = query.getEntity(rightRef.getRep());
            if (!entity) {
                throw std::runtime_error("Invalid RHS, undeclared synonym found");
            }
            QueryEntityType entityType = entity->getType();
            rightRef.setEntityType(entityType);
        }
    }

    return SemanticValHandler::handle(query, clause);

    // TODO: use this handler to check synonyms in pattern as well :-)
}