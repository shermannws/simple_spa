
#include "EntrefEntrefHandler.h"
#include "QPS/QPSUtil.h"
#include "QPS/Exceptions/SemanticException.h"

void EntrefEntrefHandler::handle(Query &query, std::shared_ptr<Clause> clause) {
    auto suchThat = std::dynamic_pointer_cast<SuchThatClause>(clause);
    if (!suchThat) {
        return SemanticValHandler::handle(query, clause);
    }
    ClauseType type = suchThat->getType();
    Ref& leftRef = suchThat->getFirstParam();
    Ref& rightRef = suchThat->getSecondParam();

    if (!(type == ClauseType::Uses || type == ClauseType::Modifies) || leftRef.isStmtRef()) {
        return SemanticValHandler::handle(query, clause);
    }

    handleRefType(query, leftRef, rightRef);

    return SemanticValHandler::handle(query, clause);
}

void EntrefEntrefHandler::handleRefType(Query &query, Ref &leftRef, Ref &rightRef) {
    RootType leftRootType = leftRef.getRootType();
    RootType rightRootType = rightRef.getRootType();

    switch (leftRootType) {
    case RootType::Synonym: {
        std::shared_ptr<QueryEntity> entity = query.getEntity(leftRef.getRep());
        if (!entity->isProcedure()) {
            throw SemanticException("Invalid LHS synonym, non-procedure found");
        }
    }
    case RootType::Ident: {
        RefType leftRefType = RefType::EntRef;
        leftRef.setType(leftRefType);
        break;
    }
    case RootType::Wildcard:
        throw SemanticException("Invalid LHS, wildcard found");
    default:
        throw SemanticException("Invalid LHS entRef");
    }

    switch (rightRootType) {
    case RootType::Synonym: {
        std::shared_ptr<QueryEntity> entity = query.getEntity(rightRef.getRep());
        if (!entity->isVariable()) {
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
}
