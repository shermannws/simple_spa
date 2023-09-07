#pragma once

#include "Statement.h"

Statement::Statement(int lineNo)
	: Entity(std::make_shared<std::string>(std::to_string(lineNo)), true) {}
