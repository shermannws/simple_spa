#pragma once

#include <memory>

#include "PKB/PkbWriter.h"

/**
 * A SPA component for processing the source program.
 */
class SP {
private:
    /**
     * PkbWriter instance for writing to the PKB.
     */
    std::shared_ptr<PkbWriter> pkbWriter;

public:
    /**
     * Creates and initiates an SP with a PkbWriter.
     * @param pkbWriter PkbWriter instance for writing to the PKB.
     */
    SP(std::shared_ptr<PkbWriter> pkbWriter);

    /**
     * Initiates the tokenizing, validation and parsing of the source program.
     * Initiates the extraction of relationships and population to PKB.
     * @param input Source program to be processed
     */
    void startSPProcessing(std::string &input);
};