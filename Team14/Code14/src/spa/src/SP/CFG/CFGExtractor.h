#pragma once

#include <unordered_map>

#include "Commons/AppConstants.h"
#include "Commons/CFG/CFGNode.h"
#include "Commons/Entities/Statement.h"
#include "PKB/PkbWriter.h"

/**
 * A class to handle extracting Next relationships and passing the CFG to the PKB.
 */
class CFGExtractor {
private:
    /**
     * PkbWriter instance for writing to the PKB.
     */
    std::shared_ptr<PkbWriter> pkbWriter;

    /**
     * Saves the CFG to the PKB using the PkbWriter.
     * @param cfgMap An unordered map mapping each procedure to its head and all its CFGNodes
     */
    void
    saveCFGToPKB(const std::unordered_map<
                 ProcedureName, std::pair<std::shared_ptr<CFGNode>, std::vector<std::shared_ptr<CFGNode>>>> &cfgMap);

    /**
     * Extracts the direct Next relationships from a CFG and saves them to the PKB using the PkbWriter.
     * @param head The head node of the CFG
     * @param cfgNodes A vector of CFGNodes of the CFG
     */
    void extractNextRelationship(const std::shared_ptr<CFGNode> &head,
                                 const std::vector<std::shared_ptr<CFGNode>> &cfgNodes);

public:
    /**
     * Creates a CFGExtractor and instantiates it with a PkbWriter.
     * @param pkbWriter PkbWriter instance for writing to the PKB
     */
    explicit CFGExtractor(std::shared_ptr<PkbWriter> pkbWriter);

    /**
     * Initiates the saving of CFG to PKB, and the extraction of direct Next relationships for each CFG.
     * @param cfgMap An unordered map mapping each procedure to its head and all its CFGNodes
     */
    void extractRelationships(
            const std::unordered_map<
                    ProcedureName, std::pair<std::shared_ptr<CFGNode>, std::vector<std::shared_ptr<CFGNode>>>> &cfgMap);
};