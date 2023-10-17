#include "NoExprHandler.h"
#include "QPS/Exceptions/SemanticException.h"

void NoExprHandler::handle(const Query &query, std::shared_ptr<Clause> clause) {
    auto pattern = std::dynamic_pointer_cast<PatternClause>(clause);
    ClauseType clauseType = pattern->getType();
    if (clauseType != ClauseType::If && clauseType != ClauseType::While) {
        return SemanticValHandler::handle(query, clause);
    }

    if (clauseType != ClauseType::If && pattern->hasThirdParam()) { throw SemanticException("Invalid syn-if"); }

    Ref &leftRef = pattern->getFirstParam();
    RefType lhsType = RefType::EntRef;
    leftRef.setType(lhsType);

    if (leftRef.getRootType() == RootType::Synonym && leftRef.getEntityType() != QueryEntityType::Variable) {
        throw SemanticException("Invalid LHS in Pattern, synonym does not represent variable");
    }

    ExpressionSpec &secondParam = pattern->getSecondParam();
    if (secondParam.first != ExpressionSpecType::Wildcard) {
        throw SemanticException("Invalid second param in if/while pattern, wildcard expected");
    }
}