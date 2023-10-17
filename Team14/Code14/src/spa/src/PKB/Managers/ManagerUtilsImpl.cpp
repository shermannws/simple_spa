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

template std::vector<Entity>
ManagerUtils::getEntitiesFromStore<AssignPatternStore, Assignment>(std::shared_ptr<AssignPatternStore> store,
                                                                   std::function<bool(Assignment &)> matcher,
                                                                   std::function<Entity(Assignment &)> getter);

template std::vector<std::vector<Entity>> ManagerUtils::getEntityPairsFromStore<AssignPatternStore, Assignment>(
        std::shared_ptr<AssignPatternStore> store, std::function<bool(Assignment &)> matcher,
        std::function<std::vector<Entity>(Assignment &)> getter);

template std::vector<Entity>
ManagerUtils::getEntitiesFromEntityStore<Constant>(std::shared_ptr<EntityStore<Constant>> store,
                                                   std::function<bool(Constant &)> matcher,
                                                   std::function<Entity(Constant &)> getter);

template std::vector<Entity>
ManagerUtils::getEntitiesFromEntityStore<Procedure>(std::shared_ptr<EntityStore<Procedure>> store,
                                                    std::function<bool(Procedure &)> matcher,
                                                    std::function<Entity(Procedure &)> getter);

template std::vector<Entity>
ManagerUtils::getEntitiesFromEntityStore<Statement>(std::shared_ptr<EntityStore<Statement>> store,
                                                    std::function<bool(Statement &)> matcher,
                                                    std::function<Entity(Statement &)> getter);

template std::vector<Entity>
ManagerUtils::getEntitiesFromEntityStore<Variable>(std::shared_ptr<EntityStore<Variable>> store,
                                                   std::function<bool(Variable &)> matcher,
                                                   std::function<Entity(Variable &)> getter);

template std::vector<Entity>
ManagerUtils::getRightEntitiesFromLeftKeyStmtMatch<Statement>(RelationshipStore<Statement, Statement> &store,
                                                              Statement &key, StatementType type);

template std::vector<Entity>
ManagerUtils::getLeftEntitiesFromRightKeyStmtMatch<Statement>(RelationshipStore<Statement, Statement> &store,
                                                              Statement &key, StatementType type);

template std::vector<Entity>
ManagerUtils::getLeftEntitiesFromRightKeyStmtMatch<Variable>(RelationshipStore<Statement, Variable> &store,
                                                             Variable &key, StatementType type);

template std::vector<Entity>
ManagerUtils::getRightEntitiesFromLeftKeyNoMatch<Statement, Variable>(RelationshipStore<Statement, Variable> &store,
                                                                      Statement &key);

template std::vector<Entity>
ManagerUtils::getRightEntitiesFromLeftKeyNoMatch<Procedure, Procedure>(RelationshipStore<Procedure, Procedure> &store,
                                                                       Procedure &key);

template std::vector<Entity>
ManagerUtils::getLeftEntitiesFromRightKeyNoMatch<Procedure, Procedure>(RelationshipStore<Procedure, Procedure> &store,
                                                                       Procedure &key);

template std::vector<Entity>
ManagerUtils::getRightEntitiesFromLeftKeyNoMatch<Procedure, Variable>(RelationshipStore<Procedure, Variable> &store,
                                                                      Procedure &key);

template std::vector<Entity>
ManagerUtils::getLeftEntitiesFromRightKeyNoMatch<Procedure, Variable>(RelationshipStore<Procedure, Variable> &store,
                                                                      Variable &key);


template std::vector<Entity> ManagerUtils::getLeftKeysStmtMatch<Variable>(RelationshipStore<Statement, Variable> &store,
                                                                          StatementType type);

template std::vector<Entity>
ManagerUtils::getLeftKeysStmtMatch<Statement>(RelationshipStore<Statement, Statement> &store, StatementType type);

template std::vector<Entity>
ManagerUtils::getRightKeysStmtMatch<Statement>(RelationshipStore<Statement, Statement> &store, StatementType type);

template std::vector<Entity>
ManagerUtils::getLeftKeysNoMatch<Procedure, Variable>(RelationshipStore<Procedure, Variable> &store);

template std::vector<Entity>
ManagerUtils::getLeftKeysNoMatch<Procedure, Procedure>(RelationshipStore<Procedure, Procedure> &store);

template std::vector<Entity>
ManagerUtils::getRightKeysNoMatch<Procedure, Procedure>(RelationshipStore<Procedure, Procedure> &store);


template bool ManagerUtils::mapContains<Statement, Variable>(RelationshipStore<Statement, Variable> &store,
                                                             Statement &key, Variable &value);

template bool ManagerUtils::mapContains<Statement, Statement>(RelationshipStore<Statement, Statement> &store,
                                                              Statement &key, Statement &value);

template bool ManagerUtils::mapContains<Procedure, Procedure>(RelationshipStore<Procedure, Procedure> &store,
                                                              Procedure &key, Procedure &value);

template bool ManagerUtils::mapContains<Procedure, Variable>(RelationshipStore<Procedure, Variable> &store,
                                                             Procedure &key, Variable &value);


template std::vector<std::vector<Entity>>
ManagerUtils::getPairs<Entity, RelationshipStore<Statement, Statement>, Statement, Statement>(
        RelationshipStore<Statement, Statement> &store, std::function<bool(Statement &)> leftMatcher,
        std::function<bool(Statement &)> rightMatcher);

template std::vector<std::vector<Entity>>
ManagerUtils::getPairs<Entity, RelationshipStore<Statement, Variable>, Statement, Variable>(
        RelationshipStore<Statement, Variable> &store, std::function<bool(Statement &)> leftMatcher,
        std::function<bool(Variable &)> rightMatcher);

template std::vector<std::vector<Entity>>
ManagerUtils::getPairsNoMatch<Procedure, Procedure>(RelationshipStore<Procedure, Procedure> &store);

template std::vector<std::vector<Entity>>
ManagerUtils::getPairsNoMatch<Procedure, Variable>(RelationshipStore<Procedure, Variable> &store);


template void ManagerUtils::unique<Entity>(std::vector<Entity> &vec);

template void
ManagerUtils::addStmtVarFromProcVar(std::shared_ptr<ModifiesRelationshipManager> stmtVarManager,
                                    std::shared_ptr<RelationshipStore<Procedure, Statement>> procStmtStore,
                                    std::shared_ptr<ModifiesProcRelationshipManager> procVarManager);

template void
ManagerUtils::addStmtVarFromProcVar(std::shared_ptr<UsesRelationshipManager> stmtVarManager,
                                    std::shared_ptr<RelationshipStore<Procedure, Statement>> procStmtStore,
                                    std::shared_ptr<UsesProcRelationshipManager> procVarManager);


template std::vector<Entity> ManagerUtils::getLeftKeysMatchRight(RelationshipStore<Statement, Statement> &store,
                                                                 std::function<bool(Statement &)> leftMatcher);