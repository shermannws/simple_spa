#include "CFGStore.h"

void CFGStore::storeCFGMap(
        std::unordered_map<ProcedureName, std::shared_ptr<CFGNode>> map) {
    this->setMapStore(map);
}
