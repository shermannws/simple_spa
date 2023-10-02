#include "StmtrefStmtrefHandler.h"
#include "QPS/Exceptions/SemanticException.h"

void StmtrefStmtrefHandler::handle(Query &query, std::shared_ptr<Clause> clause) {
    auto suchThat = std::dynamic_pointer_cast<SuchThatClause>(clause);
    if (!suchThat) {
        return SemanticValHandler::handle(query, clause);
    }
    ClauseType type = suchThat->getType();
    Ref& leftRef = suchThat->getFirstParam();
    Ref& rightRef = suchThat->getSecondParam();

    if (!(type == ClauseType::Follows || type == ClauseType::FollowsStar
                          || type == ClauseType::Parent || type == ClauseType::ParentStar)) {
        return SemanticValHandler::handle(query, clause);
    }

    handleRefType(query, leftRef, rightRef);

    return SemanticValHandler::handle(query, clause);
}

void StmtrefStmtrefHandler::handleRefType(Query& query, Ref& leftRef, Ref& rightRef) {
    RootType leftRootType = leftRef.getRootType();
    RootType rightRootType = rightRef.getRootType();
    switch (leftRootType) {
        case RootType::Synonym: {
            std::shared_ptr<QueryEntity> entity = query.getEntity(leftRef.getRep());
            if (!entity->isOfStmtType()) {
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
            if (!entity->isOfStmtType()) {
                throw SemanticException("Invalid RHS synonym, non-statement found");
            }
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
};
