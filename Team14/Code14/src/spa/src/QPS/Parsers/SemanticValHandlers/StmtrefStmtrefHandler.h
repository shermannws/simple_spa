#pragma once

#include "SemanticValHandler.h"

/**
 * StmtrefStmtrefHandler class that extends from SemanticValHandler
 */
class StmtrefStmtrefHandler : public SemanticValHandler {
public:
    /**
     * @brief Handles (stmtRef,stmtRef) semantic validation of the Clause in the Clause
     * @param query The Query object
     * @param clause The shared pointer of the Clause
     */
    void handle(const Query &query, std::shared_ptr<Clause> clause) override;
};
