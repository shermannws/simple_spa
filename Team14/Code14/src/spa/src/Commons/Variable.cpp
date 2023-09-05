#pragma once

#include "Variable.h"

Variable::Variable(string name) {
	this->name = name;
}
string Variable::getName() {
	return this->name;
}
