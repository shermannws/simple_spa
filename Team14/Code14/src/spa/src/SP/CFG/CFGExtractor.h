#pragma once

#include <unordered_map>

#include "PKB/PkbWriter.h"
#include "Commons/AppConstants.h"
#include "Commons/Entities/Statement.h"
#include "Commons/CFG/CFGNode.h"

/**
 * A class to handle extracting Next relationships and passing the CFG to the PKB.
 */
class CFGExtractor {
private:
    /**
     * PkbWriter instance for writing to the PKB.
     */
    std::shared_ptr<PkbWriter> pkbWriter;

    void saveCFGToPKB(const std::unordered_map<ProcedureName, Statement>& heads,
            const std::unordered_map<ProcedureName, std::unordered_map<Statement, std::shared_ptr<CFGNode>>>& cfgs);

    void extractNextRelationships(const std::unordered_map<ProcedureName, Statement>& heads,
            const std::unordered_map<ProcedureName, std::unordered_map<Statement, std::shared_ptr<CFGNode>>>& cfgs);
public:
    /**
     * Creates a CFGExtractor and instantiates it with a PkbWriter.
     * @param pkbWriter PkbWriter instance for writing to the PKB
     */
    explicit CFGExtractor(std::shared_ptr<PkbWriter> pkbWriter);

    void extractRelationships(const std::unordered_map<ProcedureName, Statement>& heads, const std::unordered_map<ProcedureName,
            std::unordered_map<Statement, std::shared_ptr<CFGNode>>>& cfgs);
};