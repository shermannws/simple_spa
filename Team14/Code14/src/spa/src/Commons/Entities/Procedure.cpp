#pragma once

#include "Procedure.h"

Procedure::Procedure(std::string name)
	: Entity(std::make_shared<std::string>(name), EntityType::Procedure) {}
