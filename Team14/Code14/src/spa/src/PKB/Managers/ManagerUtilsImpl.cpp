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

template std::unordered_set<Entity>
ManagerUtils::getEntitiesFromStore<AssignPatternStore, Assignment>(std::shared_ptr<AssignPatternStore> store,
                                                                   std::function<bool(Assignment &)> matcher,
                                                                   std::function<Entity(Assignment &)> getter);

template std::unordered_set<std::vector<Entity>> ManagerUtils::getEntityPairsFromStore<AssignPatternStore, Assignment>(
        std::shared_ptr<AssignPatternStore> store, std::function<bool(Assignment &)> matcher,
        std::function<std::vector<Entity>(Assignment &)> getter);

template std::unordered_set<Entity>
ManagerUtils::getEntitiesFromEntityStore<Constant>(std::shared_ptr<EntityStore<Constant>> store,
                                                   std::function<bool(Constant &)> matcher,
                                                   std::function<Entity(Constant &)> getter);

template std::unordered_set<Entity>
ManagerUtils::getEntitiesFromEntityStore<Procedure>(std::shared_ptr<EntityStore<Procedure>> store,
                                                    std::function<bool(Procedure &)> matcher,
                                                    std::function<Entity(Procedure &)> getter);

template std::unordered_set<Entity>
ManagerUtils::getEntitiesFromEntityStore<Statement>(std::shared_ptr<EntityStore<Statement>> store,
                                                    std::function<bool(Statement &)> matcher,
                                                    std::function<Entity(Statement &)> getter);

template std::unordered_set<Entity>
ManagerUtils::getEntitiesFromEntityStore<Variable>(std::shared_ptr<EntityStore<Variable>> store,
                                                   std::function<bool(Variable &)> matcher,
                                                   std::function<Entity(Variable &)> getter);

template std::unordered_set<Entity>
ManagerUtils::getRightEntitiesFromLeftKeyStmtMatch<Statement>(RelationshipStore<Statement, Statement> &store,
                                                              Statement &key, StatementType type);

template std::unordered_set<Entity>
ManagerUtils::getLeftEntitiesFromRightKeyStmtMatch<Statement>(RelationshipStore<Statement, Statement> &store,
                                                              Statement &key, StatementType type);

template std::unordered_set<Entity>
ManagerUtils::getLeftEntitiesFromRightKeyStmtMatch<Variable>(RelationshipStore<Statement, Variable> &store,
                                                             Variable &key, StatementType type);

template std::unordered_set<Entity>
ManagerUtils::getRightEntitiesFromLeftKeyNoMatch<Statement, Variable>(RelationshipStore<Statement, Variable> &store,
                                                                      Statement &key);

template std::unordered_set<Entity>
ManagerUtils::getRightEntitiesFromLeftKeyNoMatch<Procedure, Procedure>(RelationshipStore<Procedure, Procedure> &store,
                                                                       Procedure &key);

template std::unordered_set<Entity>
ManagerUtils::getLeftEntitiesFromRightKeyNoMatch<Procedure, Procedure>(RelationshipStore<Procedure, Procedure> &store,
                                                                       Procedure &key);

template std::unordered_set<Entity>
ManagerUtils::getRightEntitiesFromLeftKeyNoMatch<Procedure, Variable>(RelationshipStore<Procedure, Variable> &store,
                                                                      Procedure &key);

template std::unordered_set<Entity>
ManagerUtils::getLeftEntitiesFromRightKeyNoMatch<Procedure, Variable>(RelationshipStore<Procedure, Variable> &store,
                                                                      Variable &key);


template std::unordered_set<Entity>
ManagerUtils::getLeftKeysStmtMatch<Variable>(RelationshipStore<Statement, Variable> &store, StatementType type);

template std::unordered_set<Entity>
ManagerUtils::getLeftKeysStmtMatch<Statement>(RelationshipStore<Statement, Statement> &store, StatementType type);

template std::unordered_set<Entity>
ManagerUtils::getRightKeysStmtMatch<Statement>(RelationshipStore<Statement, Statement> &store, StatementType type);

template std::unordered_set<Entity>
ManagerUtils::getLeftKeysNoMatch<Procedure, Variable>(RelationshipStore<Procedure, Variable> &store);

template std::unordered_set<Entity>
ManagerUtils::getLeftKeysNoMatch<Procedure, Procedure>(RelationshipStore<Procedure, Procedure> &store);

template std::unordered_set<Entity>
ManagerUtils::getRightKeysNoMatch<Procedure, Procedure>(RelationshipStore<Procedure, Procedure> &store);


template bool ManagerUtils::mapContains<Statement, Variable>(RelationshipStore<Statement, Variable> &store,
                                                             Statement &key, Variable &value);

template bool ManagerUtils::mapContains<Statement, Statement>(RelationshipStore<Statement, Statement> &store,
                                                              Statement &key, Statement &value);

template bool ManagerUtils::mapContains<Procedure, Procedure>(RelationshipStore<Procedure, Procedure> &store,
                                                              Procedure &key, Procedure &value);

template bool ManagerUtils::mapContains<Procedure, Variable>(RelationshipStore<Procedure, Variable> &store,
                                                             Procedure &key, Variable &value);


template std::unordered_set<std::vector<Entity>>
ManagerUtils::getPairs<Entity, RelationshipStore<Statement, Statement>, Statement, Statement>(
        RelationshipStore<Statement, Statement> &store, std::function<bool(Statement &)> leftMatcher,
        std::function<bool(Statement &)> rightMatcher);

template std::unordered_set<std::vector<Entity>>
ManagerUtils::getPairs<Entity, RelationshipStore<Statement, Variable>, Statement, Variable>(
        RelationshipStore<Statement, Variable> &store, std::function<bool(Statement &)> leftMatcher,
        std::function<bool(Variable &)> rightMatcher);

template void ManagerUtils::unique<Entity>(std::vector<Entity> &vec);

template void
ManagerUtils::addStmtVarFromProcVar(std::shared_ptr<ModifiesRelationshipManager> stmtVarManager,
                                    std::shared_ptr<RelationshipStore<Procedure, Statement>> procStmtStore,
                                    std::shared_ptr<ModifiesProcRelationshipManager> procVarManager);

template void
ManagerUtils::addStmtVarFromProcVar(std::shared_ptr<UsesRelationshipManager> stmtVarManager,
                                    std::shared_ptr<RelationshipStore<Procedure, Statement>> procStmtStore,
                                    std::shared_ptr<UsesProcRelationshipManager> procVarManager);


template std::unordered_set<Entity> ManagerUtils::getLeftKeysMatchRight(RelationshipStore<Statement, Statement> &store,
                                                                        std::function<bool(Statement &)> leftMatcher);

template void ManagerUtils::calculateTransitivity<NextRelationshipStore, Statement>(
        std::shared_ptr<NextRelationshipStore> relationshipStore,
        std::shared_ptr<NextRelationshipStore> starRelationshipStore);

template void ManagerUtils::calculateTransitivity<CallsRelationshipStore, Procedure>(
        std::shared_ptr<CallsRelationshipStore> relationshipStore,
        std::shared_ptr<CallsRelationshipStore> starRelationshipStore);