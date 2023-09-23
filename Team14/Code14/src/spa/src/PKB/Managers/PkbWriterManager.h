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

/**
 * @brief The class is responsible for writing to the PKB.
 */
class PkbWriterManager {
private:
    /**
     * @brief The assignment manager.
     */
    std::shared_ptr<AssignmentManager> assignmentManager;

    /**
     * @brief The entities manager.
     */
    std::shared_ptr<EntitiesManager> entitiesManager;

    /**
     * @brief The follows relationship manager.
     */
    std::shared_ptr<FollowsRelationshipManager> followsRelationshipManager;

    /**
     * @brief The uses relationship manager.
     */
    std::shared_ptr<UsesRelationshipManager> usesRelationshipManager;

    /**
     * @brief The modifies relationship manager.
     */
    std::shared_ptr<ModifiesRelationshipManager> modifiesRelationshipManager;

    /**
     * @brief The parent relationship manager.
     */
    std::shared_ptr<ParentRelationshipManager> parentRelationshipManager;
public:
    /**
     * @brief Constructs a PkbWriterManager object.
     * @param assignmentManager The assignment manager.
     * @param entitiesManager The entities manager.
     * @param followsRelationshipManager The follows relationship manager.
     * @param usesRelationshipManager The uses relationship manager.
     * @param modifiesRelationshipManager The modifies relationship manager.
     * @param parentRelationshipManager The parent relationship manager.
     */
    PkbWriterManager(
            std::shared_ptr<AssignmentManager> assignmentManager,
            std::shared_ptr<EntitiesManager> entitiesManager,
            std::shared_ptr<FollowsRelationshipManager> followsRelationshipManager,
            std::shared_ptr<UsesRelationshipManager> usesRelationshipManager,
            std::shared_ptr<ModifiesRelationshipManager> modifiesRelationshipManager,
            std::shared_ptr<ParentRelationshipManager> parentRelationshipManager
    );

    /**
     * @brief Adds a constant to the PKB.
     * @param c The shared pointer to the constant to be added.
     */
    void addConstant(std::shared_ptr<Constant> c);

    /**
     * @brief Adds a variable to the PKB.
     * @param v The shared pointer to the variable to be added.
     */
    void addVariable(std::shared_ptr<Variable> v);

    /**
     * @brief Adds a procedure to the PKB.
     * @param p The shared pointer to the procedure to be added.
     */
    void addProcedure(std::shared_ptr<Procedure> p);

    /**
     * @brief Adds a statement to the PKB.
     * @param s The shared pointer to the statement to be added.
     */
    void addStatement(std::shared_ptr<Statement> s);

    /**
     * @brief Adds a assign statement to the PKB.
     * @param s The shared pointer to the assign statement to be added.
     */
    void addAssignStatement(std::shared_ptr<Statement> s, std::shared_ptr<Variable> lhs, std::shared_ptr<Expression> rhs);

    /**
     * @brief Adds a follows relationship to the PKB.
     * @param s1 The shared pointer to the first statement.
     * @param s2 The shared pointer to the second statement.
     * @param isDirect A boolean value indicating if the follows relationship is direct.
     */
    void addFollowsRelationship(std::shared_ptr<Statement> s1, std::shared_ptr<Statement> s2, bool isDirect);

    /**
     * @brief Adds a uses relationship to the PKB.
     * @param s The shared pointer to the statement.
     * @param v The shared pointer to the variable.
     */
    void addUsesRelationship(std::shared_ptr<Statement> s, std::shared_ptr<Variable> v);

    /**
     * @brief Adds a modifies relationship to the PKB.
     * @param s The shared pointer to the statement.
     * @param v The shared pointer to the variable.
     */
    void addModifiesRelationship(std::shared_ptr<Statement> s, std::shared_ptr<Variable> v);

    /**
     * @brief Adds a parent relationship to the PKB.
     * @param s1 The shared pointer to the first statement.
     * @param s2 The shared pointer to the second statement.
     * @param isDirect A boolean value indicating if the parent relationship is direct.
     */
    void addParentRelationship(std::shared_ptr<Statement> s1, std::shared_ptr<Statement> s2, bool isDirect);
};