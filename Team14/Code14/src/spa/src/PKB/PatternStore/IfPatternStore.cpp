#include "IfPatternStore.h"

IfPatternStore::IfPatternStore() : DoubleMapStore<Statement, Variable, VariableStore, StatementStore, Entity, Entity>() {}