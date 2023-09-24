#pragma once

#include <stdexcept>

#include "SemanticValHandler.h"

/**
 * SynonymHandler class that extends from SemanticValHandler
 */
class SynonymHandler : public SemanticValHandler {
public:
    /**
     * @brief Handles the semantic validation related to declared synonyms in the Clause
     * @param query The Query object
     * @param clause The shared pointer of the Clause
     */
    void handle(Query &query, std::shared_ptr<Clause> clause) override;
};