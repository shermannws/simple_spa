#include "ConditionPatternStore.h"

ConditionPatternStore::ConditionPatternStore() : DoubleMapStore<Statement, Variable, EntityStore<Variable>, EntityStore<Statement>, Entity, Entity>() {}