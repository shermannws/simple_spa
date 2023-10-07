#include "StatementTypeFactory.h"


std::unordered_map<StatementNodeType, std::function<StatementType(void)>> StatementTypeFactory::functionMap = {
	{StatementNodeType::Assign, [&]() -> StatementType { return StatementType::Assign; }},
	{StatementNodeType::Print, [&]() -> StatementType { return StatementType::Print; }},
	{StatementNodeType::Read, [&]() -> StatementType { return StatementType::Read; }},
	{StatementNodeType::Call, [&]() -> StatementType { return StatementType::Call; }},
	{StatementNodeType::While, [&]() -> StatementType { return StatementType::While; }},
	{StatementNodeType::If, [&]() -> StatementType { return StatementType::If; }}
};

StatementType StatementTypeFactory::getStatementTypeFrom(StatementNodeType type) {
	return StatementTypeFactory::functionMap[type]();
}