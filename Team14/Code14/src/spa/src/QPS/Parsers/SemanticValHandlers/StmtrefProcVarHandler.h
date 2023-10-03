#pragma once

#include <stdexcept>

#include "SemanticValHandler.h"

/**
 * StmtrefProcVarHandler class that extends SemanticValHandler
 */
class StmtrefProcVarHandler : public SemanticValHandler {
private:
    std::unordered_set<ClauseType> clauseTypes {ClauseType::Uses, ClauseType::Modifies};
    std::unordered_map<QueryEntityType, RefType> entityRefMap {
        {QueryEntityType::Stmt, RefType::StmtRef},
        {QueryEntityType::Assign, RefType::StmtRef},
        {QueryEntityType::Print, RefType::StmtRef},
        {QueryEntityType::If, RefType::StmtRef},
        {QueryEntityType::While, RefType::StmtRef},
        {QueryEntityType::Read, RefType::StmtRef},
        {QueryEntityType::Procedure, RefType::EntRef}
    };
public:
    /**
     * @brief Handles (stmtRef, entRef) semantic validation of the Clause in the Query
     * @param query The Query object
     * @param clause The shared pointer of the Clause
     */
    void handle(Query &query, std::shared_ptr<Clause> clause) override;

    void handleRefType(Ref& leftRef, Ref& rightRef);
};