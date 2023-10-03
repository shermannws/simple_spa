#include "StmtrefProcVarHandler.h"
#include "QPS/Exceptions/SemanticException.h"

void StmtrefProcVarHandler::handle(Query &query, std::shared_ptr<Clause> clause) {
    auto suchThat = std::dynamic_pointer_cast<SuchThatClause>(clause);
    if (!suchThat) {
        return SemanticValHandler::handle(query, clause);
    }

    ClauseType type = suchThat->getType();
    Ref& leftRef = suchThat->getFirstParam();
    Ref& rightRef = suchThat->getSecondParam();

    if (clauseTypes.find(type) == clauseTypes.end()) {
        return SemanticValHandler::handle(query, clause);
    }

    handleRefType(leftRef, rightRef);

    return SemanticValHandler::handle(query, clause);
}

void StmtrefProcVarHandler::handleRefType(Ref& leftRef, Ref& rightRef) {
    RootType leftRootType = leftRef.getRootType();
    RootType rightRootType = rightRef.getRootType();

    switch (leftRootType) {
    case RootType::Synonym: {
        QueryEntityType entityType = leftRef.getEntityType();
        if (entityRefMap.find(entityType) == entityRefMap.end()) {
            throw SemanticException("Invalid LHS synonym");
        }
        RefType leftRefType = entityRefMap[entityType];
        leftRef.setType(leftRefType);
    }
    case RootType::Integer: {
        RefType leftRefType = RefType::StmtRef;
        leftRef.setType(leftRefType);
        break;
    }
    case RootType::Ident: {
        RefType leftRefType = RefType::EntRef;
        leftRef.setType(leftRefType);
        break;
    }
    case RootType::Wildcard:
        throw SemanticException("Invalid LHS, wildcard found");
    default:
        throw SemanticException("Invalid LHS stmtRef");
    }

    switch (rightRootType) {
    case RootType::Synonym: {
        QueryEntityType entityType = rightRef.getEntityType();
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
}