#include "Statement.h"

Statement::Statement(int lineNo, StatementType statementType)
	: Entity(std::make_shared<std::string>(std::to_string(lineNo)), true, EntityType::Statement) {
    this->statementType = statementType;
}

StatementType Statement::getStatementType() const {
    return this->statementType;
}

bool Statement::isStatementType(StatementType statementType) const {
    return this->statementType == statementType || statementType == StatementType::Stmt;
}