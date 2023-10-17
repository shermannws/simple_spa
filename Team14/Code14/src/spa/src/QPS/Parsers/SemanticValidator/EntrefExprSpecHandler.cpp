#include "EntrefExprSpecHandler.h"
#include "QPS/Exceptions/SemanticException.h"


void EntrefExprSpecHandler::handle(const Query &query, std::shared_ptr<Clause> clause) {
    auto patternClause = std::dynamic_pointer_cast<PatternClause>(clause);

    if (!patternClause) {
        return SemanticValHandler::handle(query, clause);
    }

    EntityPtr entity = query.getEntity(patternClause->getSyn());
    if (entity->getType() != QueryEntityType::Assign) {
        throw SemanticException("Unsupported pattern clause, expected an assign synonym");
    }

    Ref& leftRef = clause->getFirstParam();
    RefType lhsType = RefType::EntRef;
    leftRef.setType(lhsType);

    if (leftRef.getRootType() == RootType::Synonym && leftRef.getEntityType() != QueryEntityType::Variable) {
        throw SemanticException("Invalid LHS in Pattern, synonym does not represent variable");
    }

    return SemanticValHandler::handle(query, clause);
}