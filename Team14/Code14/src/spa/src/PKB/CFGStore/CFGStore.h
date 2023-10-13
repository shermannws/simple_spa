#include "PKB/Commons/MapStore.h"
#include "Commons/CFG/CFGNode.h"

class CFGStore : public MapStore<ProcedureName, CFGNode> {
public:
    /**
     * @brief Store the argument `map` as the CFG into PKB
     * @param map The map to be stored
     */
    void storeCFGMap(std::unordered_map<ProcedureName, std::shared_ptr<CFGNode>> map);
};