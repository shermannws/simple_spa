#include "CFGManager.h"

CFGManager::CFGManager() {
	this->cfgStore = std::make_shared<CFGStore>();
}

void CFGManager::addCFG(std::unordered_map<ProcedureName, std::shared_ptr<CFGNode>> map) {
	this->cfgStore->storeCFGMap(map);
}

std::shared_ptr<CFGNode> CFGManager::getCFG(ProcedureName procedureName) {
	return this->cfgStore->getValueOf(procedureName);
}
