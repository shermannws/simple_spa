#include "ProcProcHandler.h"

void ProcProcHandler::handle(const Query &query, std::shared_ptr<Clause> clause) {
    auto suchThat = std::dynamic_pointer_cast<SuchThatClause>(clause);
    if (!suchThat) {
        return SemanticValHandler::handle(query, clause);
    }
    ClauseType type = suchThat->getType();
    Ref& leftRef = suchThat->getFirstParam();
    Ref& rightRef = suchThat->getSecondParam();

    if (QPSUtil::typeToArgTypeMap[type] != ProcProc) {
        return SemanticValHandler::handle(query, clause);
    }

    handleRefType(leftRef, rightRef);

    return SemanticValHandler::handle(query, clause);
}

void ProcProcHandler::handleRefType(Ref &leftRef, Ref &rightRef) {
    auto refType = RefType::EntRef;
    leftRef.setType(refType);
    rightRef.setType(refType);

    if (leftRef.getRootType() == RootType::Synonym &&
            leftRef.getEntityType() != QueryEntityType::Procedure) {
        throw SemanticException("Invalid LHS, non-procedure synonym");
    }

    if (rightRef.getRootType() == RootType::Synonym &&
        rightRef.getEntityType() != QueryEntityType::Procedure) {
        throw SemanticException("Invalid RHS, non-procedure synonym");
    }

}
