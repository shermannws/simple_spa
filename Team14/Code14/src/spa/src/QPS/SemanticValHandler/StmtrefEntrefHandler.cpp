#pragma once

#include "StmtrefEntrefHandler.h"
#include "../QPSUtil.h"
#include "../Exception/SemanticException.h"

void StmtrefEntrefHandler::handle(Query &query, std::shared_ptr<Clause> clause) {
    auto suchThat = std::dynamic_pointer_cast<SuchThatClause>(clause);
    ClauseType type = suchThat->getType();
    Ref& leftRef = suchThat->getFirstParam();
    RootType leftRootType = leftRef.getRootType();
    Ref& rightRef = suchThat->getSecondParam();
    RootType rightRootType = rightRef.getRootType();

    if (!suchThat || !(type == ClauseType::Uses || type == ClauseType::Modifies)) {
        return SemanticValHandler::handle(query, clause);
    }

    // TODO: to add more checks depending on whether need to handle Uses(proc, v)
    // TODO: set StmtRef here if correct

    switch (leftRootType) {
        case RootType::Synonym: {
            std::shared_ptr<QueryEntity> entity = query.getEntity(leftRef.getRep());
            QueryEntityType entityType = entity->getType();
            if (!QPSUtil::isOfStmtType(entityType)) {
                // TODO: change to return SemanticValHandler::handle(query, clause); when Uses(proc,v) is handled
                throw SemanticException("Invalid LHS synonym, non-statement found");
            }
//            break;
        }
        case RootType::Integer: {
            RefType leftRefType = RefType::StmtRef;
            leftRef.setType(leftRefType);
            break;
        }
        case RootType::Wildcard:
            throw SemanticException("Invalid LHS, wildcard found");
        default:
            throw std::runtime_error("Invalid LHS stmtRef");
    }

    switch (type) {
        case ClauseType::Uses:
            if (leftRootType == RootType::Synonym) {
                std::shared_ptr<QueryEntity> entity = query.getEntity(leftRef.getRep());
                QueryEntityType entityType = entity->getType();
                if (!QPSUtil::isOfUsesStmtType(entityType)) {
                    throw SemanticException("Invalid Uses LHS, invalid stmtRef found");
                }
                RefType leftRefType = RefType::StmtRef;
                leftRef.setType(leftRefType);
            }
            break;
        case ClauseType::Modifies:
            if (leftRootType == RootType::Synonym) {
                std::shared_ptr<QueryEntity> entity = query.getEntity(leftRef.getRep());
                QueryEntityType entityType = entity->getType();
                if (!QPSUtil::isOfModifiesStmtType(entityType)) {
                    throw SemanticException("Invalid Modifies LHS, invalid stmtRef found");
                }
                RefType leftRefType = RefType::StmtRef;
                leftRef.setType(leftRefType);
            }
            break;
    }

    switch (rightRootType) {
        case RootType::Synonym: {
            std::shared_ptr<QueryEntity> entity = query.getEntity(rightRef.getRep());
            QueryEntityType entityType = entity->getType();
            if (entityType != QueryEntityType::Variable) {
                throw SemanticException("Invalid RHS synonym, non-variable found");
            }
        }
        case RootType::Ident:
        case RootType::Wildcard: {
            RefType rightRefType = RefType::EntRef;
            rightRef.setType(rightRefType);
            break;
        }
        default:
            throw std::runtime_error("Invalid RHS entRef");
    }


    return SemanticValHandler::handle(query, clause);
}