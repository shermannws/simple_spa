#pragma once

#include "Procedure.h"

Procedure::Procedure(string name) {
	this->name = name;
}
string Procedure::getName() {
	return this->name;
}
