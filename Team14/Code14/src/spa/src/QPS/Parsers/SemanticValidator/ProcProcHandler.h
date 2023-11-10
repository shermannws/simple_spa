#pragma once

#include <stdexcept>

#include "QPS/Exceptions/SemanticException.h"
#include "QPS/QPSUtil.h"
#include "SemanticValHandler.h"

/**
 * ProcProcHandler class that extends from SemanticValHandler
 */
class ProcProcHandler : public SemanticValHandler {
private:
    /**
     * @brief Handles the Refs of the clause by checking the semantics and setting the appropriate RefType
     * @param leftRef The first parameter of the Clause
     * @param rightRef The second parameter of the Clause
     */
    void handleRefType(Ref &leftRef, Ref &rightRef);

public:
    /**
     * @brief Handles (proc,proc) semantic validation of the Clause in the Query
     * @param query The Query object
     * @param clause The shared pointer to the Clause
     */
    void handle(const Query &query, std::shared_ptr<Clause> clause) override;
};
