#include "Commons/Entities/Constant.h"
#include "Commons/Entities/Procedure.h"
#include "Commons/Entities/Statement.h"
#include "Commons/Entities/Variable.h"
#include "PKB/Commons/Assignment.h"
#include "PKB/Managers/ManagerUtils.cpp"
#include "PKB/Managers/ModifiesProcRelationshipManager.h"
#include "PKB/Managers/ModifiesRelationshipManager.h"
#include "PKB/Managers/UsesProcRelationshipManager.h"
#include "PKB/Managers/UsesRelationshipManager.h"
#include "PKB/PatternStore/AssignPatternStore.h"
#include "PKB/RelationshipStores/CallsRelationshipStore.h"
#include "PKB/RelationshipStores/NextRelationshipStore.h"

template EntitySet
ManagerUtils::getEntitiesFromStore<AssignPatternStore, Assignment>(std::shared_ptr<AssignPatternStore> store,
                                                                   std::function<bool(std::shared_ptr<Assignment>)> matcher,
                                                                   std::function<EntityPointer(std::shared_ptr<Assignment>)> getter);

template EntityPairSet ManagerUtils::getEntityPairsFromStore<AssignPatternStore, Assignment>(
        std::shared_ptr<AssignPatternStore> store, std::function<bool(std::shared_ptr<Assignment>)> matcher,
        std::function<std::vector<EntityPointer>(std::shared_ptr<Assignment>)> getter);

template EntitySet
ManagerUtils::getEntitiesFromEntityStore<Constant>(std::shared_ptr<EntityStore<Constant>> store,
                                                   std::function<bool(std::shared_ptr<Constant>)> matcher,
                                                   std::function<EntityPointer(std::shared_ptr<Constant>)> getter);

template EntitySet
ManagerUtils::getEntitiesFromEntityStore<Procedure>(std::shared_ptr<EntityStore<Procedure>> store,
                                                    std::function<bool(std::shared_ptr<Procedure>)> matcher,
                                                    std::function<EntityPointer(std::shared_ptr<Procedure>)> getter);

template EntitySet
ManagerUtils::getEntitiesFromEntityStore<Statement>(std::shared_ptr<EntityStore<Statement>> store,
                                                    std::function<bool(std::shared_ptr<Statement>)> matcher,
                                                    std::function<EntityPointer(std::shared_ptr<Statement>)> getter);

template EntitySet
ManagerUtils::getEntitiesFromEntityStore<Variable>(std::shared_ptr<EntityStore<Variable>> store,
                                                   std::function<bool(std::shared_ptr<Variable>)> matcher,
                                                   std::function<EntityPointer(std::shared_ptr<Variable>)> getter);

template EntitySet
ManagerUtils::getRightEntitiesFromLeftKeyStmtMatch<Statement>(RelationshipStore<Statement, Statement> &store,
                                                              Statement &key, StatementType type);

template EntitySet
ManagerUtils::getLeftEntitiesFromRightKeyStmtMatch<Statement>(RelationshipStore<Statement, Statement> &store,
                                                              Statement &key, StatementType type);

template EntitySet
ManagerUtils::getLeftEntitiesFromRightKeyStmtMatch<Variable>(RelationshipStore<Statement, Variable> &store,
                                                             Variable &key, StatementType type);

template EntitySet
ManagerUtils::getRightEntitiesFromLeftKeyNoMatch<Statement, Variable>(RelationshipStore<Statement, Variable> &store,
                                                                      Statement &key);

template EntitySet
ManagerUtils::getRightEntitiesFromLeftKeyNoMatch<Procedure, Procedure>(RelationshipStore<Procedure, Procedure> &store,
                                                                       Procedure &key);

template EntitySet
ManagerUtils::getLeftEntitiesFromRightKeyNoMatch<Procedure, Procedure>(RelationshipStore<Procedure, Procedure> &store,
                                                                       Procedure &key);

template EntitySet
ManagerUtils::getRightEntitiesFromLeftKeyNoMatch<Procedure, Variable>(RelationshipStore<Procedure, Variable> &store,
                                                                      Procedure &key);

template EntitySet
ManagerUtils::getLeftEntitiesFromRightKeyNoMatch<Procedure, Variable>(RelationshipStore<Procedure, Variable> &store,
                                                                      Variable &key);


template EntitySet
ManagerUtils::getLeftKeysStmtMatch<Variable>(RelationshipStore<Statement, Variable> &store, StatementType type);

template EntitySet
ManagerUtils::getLeftKeysStmtMatch<Statement>(RelationshipStore<Statement, Statement> &store, StatementType type);

template EntitySet
ManagerUtils::getRightKeysStmtMatch<Statement>(RelationshipStore<Statement, Statement> &store, StatementType type);

template EntitySet
ManagerUtils::getLeftKeysNoMatch<Procedure, Variable>(RelationshipStore<Procedure, Variable> &store);

template EntitySet
ManagerUtils::getLeftKeysNoMatch<Procedure, Procedure>(RelationshipStore<Procedure, Procedure> &store);

template EntitySet
ManagerUtils::getRightKeysNoMatch<Procedure, Procedure>(RelationshipStore<Procedure, Procedure> &store);


template bool ManagerUtils::mapContains<Statement, Variable>(RelationshipStore<Statement, Variable> &store,
                                                             Statement &key, Variable &value);

template bool ManagerUtils::mapContains<Statement, Statement>(RelationshipStore<Statement, Statement> &store,
                                                              Statement &key, Statement &value);

template bool ManagerUtils::mapContains<Procedure, Procedure>(RelationshipStore<Procedure, Procedure> &store,
                                                              Procedure &key, Procedure &value);

template bool ManagerUtils::mapContains<Procedure, Variable>(RelationshipStore<Procedure, Variable> &store,
                                                             Procedure &key, Variable &value);


template EntityPairSet ManagerUtils::getPairs<Entity, RelationshipStore<Statement, Statement>, Statement, Statement>(
        RelationshipStore<Statement, Statement> &store, std::function<bool(std::shared_ptr<Statement>)> leftMatcher,
        std::function<bool(std::shared_ptr<Statement>)> rightMatcher);

template EntityPairSet ManagerUtils::getPairs<Entity, RelationshipStore<Statement, Variable>, Statement, Variable>(
        RelationshipStore<Statement, Variable> &store, std::function<bool(std::shared_ptr<Statement>)> leftMatcher,
        std::function<bool(std::shared_ptr<Variable>)> rightMatcher);

template void ManagerUtils::unique<Entity>(std::vector<Entity> &vec);

template void
ManagerUtils::addStmtVarFromProcVar(std::shared_ptr<ModifiesRelationshipManager> stmtVarManager,
                                    std::shared_ptr<RelationshipStore<Procedure, Statement>> procStmtStore,
                                    std::shared_ptr<ModifiesProcRelationshipManager> procVarManager);

template void
ManagerUtils::addStmtVarFromProcVar(std::shared_ptr<UsesRelationshipManager> stmtVarManager,
                                    std::shared_ptr<RelationshipStore<Procedure, Statement>> procStmtStore,
                                    std::shared_ptr<UsesProcRelationshipManager> procVarManager);


template EntitySet ManagerUtils::getLeftKeysMatchRight(RelationshipStore<Statement, Statement> &store,
                                                                        std::function<bool(std::shared_ptr<Statement>)> leftMatcher);

template void ManagerUtils::calculateTransitivity<NextRelationshipStore, Statement>(
        std::shared_ptr<NextRelationshipStore> relationshipStore,
        std::shared_ptr<NextRelationshipStore> starRelationshipStore);

template void ManagerUtils::calculateTransitivity<CallsRelationshipStore, Procedure>(
        std::shared_ptr<CallsRelationshipStore> relationshipStore,
        std::shared_ptr<CallsRelationshipStore> starRelationshipStore);