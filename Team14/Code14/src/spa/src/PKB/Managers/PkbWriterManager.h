#pragma once

#include <memory>

#include "PKB/Managers/AssignmentManager.h"
#include "PKB/EntityStores/ConstantStore.h"
#include "PKB/EntityStores/ProcedureStore.h"
#include "PKB/EntityStores/StatementStore.h"
#include "PKB/EntityStores/VariableStore.h"
#include "PKB/Managers/FollowsRelationshipManager.h"
#include "PKB/Managers/UsesRelationshipManager.h"
#include "Commons/Entities/Constant.h"
#include "Commons/Entities/Procedure.h"
#include "PKB/Managers/ModifiesRelationshipManager.h"
#include "PKB/Managers/ParentRelationshipManager.h"

class PkbWriterManager {
private:
    std::shared_ptr<AssignmentManager> assignmentManager;

    std::shared_ptr<ConstantStore> constantStore;
    std::shared_ptr<ProcedureStore> procedureStore;
    std::shared_ptr<StatementStore> statementStore;
    std::shared_ptr<VariableStore> variableStore;

    std::shared_ptr<FollowsRelationshipManager> followsRelationshipManager;
    std::shared_ptr<UsesRelationshipManager> usesRelationshipManager;
    std::shared_ptr<ModifiesRelationshipManager> modifiesRelationshipManager;
    std::shared_ptr<ParentRelationshipManager> parentRelationshipManager;
public:
    PkbWriterManager(
            std::shared_ptr<AssignmentManager> assignmentManager,
            std::shared_ptr<ConstantStore> constantStore,
            std::shared_ptr<ProcedureStore> procedureStore,
            std::shared_ptr<StatementStore> statementStore,
            std::shared_ptr<VariableStore> variableStore,
            std::shared_ptr<FollowsRelationshipManager> followsRelationshipManager,
            std::shared_ptr<UsesRelationshipManager> usesRelationshipManager,
            std::shared_ptr<ModifiesRelationshipManager> modifiesRelationshipManager,
            std::shared_ptr<ParentRelationshipManager> parentRelationshipManager
    );

    void addConstant(std::shared_ptr<Constant> c);
    void addVariable(std::shared_ptr<Variable> v);
    void addProcedure(std::shared_ptr<Procedure> p);

    void addPrintStatement(std::shared_ptr<Statement> s);
    void addReadStatement(std::shared_ptr<Statement> s);
    void addAssignStatement(std::shared_ptr<Statement> s, std::shared_ptr<Variable> lhs, std::shared_ptr<std::string> rhs);

    void addFollowsRelationship(std::shared_ptr<Statement> s1, std::shared_ptr<Statement> s2, bool isDirect);
    void addUsesRelationship(std::shared_ptr<Statement> s, std::shared_ptr<Variable> v);
};