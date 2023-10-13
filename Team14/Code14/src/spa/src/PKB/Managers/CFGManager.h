#include "PKB/CFGStore/CFGStore.h";

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
	 * @brief Adds the map from ProcedureName to the first CFGNode of the CFG to the CFGStore.
	 * @param map The map from ProcedureName to the first CFGNode of the CFG.
	 */
	void addCFG(std::unordered_map<ProcedureName, std::shared_ptr<CFGNode>> map);

	/**
	 * @brief Gets the CFG of the procedure with the given procedureName.
	 * @param procedureName The name of the procedure.
	 * @return The CFG of the procedure with the given procedureName.
	 */
	std::shared_ptr<CFGNode> getCFG(ProcedureName procedureName);
};