#include "StmtrefEntrefHandler.h"
#include "QPS/QPSUtil.h"
#include "QPS/Exceptions/SemanticException.h"

void StmtrefEntrefHandler::handle(const Query &query, std::shared_ptr<Clause> clause) {
    auto suchThat = std::dynamic_pointer_cast<SuchThatClause>(clause);
    ClauseType type = suchThat->getType();
    Ref& leftRef = suchThat->getFirstParam();
    RootType leftRootType = leftRef.getRootType();
    Ref& rightRef = suchThat->getSecondParam();
    RootType rightRootType = rightRef.getRootType();

    if (!suchThat || !(type == ClauseType::Uses || type == ClauseType::Modifies)) {
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