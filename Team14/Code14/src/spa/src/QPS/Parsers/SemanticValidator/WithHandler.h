#pragma once

#include <stdexcept>

#include "QPS/Exceptions/SemanticException.h"
#include "QPS/QPSUtil.h"
#include "SemanticValHandler.h"

/**
 * WithHandler class that extends from SemanticValHandler
 */
class WithHandler : public SemanticValHandler {
private:
    /**
     * @brief Handles the Refs of the clause by checking the semantics and setting the appropriate RefType
     * @param leftRef The first parameter of the Clause
     * @param rightRef The second parameter of the Clause
     */
    void handleRefType(Ref &leftRef, Ref &rightRef);

    /**
     * @brief Validates that the two refs to compare are of the same type
     * @param leftRef The first parameter of the Clause
     * @param rightRef The second parameter of the Clause
     */
    void validateSameType(Ref &leftRef, Ref &rightRef);

    /**
     * @brief Validates that the attrName of attrRef is applicable to the design entity of the synonym
     * @param attrRef The attrRef whose attrName is to check
     */
    void validateAttrRef(Ref &attrRef);

public:
    /**
     * @brief Handles the ref semantic validation of the Clause
     * @param query The Query object
     * @param clause The shared pointer to the Clause
     */
    void handle(const Query &query, std::shared_ptr<Clause> clause) override;
};
