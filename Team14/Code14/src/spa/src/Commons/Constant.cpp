#pragma once

#include "Constant.h"

Constant::Constant(int value) {
	this->value = value;
}
int Constant::getValue() {
	return this->value;
}
