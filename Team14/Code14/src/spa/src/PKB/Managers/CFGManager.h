#pragma once

#include "PKB/CFGStore/CFGStore.h"

class CFGManager {
private:
	/**
	 * The CFGStore that stores all the CFGs. 
	 */
	std::shared_ptr<CFGStore> cfgStore;

public:
	/**
	 * Constructor for CFGManager.
	 */
	CFGManager();

	/**
	 * @brief Sets the map from ProcedureName to the first CFGNode as the representation of the CFG.
	 * @param map The map from ProcedureName to the first CFGNode of the CFG.
	 */
	void setCFG(std::unordered_map<ProcedureName, std::shared_ptr<CFGNode>> map);
};