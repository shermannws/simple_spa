#pragma once

#include <memory>

#include "Commons/Entities/Constant.h"
#include "Commons/Entities/Procedure.h"
#include "Commons/Entities/Statement.h"
#include "Commons/Entities/Variable.h"
#include "PKB/EntityStores/ConstantStore.h"
#include "PKB/EntityStores/ProcedureStore.h"
#include "PKB/EntityStores/StatementStore.h"
#include "PKB/EntityStores/VariableStore.h"
#include "PKB/Managers/AssignPatternManager.h"
#include "PKB/Managers/PkbWriterManager.h"
#include "PKB/PkbTypes.h"
#include "PKB/RelationshipStores/FollowsRelationshipStore.h"
#include "PKB/RelationshipStores/UsesRelationshipStore.h"

/**
 * @brief The facade abstract class for writing from the PKB
 */
class PkbWriter {
public:
    /*!
     * Adds new Constant Entity into the PKB
     */
    virtual void addConstant(std::shared_ptr<Constant> c) = 0;

    /*!
     * Adds new Variable Entity into the PKB
     */
    virtual void addVariable(std::shared_ptr<Variable> v) = 0;

    /*!
     * Adds new Procedure Entity into the PKB
     */
    virtual void addProcedure(std::shared_ptr<Procedure> p) = 0;

    /*!
     * Adds new Print Statement Entity into the PKB
     */
    virtual void addPrintStatement(std::shared_ptr<Statement> s) = 0;

    /*!
     * Adds new Read Statement Entity into the PKB
     */
    virtual void addReadStatement(std::shared_ptr<Statement> s) = 0;

    /*!
     * Adds new Assign Statement Entity into the PKB
     */
    virtual void addAssignStatement(std::shared_ptr<Statement> s) = 0;

    /*!
     * Add new Assign Pattern into the PKB
     */
    virtual void addAssignPattern(std::shared_ptr<Statement> s,
                                  std::shared_ptr<Variable> lhs,
                                  std::shared_ptr<Expression> rhs) = 0;

    /*!
     * Adds new Follows Relationship into the PKB
     */
    virtual void addFollowsRelationship(std::shared_ptr<Statement> s1,
                                        std::shared_ptr<Statement> s2,
                                        bool isDirect) = 0;

    /*!
     * Adds new Uses Relationship into the PKB
     */
    virtual void addUsesRelationship(std::shared_ptr<Statement> s,
                                     std::shared_ptr<Variable> v) = 0;

    /*!
     * Adds new Call Statement Entity into the PKB
     */
    virtual void addCallStatement(std::shared_ptr<Statement> s) = 0;

    /*!
     * Adds new If Statement Entity into the PKB
     */
    virtual void addIfStatement(std::shared_ptr<Statement> s) = 0;

    /*!
     * Adds new While Statement Entity into the PKB
     */
    virtual void addWhileStatement(std::shared_ptr<Statement> s) = 0;

    /*!
     * Adds new Modifies Relationship into the PKB
     */
    virtual void addModifiesRelationship(std::shared_ptr<Statement> s,
                                         std::shared_ptr<Variable> v) = 0;

    /*!
     * Adds new Parent Relationship into the PKB
     */
    virtual void addParentRelationship(std::shared_ptr<Statement> s1,
                                       std::shared_ptr<Statement> s2,
                                       bool isDirect) = 0;

    /*!
     * Adds new Calls Relationship into the PKB
     */
    virtual void addCallsRelationship(std::shared_ptr<Procedure> p1,
                                      std::shared_ptr<Procedure> p2) = 0;

    /*!
     * Stores a map of procedures to a vector of statements that modifies/uses
     * whatever the procedure modifies/uses
     */
    virtual void
    addProcedureToStatementsMap(std::shared_ptr<Procedure> p,
                                std::vector<std::shared_ptr<Statement>> s) = 0;

    /*!
     * Triggers transitivity calculation for Relationships
     */
    virtual void triggerTransitiveCalc() = 0;

    /*!
     * Adds new Modifies (Procedure-Variable) Relationship into the PKB
     */
    virtual void addModifiesProcRelationship(std::shared_ptr<Procedure> p,
                                             std::shared_ptr<Variable> v) = 0;

    /*!
     * Adds new Uses (Procedure-Variable) Relationship into the PKB
     */
    virtual void addUsesProcRelationship(std::shared_ptr<Procedure> p,
                                         std::shared_ptr<Variable> v) = 0;

    /*!
     * Adds new Next Relationship into the PKB
     */
    virtual void addNextRelationship(std::shared_ptr<Statement> s1,
                                     std::shared_ptr<Statement> s2) = 0;

    /*!
     * Sets the `cfgMap` received as argument as the CFGs for each procedures
     */
    virtual void
    setCFGMap(std::unordered_map<ProcedureName, std::shared_ptr<CFGNode>>
                      cfgMap) = 0;

    /*!
     * Clears any Cache in the PKB that is used for Query Processing
     *
     */
    virtual void clearCache() = 0;

    /*!
     * Adds new If Pattern into the PKB
     */
    virtual void
    addIfPattern(std::shared_ptr<Statement> s,
                 std::shared_ptr<std::vector<std::shared_ptr<Variable>>> v) = 0;

    /*!
     * Adds new While Pattern into the PKB
     */
    virtual void addWhilePattern(
            std::shared_ptr<Statement> s,
            std::shared_ptr<std::vector<std::shared_ptr<Variable>>> v) = 0;
};