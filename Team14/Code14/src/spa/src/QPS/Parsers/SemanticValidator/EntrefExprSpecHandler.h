#pragma once

#include <stdexcept>

#include "SemanticValHandler.h"

/**
 * EntrefExprSpecHandler class that extends from SemanticValHandler
 */
class EntrefExprSpecHandler : public SemanticValHandler {
public:
    /**
     * @brief Handles (entRef, expression-spec) semantic validation of the Clause in the Query
     * @param query The Query object
     * @param clause The shared pointer of the Clause
     */
    void handle(const Query &query, std::shared_ptr<Clause> clause) override;
};
