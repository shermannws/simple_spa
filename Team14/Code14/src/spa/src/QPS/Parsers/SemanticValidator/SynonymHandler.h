#pragma once

#include <stdexcept>

#include "SemanticValHandler.h"

/**
 * SynonymHandler class that extends from SemanticValHandler
 */
class SynonymHandler : public SemanticValHandler {
private:
    /**
     * sets the entityType of the Ref object if the synonym is valid, otherwise throws semantic exception
     * @param query the query object
     * @param ref the Ref object we want to validate
     */
    void handleRefSyn(const Query &query, Ref &ref);

public:
    /**
     * @brief Handles the semantic validation related to declared synonyms in the Clause
     * @param query The Query object
     * @param clause The shared pointer of the Clause
     */
    void handle(const Query &query, std::shared_ptr<Clause> clause) override;
};