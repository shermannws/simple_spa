#pragma once

#include "Procedure.h"

Procedure::Procedure(string name)
	: Entity(std::make_shared<std::string>(name), false) {}
