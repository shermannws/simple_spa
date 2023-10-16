#include "Procedure.h"

Procedure::Procedure(ProcedureName name)
    : Entity(std::make_shared<EntityValue>(name), EntityType::Procedure) {}
