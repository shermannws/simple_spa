#pragma once

#include "StmtrefStmtrefHandler.h"
#include "../QPSUtil.h"
#include "../Exception/SemanticException.h"

void StmtrefStmtrefHandler::handle(Query &query, std::shared_ptr<Clause> clause) {
    auto suchThat = std::dynamic_pointer_cast<SuchThatClause>(clause);
    ClauseType type = suchThat->getType();
    Ref& leftRef = suchThat->getFirstParam();
    RootType leftRootType = leftRef.getRootType();
    Ref& rightRef = suchThat->getSecondParam();
    RootType rightRootType = rightRef.getRootType();

    if (!suchThat || !(type == ClauseType::Follows || type == ClauseType::FollowsStar
                          || type == ClauseType::Parent || type == ClauseType::ParentStar)) {
        return SemanticValHandler::handle(query, clause);
    }

    switch (leftRootType) {
    case RootType::Synonym: {
        std::shared_ptr<QueryEntity> entity = query.getEntity(leftRef.getRep());
        QueryEntityType entityType = entity->getType();
        if (!QPSUtil::isOfStmtType(entityType)) {
            throw SemanticException("Invalid LHS synonym, non-statement found");
        }
    }
    case RootType::Integer:
    case RootType::Wildcard: {
        RefType leftRefType = RefType::StmtRef;
        leftRef.setType(leftRefType);
        break;
    }
    default:
        throw std::runtime_error("Invalid LHS stmtRef");
    }

    switch (rightRootType) {
        case RootType::Synonym: {
            std::shared_ptr<QueryEntity> entity = query.getEntity(rightRef.getRep());
            QueryEntityType entityType = entity->getType();
            if (!QPSUtil::isOfStmtType(entityType)) {
                throw SemanticException("Invalid RHS synonym, non-statement found");
            }
//            break;
        }
        case RootType::Integer:
        case RootType::Wildcard: {
            RefType rightRefType = RefType::StmtRef;
            rightRef.setType(rightRefType);
            break;
        }
        default:
            throw std::runtime_error("Invalid RHS stmtRef");
    }

    return SemanticValHandler::handle(query, clause);
}