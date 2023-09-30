#include "PqlSemanticValidator.h"
#include "QPS/Clauses/SuchThatClause.h"
#include "SynonymHandler.h"
#include "StmtrefStmtrefHandler.h"
#include "StmtrefEntrefHandler.h"
#include "EntrefExprSpecHandler.h"
#include "QPS/QPSUtil.h"
#include "QPS/Exceptions/SemanticException.h"

PqlSemanticValidator::PqlSemanticValidator() {};

void PqlSemanticValidator::validateSelectSemantics(const Query& query, const Synonym& syn) {
    EntityPtr entity = query.getEntity(syn);
    if (!entity) {
        throw SemanticException("Undeclared synonym in Select clause");
    }
}

void PqlSemanticValidator::validateClauseSemantics(const Query& query, const std::shared_ptr<SuchThatClause> clause) {
//    if (!clause) {
//        return;
//    }
    std::shared_ptr<SynonymHandler> synonymHandler = std::make_shared<SynonymHandler>();
    std::shared_ptr<StmtrefStmtrefHandler> stmtrefHandler = std::make_shared<StmtrefStmtrefHandler>();
    std::shared_ptr<StmtrefEntrefHandler> stmtEntHandler = std::make_shared<StmtrefEntrefHandler>();
    synonymHandler->setNext(stmtrefHandler)->setNext(stmtEntHandler);
    synonymHandler->handle(query, clause);
}

void PqlSemanticValidator::validateClauseSemantics(const Query& query, const std::shared_ptr<PatternClause> clause) {
//    if (!clause) {
//        return;
//    }
    std::shared_ptr<SynonymHandler> synonymHandler = std::make_shared<SynonymHandler>();
    std::shared_ptr<EntrefExprSpecHandler> EntExprHandler = std::make_shared<EntrefExprSpecHandler>();
    synonymHandler->setNext(EntExprHandler);
    synonymHandler->handle(query, clause);
}