#include "Constant.h"

Constant::Constant(ConstantValue value)
    : Entity(std::make_shared<ConstantValue>(value), EntityType::Constant) {}
