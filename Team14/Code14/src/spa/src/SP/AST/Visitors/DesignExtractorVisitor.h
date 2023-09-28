#pragma once
#include <PKB/PkbWriter.h>

/**
 * Interface for all design extractors.
 */
class DesignExtractorVisitor {
protected:
    /**
     * PkbWriter instance for writing to the PKB.
     */
    std::shared_ptr<PkbWriter> pkbWriter;

public:
    // Added to allow this class to be used in dynamic_cast expression
    virtual ~DesignExtractorVisitor() = default;
};
