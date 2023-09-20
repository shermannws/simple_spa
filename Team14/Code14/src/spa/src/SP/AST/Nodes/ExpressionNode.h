#pragma once

#include "ASTNode.h"

// Interface for all expression node subtypes
class ExpressionNode : public ASTNode {
public:
	/*!
	 * Returns the expression as type string
	 */
	virtual std::string toString() = 0;
};
