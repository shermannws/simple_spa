#pragma once

#include "Constant.h"

Constant::Constant(int value)
	: Entity(std::make_shared<std::string>(std::to_string(value)), true, EntityType::Constant) {}
