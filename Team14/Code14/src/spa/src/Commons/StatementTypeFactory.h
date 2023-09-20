#pragma once

#include "Commons/Entities/StatementType.h"
#include "SP/AST/Nodes/StatementNode.h"

class StatementTypeFactory {
public:
	static StatementType getStatementTypeFrom(StatementNodeType type);
};