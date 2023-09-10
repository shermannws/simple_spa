#pragma once

#include <string>

#include "Entity.h"

class Variable : public Entity {
public:
	Variable(std::string name);

    virtual bool isWildCard();
};