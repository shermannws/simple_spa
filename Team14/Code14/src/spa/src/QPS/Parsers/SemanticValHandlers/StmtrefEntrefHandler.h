#pragma once

#include <stdexcept>

#include "SemanticValHandler.h"

/**
 * StmtrefEntrefHandler class that extends SemanticValHandler
 */
class StmtrefEntrefHandler : public SemanticValHandler {
public:
    /**
     * @brief Handles (stmtRef, entRef) semantic validation of the Clause in the Query
     * @param query The Query object
     * @param clause The shared pointer of the Clause
     */
    void handle(Query &query, std::shared_ptr<Clause> clause) override;

    void handleRefType(Query& query, Ref& leftRef, Ref& rightRef);
};