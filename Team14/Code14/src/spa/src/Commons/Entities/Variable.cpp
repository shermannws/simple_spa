#include "Variable.h"

Variable::Variable(VariableName name) : Entity(std::make_shared<EntityValue>(name), EntityType::Variable) {}
