#pragma once

#include <memory>
#include <functional>

#include "SP/AST/Nodes/ASTNode.h"
#include "Commons/Entities/Statement.h"
#include "Commons/Entities/Variable.h"

class VisitorUtility {
public:
	/*!
	 * Adds all Statement-Variable Relationship where the Variable is child of root
	 */
	static void addAllStatementVariableRelationshipFrom(
		std::shared_ptr<ASTNode> root,
		Statement s,
		std::function<void(std::shared_ptr<Statement>, std::shared_ptr<Variable>)> func
	);
};