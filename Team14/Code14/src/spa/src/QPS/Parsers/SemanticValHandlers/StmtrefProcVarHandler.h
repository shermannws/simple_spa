#pragma once

#include <stdexcept>

#include "SemanticValHandler.h"

/**
 * StmtrefProcVarHandler class that extends SemanticValHandler
 */
class StmtrefProcVarHandler : public SemanticValHandler {
public:
    /**
     * @brief Handles (stmtRef/proc, entRef) semantic validation of the Clause in the Query
     * @param query The Query object
     * @param clause The shared pointer of the Clause
     */
    void handle(Query &query, std::shared_ptr<Clause> clause) override;

    /**
     * @brief Handles the Refs of the clause by checking the semantics and setting the appropriate RefType
     * @param leftRef The first parameter of the Clause
     * @param rightRef The second parameter of the Clause
     */
    void handleRefType(Ref& leftRef, Ref& rightRef);
};