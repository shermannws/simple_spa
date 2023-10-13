#include "PqlSemanticValidator.h"
#include "QPS/Clauses/SuchThatClause.h"
#include "SynonymHandler.h"
#include "StmtrefStmtrefHandler.h"
#include "EntrefExprSpecHandler.h"
#include "QPS/Exceptions/SemanticException.h"
#include "StmtrefProcVarHandler.h"
#include "ProcProcHandler.h"
#include "WithHandler.h"

PqlSemanticValidator::PqlSemanticValidator() = default;

void PqlSemanticValidator::validateDeclarations(const std::vector<Synonym>& synonyms) {
    std::unordered_set<Synonym> declared;
    for (const Synonym& syn : synonyms) {
        if (!declared.insert(syn).second)
            throw SemanticException("Trying to redeclare a synonym");
    }
}

void PqlSemanticValidator::validateResultClause(const Query& query, const Synonym& syn) {
    EntityPtr entity = query.getEntity(syn);
    if (!entity) {
        throw SemanticException("Undeclared synonym in Select clause");
    }
}

void PqlSemanticValidator::validateConstraintClauses(const Query& query) {
    for (const auto& clause : query.getSuchThat()) {
        validateClauseSemantics(query, clause);
    }
    for (const auto& clause : query.getPattern()) {
        validateClauseSemantics(query, clause);
    }
    for (const auto& clause : query.getWith()) {
        validateClauseSemantics(query, clause);
    }
}

void PqlSemanticValidator::validateClauseSemantics(const Query& query, const std::shared_ptr<SuchThatClause> clause) {
    std::shared_ptr<SynonymHandler> synonymHandler = std::make_shared<SynonymHandler>();
    std::shared_ptr<StmtrefStmtrefHandler> stmtrefHandler = std::make_shared<StmtrefStmtrefHandler>();
    std::shared_ptr<StmtrefProcVarHandler> stmtProcVarHandler = std::make_shared<StmtrefProcVarHandler>();
    std::shared_ptr<ProcProcHandler> ProcrefHandler = std::make_shared<ProcProcHandler>();
    synonymHandler->setNext(stmtrefHandler)->setNext(stmtProcVarHandler)->setNext(ProcrefHandler);
    synonymHandler->handle(query, clause);
}

void PqlSemanticValidator::validateClauseSemantics(const Query& query, const std::shared_ptr<PatternClause> clause) {
    std::shared_ptr<SynonymHandler> synonymHandler = std::make_shared<SynonymHandler>();
    std::shared_ptr<EntrefExprSpecHandler> EntExprHandler = std::make_shared<EntrefExprSpecHandler>();
    synonymHandler->setNext(EntExprHandler);
    synonymHandler->handle(query, clause);
}

void PqlSemanticValidator::validateClauseSemantics(const Query& query, const std::shared_ptr<WithClause> clause) {
    std::shared_ptr<SynonymHandler> synonymHandler = std::make_shared<SynonymHandler>();
    std::shared_ptr<WithHandler> withHandler = std::make_shared<WithHandler>();
    synonymHandler->setNext(withHandler);
    synonymHandler->handle(query, clause);
}
