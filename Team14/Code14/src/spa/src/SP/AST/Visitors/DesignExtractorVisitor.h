#pragma once
#include <PKB/PkbWriter.h>

// interface for all design extractors
class DesignExtractorVisitor {
protected:
    std::shared_ptr<PkbWriter> pkbWriter;

public:
    // Added to allow this class to be used in dynamic_cast expression
    // Made pure to prevent instantiation of this class
    virtual ~DesignExtractorVisitor() = 0;
};
