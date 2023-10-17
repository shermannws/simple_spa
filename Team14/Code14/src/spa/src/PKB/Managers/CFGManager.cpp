#include "CFGManager.h"

CFGManager::CFGManager() { this->cfgStore = std::make_shared<CFGStore>(); }

void CFGManager::setCFG(
        std::unordered_map<ProcedureName, std::shared_ptr<CFGNode>> map) {
    this->cfgStore->storeCFGMap(map);
}
