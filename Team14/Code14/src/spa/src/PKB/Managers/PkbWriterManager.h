#pragma once

#include <memory>

#include "PKB/Managers/AssignmentManager.h"
#include "PKB/Managers/EntitiesManager.h"
#include "PKB/Managers/FollowsRelationshipManager.h"
#include "PKB/Managers/UsesRelationshipManager.h"
#include "Commons/Entities/Constant.h"
#include "Commons/Entities/Procedure.h"
#include "PKB/Managers/ModifiesRelationshipManager.h"
#include "PKB/Managers/ParentRelationshipManager.h"
#include "PKB/PkbTypes.h"

class PkbWriterManager {
private:
    std::shared_ptr<AssignmentManager> assignmentManager;

    std::shared_ptr<EntitiesManager> entitiesManager;

    std::shared_ptr<FollowsRelationshipManager> followsRelationshipManager;
    std::shared_ptr<UsesRelationshipManager> usesRelationshipManager;
    std::shared_ptr<ModifiesRelationshipManager> modifiesRelationshipManager;
    std::shared_ptr<ParentRelationshipManager> parentRelationshipManager;
public:
    PkbWriterManager(
            std::shared_ptr<AssignmentManager> assignmentManager,
            std::shared_ptr<EntitiesManager> entitiesManager,
            std::shared_ptr<FollowsRelationshipManager> followsRelationshipManager,
            std::shared_ptr<UsesRelationshipManager> usesRelationshipManager,
            std::shared_ptr<ModifiesRelationshipManager> modifiesRelationshipManager,
            std::shared_ptr<ParentRelationshipManager> parentRelationshipManager
    );

    void addConstant(std::shared_ptr<Constant> c);
    void addVariable(std::shared_ptr<Variable> v);
    void addProcedure(std::shared_ptr<Procedure> p);

    void addStatement(std::shared_ptr<Statement> s);
    void addAssignStatement(std::shared_ptr<Statement> s, std::shared_ptr<Variable> lhs, std::shared_ptr<Expression> rhs);

    void addFollowsRelationship(std::shared_ptr<Statement> s1, std::shared_ptr<Statement> s2, bool isDirect);
    void addUsesRelationship(std::shared_ptr<Statement> s, std::shared_ptr<Variable> v);
    void addModifiesRelationship(std::shared_ptr<Statement> s, std::shared_ptr<Variable> v);
    void addParentRelationship(std::shared_ptr<Statement> s1, std::shared_ptr<Statement> s2, bool isDirect);
};