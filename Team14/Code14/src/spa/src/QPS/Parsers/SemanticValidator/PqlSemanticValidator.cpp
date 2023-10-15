#include "PqlSemanticValidator.h"
#include "QPS/Clauses/SuchThatClause.h"
#include "SynonymHandler.h"
#include "StmtrefStmtrefHandler.h"
#include "EntrefExprSpecHandler.h"
#include "QPS/Exceptions/SemanticException.h"
#include "StmtrefProcVarHandler.h"
#include "ProcProcHandler.h"

PqlSemanticValidator::PqlSemanticValidator() = default;

void PqlSemanticValidator::validateDeclarations(const std::vector<Synonym>& synonyms) {
    std::unordered_set<Synonym> declared;
    for (const Synonym& syn : synonyms) {
        if (!declared.insert(syn).second)
            throw SemanticException("Trying to redeclare a synonym");
    }
}

void PqlSemanticValidator::validateResultClause(const Query& query) {
    // if size == 1 and "BOOLEAN" and undeclared
    auto resultClause = query.getSelect();
    if (isBoolean(resultClause)) {
        // set query as type bool? validateResultBoolean()
    } else {
        for (const auto& elem : resultClause) {
            std::size_t dotPos = elem.find('.');
            if (dotPos != std::string::npos){ // attrRef
                validateResultAttrRef(query, elem, dotPos);
            } else {  // synonym
                validateResultSynonym(query, elem);
            }
        }
    }
}


void PqlSemanticValidator::validateResultSynonym(const Query& query, Synonym elem) {
    EntityPtr entity = query.getEntity(elem);
    if (!entity) {
        throw SemanticException("Undeclared synonym in Select clause");
    }
}

void PqlSemanticValidator::validateResultAttrRef(const Query& query, Synonym elem, size_t dotPos) {
    Synonym syn = elem.substr(0, dotPos);
    AttrName attrName = elem.substr(dotPos + 1);
    EntityPtr entity = query.getEntity(syn);
    if (!entity) {
        throw SemanticException("Undeclared synonym in Select clause");
    }
    auto expectedEntityTypes = QPSUtil::attrNameToTypeMap[attrName];
    auto it = expectedEntityTypes.find(entity->getType());
    if (it == expectedEntityTypes.end()) {
        throw SemanticException("Invalid attrRef in result clause");
    }
}


bool PqlSemanticValidator::isBoolean(std::vector<Synonym> resultClause) {
    return (resultClause.size() == 1 && resultClause[0] == "BOOLEAN");
}


void PqlSemanticValidator::validateConstraintClauses(const Query& query) {
    for (const auto& clause : query.getSuchThat()) {
        validateClauseSemantics(query, clause);
    }
    for (const auto& clause : query.getPattern()) {
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