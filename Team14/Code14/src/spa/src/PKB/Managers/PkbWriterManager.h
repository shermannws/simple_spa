#pragma once

#include <memory>

#include "AffectsRelationshipManager.h"
#include "PKB/Managers/AssignPatternManager.h"
#include "PKB/Managers/CFGManager.h"
#include "PKB/Managers/CallsRelationshipManager.h"
#include "PKB/Managers/EntitiesManager.h"
#include "PKB/Managers/FollowsRelationshipManager.h"
#include "PKB/Managers/IfPatternManager.h"
#include "PKB/Managers/ModifiesProcRelationshipManager.h"
#include "PKB/Managers/ModifiesRelationshipManager.h"
#include "PKB/Managers/NextRelationshipManager.h"
#include "PKB/Managers/ParentRelationshipManager.h"
#include "PKB/Managers/UsesProcRelationshipManager.h"
#include "PKB/Managers/UsesRelationshipManager.h"
#include "PKB/Managers/WhilePatternManager.h"
#include "PKB/PkbTypes.h"
#include "PKB/RelationshipStores/RelationshipStore.h"

/**
 * @brief The class is responsible for writing to the PKB.
 */
class PkbWriterManager {
private:
    /**
     * @brief The assignment manager.
     */
    std::shared_ptr<AssignPatternManager> assignmentManager;

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

    /**
     * @brief The calls relationship manager.
     */
    std::shared_ptr<CallsRelationshipManager> callsRelationshipManager;

    /**
     * @brief The modifies (proc-variable) relationship manager.
     */
    std::shared_ptr<ModifiesProcRelationshipManager> modifiesProcRelationshipManager;

    /**
     * @brief The uses (proc-variable) relationship manager.
     */
    std::shared_ptr<UsesProcRelationshipManager> usesProcRelationshipManager;

    /**
     * @brief The if pattern manager.
     */
    std::shared_ptr<IfPatternManager> ifPatternManager;

    /**
     * @brief The while pattern manager.
     */
    std::shared_ptr<WhilePatternManager> whilePatternManager;

    /**
     * @brief The next relationship manager.
     */
    std::shared_ptr<NextRelationshipManager> nextRelationshipManager;

    /**
     *
     */
    std::shared_ptr<CFGManager> cfgManager;

    /**
     * @brief The affects relationship manager.
     */
    std::shared_ptr<AffectsRelationshipManager> affectsRelationshipManager;

    /**
     * @brief The map of procedure to statements where statements modifies/uses whatever modifies/uses by the procedure.
     * @note This will be cleared after the transitive calculation is done.
     */
    RelationshipStore<Procedure, Statement> tempProcedureToStatementsMap;

    /**
     * @brief Triggers transitivity calculation for Calls* relationship.
     * @note This method should be called after all calls relationships have been added.
     */
    void triggerCallsTransitiveCalculation();

    /**
     * @brief Triggers transitivity calculation for Modifies and Uses (proc-var relationships)
     */
    void triggerProcToVarTransitiveCalculation();

    /**
     * @brief Triggers transitivity calculation for Modifies and Uses (stmt-var relationships) arising from call
     * statements
     */
    void triggerStmtToVarTransitiveCalculation();

public:
    /**
     * @brief Constructs a PkbWriterManager object.
     * @param assignmentManager The assignment manager.
     * @param entitiesManager The entities manager.
     * @param followsRelationshipManager The follows relationship manager.
     * @param usesRelationshipManager The uses relationship manager.
     * @param modifiesRelationshipManager The modifies relationship manager.
     * @param parentRelationshipManager The parent relationship manager.
     * @param callsRelatioShipManager The calls relationship manager.
     * @param modifiesProcRelationshipManager The modifies procedure relationship manager.
     * @param usesProcRelationshipManager The uses procedure relationship manager.
     * @param ifPatternManager The if pattern manager.
     * @param whilePatternManager The while pattern manager.
     * @param nextRelationshipManager The next relationship manager.
     * @param cfgManager The CFG manager.
     * @param affectsRelationshipManager The affects relationship manager.
     */
    PkbWriterManager(std::shared_ptr<AssignPatternManager> assignmentManager,
                     std::shared_ptr<EntitiesManager> entitiesManager,
                     std::shared_ptr<FollowsRelationshipManager> followsRelationshipManager,
                     std::shared_ptr<UsesRelationshipManager> usesRelationshipManager,
                     std::shared_ptr<ModifiesRelationshipManager> modifiesRelationshipManager,
                     std::shared_ptr<ParentRelationshipManager> parentRelationshipManager,
                     std::shared_ptr<CallsRelationshipManager> callsRelationshipManager,
                     std::shared_ptr<ModifiesProcRelationshipManager> modifiesProcRelationshipManager,
                     std::shared_ptr<UsesProcRelationshipManager> usesProcRelationshipManager,
                     std::shared_ptr<IfPatternManager> ifPatternManager,
                     std::shared_ptr<WhilePatternManager> whilePatternManager,
                     std::shared_ptr<NextRelationshipManager> nextRelationshipManager,
                     std::shared_ptr<CFGManager> cfgManager,
                     std::shared_ptr<AffectsRelationshipManager> affectsRelationshipManager);

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
    void addAssignPattern(std::shared_ptr<Statement> s, std::shared_ptr<Variable> lhs, std::shared_ptr<Expression> rhs);

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

    /**
     * @brief Adds a calls relationship to the PKB.
     * @param s1 The shared pointer to the first statement.
     * @param s2 The shared pointer to the second statement.
     */
    void addCallsRelationship(std::shared_ptr<Procedure> p1, std::shared_ptr<Procedure> p2);

    /**
     * @brief Adds a modifies procedure relationship to the PKB.
     * @param p The shared pointer to the procedure.
     * @param v The shared pointer to the variable.
     */
    void addModifiesProcRelationship(std::shared_ptr<Procedure> p, std::shared_ptr<Variable> v);

    /**
     * @brief Adds a uses procedure relationship to the PKB.
     * @param p The shared pointer to the procedure.
     * @param v The shared pointer to the variable.
     */
    void addUsesProcRelationship(std::shared_ptr<Procedure> p, std::shared_ptr<Variable> v);

    /**
     * @brief Adds an if pattern to the PKB.
     * @param s The shared pointer to the statement.
     * @param v The shared pointer to the vector of variables.
     */
    void addIfPattern(std::shared_ptr<Statement> s, std::shared_ptr<std::vector<std::shared_ptr<Variable>>> v);

    /**
     * @brief Adds a while pattern to the PKB.
     * @param s The shared pointer to the statement.
     * @param v The shared pointer to the vector of variables.
     */
    void addWhilePattern(std::shared_ptr<Statement> s, std::shared_ptr<std::vector<std::shared_ptr<Variable>>> v);

    /**
     * @brief Adds procedure to statements map into tempProcedureStatementMap.
     * @param p The procedure.
     * @param s The statements to be added.
     */
    void addProcedureToStatementsMap(std::shared_ptr<Procedure> p, std::vector<std::shared_ptr<Statement>> s);

    /**
     * @brief Triggers transitivity calculation for Relationships
     */
    void triggerTransitiveCalc();

    /**
     * @brief Adds a direct next relationship to the PKB.
     * @param s1 The shared pointer to the first statement.
     * @param s2 The shared pointer to the second statement.
     */
    void addNextRelationship(std::shared_ptr<Statement> s1, std::shared_ptr<Statement> s2);

    /**
     * @brief Sets the `cfgMap` received as argument as the CFGs for each procedures
     * @param cfgMap The map of procedure name to CFGNode
     */
    void setCFGMap(std::unordered_map<ProcedureName, std::shared_ptr<CFGNode>> cfgMap);

    /**
     * @brief Clears the PKB of any cache information that should not persist across queries
     */
    void clearCache();
};