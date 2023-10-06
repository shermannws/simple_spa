#include "PKB/Managers/ManagerUtils.cpp"
#include "PKB/AssignmentPatternStore/Assignment.h"
#include "PKB/AssignmentPatternStore/AssignmentPatternStore.h"
#include "Commons/Entities/Constant.h"
#include "Commons/Entities/Procedure.h"
#include "Commons/Entities/Statement.h"
#include "Commons/Entities/Variable.h"
#include "PKB/Managers/ModifiesProcRelationshipManager.h"
#include "PKB/Managers/ModifiesRelationshipManager.h"
#include "PKB/Managers/UsesProcRelationshipManager.h"
#include "PKB/Managers/UsesRelationshipManager.h"

template std::vector<Entity> ManagerUtils::getEntitiesFromStore<AssignmentPatternStore, Assignment>(std::shared_ptr<AssignmentPatternStore> store, std::function<bool(Assignment&)> matcher, std::function<Entity(Assignment&)> getter);

template std::vector<std::vector<Entity>> ManagerUtils::getEntityPairsFromStore<AssignmentPatternStore, Assignment>(std::shared_ptr<AssignmentPatternStore> store, std::function<bool(Assignment&)> matcher, std::function<std::vector<Entity>(Assignment&)> getter);

template std::vector<Entity> ManagerUtils::getEntitiesFromEntityStore<Constant>(std::shared_ptr<EntityStore<Constant>> store, std::function<bool(Constant&)> matcher, std::function<Entity(Constant&)> getter);

template std::vector<Entity> ManagerUtils::getEntitiesFromEntityStore<Procedure>(std::shared_ptr<EntityStore<Procedure>> store, std::function<bool(Procedure&)> matcher, std::function<Entity(Procedure&)> getter);

template std::vector<Entity> ManagerUtils::getEntitiesFromEntityStore<Statement>(std::shared_ptr<EntityStore<Statement>> store, std::function<bool(Statement&)> matcher, std::function<Entity(Statement&)> getter);

template std::vector<Entity> ManagerUtils::getEntitiesFromEntityStore<Variable>(std::shared_ptr<EntityStore<Variable>> store, std::function<bool(Variable&)> matcher, std::function<Entity(Variable&)> getter);

template std::vector<Entity> ManagerUtils::getRightEntitiesFromLeftKey<Statement, Statement>(RelationshipStore<Statement, Statement>& store, Statement& key, std::function<bool(Statement&)> matcher);

template std::vector<Entity> ManagerUtils::getLeftEntitiesFromRightKey<Statement, Statement>(RelationshipStore<Statement, Statement>& store, Statement& key, std::function<bool(Statement&)> matcher);

template std::vector<Entity> ManagerUtils::getRightEntitiesFromLeftKey<Statement, Variable>(RelationshipStore<Statement, Variable>& store, Statement& key, std::function<bool(Variable&)> matcher);

template std::vector<Entity> ManagerUtils::getLeftEntitiesFromRightKey<Statement, Variable>(RelationshipStore<Statement, Variable>& store, Variable& key, std::function<bool(Statement&)> matcher);

template std::vector<Entity> ManagerUtils::getRightEntitiesFromLeftKey<Procedure, Procedure>(RelationshipStore<Procedure, Procedure>& store, Procedure& key, std::function<bool(Procedure&)> matcher);

template std::vector<Entity> ManagerUtils::getLeftEntitiesFromRightKey<Procedure, Procedure>(RelationshipStore<Procedure, Procedure>& store, Procedure& key, std::function<bool(Procedure&)> matcher);

template std::vector<Entity> ManagerUtils::getRightEntitiesFromLeftKey<Procedure, Variable>(RelationshipStore<Procedure, Variable>& store, Procedure& key, std::function<bool(Variable&)> matcher);

template std::vector<Entity> ManagerUtils::getLeftEntitiesFromRightKey<Procedure, Variable>(RelationshipStore<Procedure, Variable>& store, Variable& key, std::function<bool(Procedure&)> matcher);

template void ManagerUtils::unique<Entity>(std::vector<Entity>& vec);

template void ManagerUtils::addStmtVarFromProcVar(std::shared_ptr<ModifiesRelationshipManager> stmtVarManager, std::shared_ptr<RelationshipStore<Procedure, Statement>> procStmtStore, std::shared_ptr<ModifiesProcRelationshipManager> procVarManager);

template void ManagerUtils::addStmtVarFromProcVar(std::shared_ptr<UsesRelationshipManager> stmtVarManager, std::shared_ptr<RelationshipStore<Procedure, Statement>> procStmtStore, std::shared_ptr<UsesProcRelationshipManager> procVarManager);