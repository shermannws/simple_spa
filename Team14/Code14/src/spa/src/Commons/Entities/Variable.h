#pragma once

#include <string>
using namespace std;

#include "Entity.h"

class Variable : public Entity {
public:
	Variable(string name);

    virtual bool isWildCard();
};