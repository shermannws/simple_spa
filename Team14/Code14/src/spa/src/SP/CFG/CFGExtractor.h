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

    void
    saveCFGToPKB(const std::unordered_map<
                 ProcedureName, std::pair<std::shared_ptr<CFGNode>, std::vector<std::shared_ptr<CFGNode>>>> &cfgMap);

    void extractNextRelationship(const std::shared_ptr<CFGNode> &head,
                                 const std::vector<std::shared_ptr<CFGNode>> &cfgNodes);

public:
    /**
     * Creates a CFGExtractor and instantiates it with a PkbWriter.
     * @param pkbWriter PkbWriter instance for writing to the PKB
     */
    explicit CFGExtractor(std::shared_ptr<PkbWriter> pkbWriter);

    void extractRelationships(
            const std::unordered_map<
                    ProcedureName, std::pair<std::shared_ptr<CFGNode>, std::vector<std::shared_ptr<CFGNode>>>> &cfgMap);
};