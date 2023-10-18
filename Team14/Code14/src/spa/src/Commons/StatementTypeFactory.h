#pragma once

#include "Commons/Entities/StatementType.h"
#include "SP/AST/Nodes/StatementNode.h"

/**
 * @brief A factory class for StatementType
 * @details A factory class for StatementType
 */
class StatementTypeFactory {
private:
    /**
     * @brief A map of StatementNodeType to a function that returns a StatementNode object
     */
    static std::unordered_map<StatementNodeType, std::function<StatementType(void)>> functionMap;

public:
    /**
     * @brief Returns the StatementType of the StatementNode object
     * @param type The StatementNode object
     * @return The StatementType of the StatementNode object
     */
    static StatementType getStatementTypeFrom(StatementNodeType type);
};