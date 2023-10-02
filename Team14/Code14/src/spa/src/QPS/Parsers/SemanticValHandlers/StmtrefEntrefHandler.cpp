#include "StmtrefEntrefHandler.h"
#include "QPS/Exceptions/SemanticException.h"

void StmtrefEntrefHandler::handle(Query &query, std::shared_ptr<Clause> clause) {
    auto suchThat = std::dynamic_pointer_cast<SuchThatClause>(clause);
    if (!suchThat) {
        return SemanticValHandler::handle(query, clause);
    }

    ClauseType type = suchThat->getType();
    Ref& leftRef = suchThat->getFirstParam();
    Ref& rightRef = suchThat->getSecondParam();

    if (!(type == ClauseType::Uses || type == ClauseType::Modifies)) {
        return SemanticValHandler::handle(query, clause);
    }

    handleRefType(query, leftRef, rightRef);

    return SemanticValHandler::handle(query, clause);
}

void StmtrefEntrefHandler::handleRefType(Query& query, Ref& leftRef, Ref& rightRef) {
    RootType leftRootType = leftRef.getRootType();
    RootType rightRootType = rightRef.getRootType();

    switch (leftRootType) {
    case RootType::Synonym: {
        std::shared_ptr<QueryEntity> entity = query.getEntity(leftRef.getRep());
        if (entity->isType(QueryEntityType::Procedure)) {
            return; // route to EntrefEntrefHandler
        }

        if (!entity->isOfStmtType()) {
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
    case RootType::Ident:
        return; // route to EntrefEntrefHandler
    default:
        throw SemanticException("Invalid LHS stmtRef");
    }

    switch (rightRootType) {
    case RootType::Synonym: {
        std::shared_ptr<QueryEntity> entity = query.getEntity(rightRef.getRep());
        if (!entity->isType(QueryEntityType::Variable)) {
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