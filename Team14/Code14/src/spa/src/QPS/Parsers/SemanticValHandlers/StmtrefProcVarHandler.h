#pragma once

#include <stdexcept>

#include "SemanticValHandler.h"

/**
 * StmtrefProcVarHandler class that extends SemanticValHandler
 */
class StmtrefProcVarHandler : public SemanticValHandler {
public:
    /**
     * @brief Handles (stmtRef, entRef) semantic validation of the Clause in the Query
     * @param query The Query object
     * @param clause The shared pointer of the Clause
     */
    void handle(Query &query, std::shared_ptr<Clause> clause) override;

    void handleRefType(Ref& leftRef, Ref& rightRef);
};