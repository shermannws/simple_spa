#include "StmtrefStmtrefHandler.h"
#include "QPS/Exceptions/SemanticException.h"
#include "QPS/QPSUtil.h"

void StmtrefStmtrefHandler::handle(const Query &query, std::shared_ptr<Clause> clause) {
    auto suchThat = std::dynamic_pointer_cast<SuchThatClause>(clause);
    if (!suchThat) {
        return SemanticValHandler::handle(query, clause);
    }
    ClauseType type = suchThat->getType();
    Ref& leftRef = suchThat->getFirstParam();
    Ref& rightRef = suchThat->getSecondParam();

    if (QPSUtil::stmtrefClauseTypes.find(type) == QPSUtil::stmtrefClauseTypes.end()) {
        return SemanticValHandler::handle(query, clause);
    }

    handleRefType(leftRef, rightRef);

    return SemanticValHandler::handle(query, clause);
}

void StmtrefStmtrefHandler::handleRefType(Ref& leftRef, Ref& rightRef) {
    RootType leftRootType = leftRef.getRootType();
    RootType rightRootType = rightRef.getRootType();
    switch (leftRootType) {
        case RootType::Synonym: {
            QueryEntityType entityType = leftRef.getEntityType();
            if (QPSUtil::stmtRefEntities.find(entityType) == QPSUtil::stmtRefEntities.end()) {
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
            QueryEntityType entityType = rightRef.getEntityType();
            if (QPSUtil::stmtRefEntities.find(entityType) == QPSUtil::stmtRefEntities.end()) {
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
