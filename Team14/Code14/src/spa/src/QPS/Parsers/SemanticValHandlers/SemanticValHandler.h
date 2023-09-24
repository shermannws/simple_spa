#pragma once

#include <memory>
#include <stdexcept>

#include "QPS/Query.h"

/**
 * @brief SemanticValHandler
 */
class SemanticValHandler {
private:
    /**
     * @brief The shared pointer of the next handler linked to this handler
     */
    std::shared_ptr<SemanticValHandler> nextHandler;
public:
    /**
     * The constructor of SemanticValHandler
     */
    explicit SemanticValHandler();

    /**
     * The destructor of SemanticValHandler
     */
    virtual ~SemanticValHandler() = default;

    /**
     * @brief The setter of the next handler
     * @param handler The shared pointer of the next handler
     * @return The shared pointer of the next handler
     */
    std::shared_ptr<SemanticValHandler> setNext(std::shared_ptr<SemanticValHandler> handler);

    /**
     * @brief Handles the semantic validation of the Clause in the Query
     * @param query The Query object
     * @param clause The shared pointer of the Clause
     */
    virtual void handle(Query& query, std::shared_ptr<Clause> clause) = 0;
};