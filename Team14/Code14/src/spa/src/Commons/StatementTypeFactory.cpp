#include "StatementTypeFactory.h"

// Helper method to translate from AST StatementNodeType into PKB StatementType
StatementType StatementTypeFactory::getStatementTypeFrom(StatementNodeType type) {
	switch (type) {
	case StatementNodeType::Assign:
		return StatementType::Assign;
		break;
	case StatementNodeType::Print:
		return StatementType::Print;
		break;
	case StatementNodeType::Read:
		return StatementType::Read;
		break;
	case StatementNodeType::Call:
		return StatementType::Call;
		break;
	case StatementNodeType::While:
		return StatementType::While;
		break;
	case StatementNodeType::If:
		return StatementType::If;
		break;
	}
	//Should never reach here as all statements must be one of the above types
	throw std::runtime_error("Invalid StatementNodeType");
}