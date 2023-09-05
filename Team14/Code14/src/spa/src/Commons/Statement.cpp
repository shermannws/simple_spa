#pragma once

#include "Statement.h"

Statement::Statement(int lineNo) {
	this->lineNo = lineNo;
}
int Statement::getLineNo() {
	return this->lineNo;
}
