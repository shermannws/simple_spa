#include "Variable.h"

Variable::Variable(std::string name)
	: Entity(std::make_shared<std::string>(name), false, EntityType::Variable) {}

bool Variable::isWildCard() {
    return false;
}
