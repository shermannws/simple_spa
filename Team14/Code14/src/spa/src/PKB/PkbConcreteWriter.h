#pragma once

#include <memory>

#include "PKB/Managers/PkbWriterManager.h"
#include "PKB/PkbTypes.h"
#include "PKB/PkbWriter.h"

/**
 * @brief The facade class is responsible for writing from the PKB.
 */
class PkbConcreteWriter : public PkbWriter {
private:
    /**
     * @brief The PkbWriterManager that is used to write to the PKB.
     */
    std::shared_ptr<PkbWriterManager> writerManager;

public:
    /*!
     * Constructor for PkbConcreteWriter Class
     */
    PkbConcreteWriter(std::shared_ptr<PkbWriterManager> writerManager);

    /*!
     * Adds new Constant Entity into the PKB
     */
    void addConstant(std::shared_ptr<Constant> c) override;

    /*!
     * Adds new Variable Entity into the PKB
     */
    void addVariable(std::shared_ptr<Variable> v) override;

    /*!
     * Adds new Procedure Entity into the PKB
     */
    void addProcedure(std::shared_ptr<Procedure> p) override;

    /*!
     * Adds new Print Statement Entity into the PKB
     */
    void addPrintStatement(std::shared_ptr<Statement> s) override;

    /*!
     * Adds new Read Statement Entity into the PKB
     */
    void addReadStatement(std::shared_ptr<Statement> s) override;

    /*!
     * Adds new Assign Statement Entity into the PKB
     */
    void addAssignStatement(std::shared_ptr<Statement> s) override;

    /*!
     * Add new Assign Pattern into the PKB
     */
    void addAssignPattern(std::shared_ptr<Statement> s,
                          std::shared_ptr<Variable> lhs,
                          std::shared_ptr<Expression> rhs) override;

    /*!
     * Adds new Follows Relationship into the PKB
     */
    void addFollowsRelationship(std::shared_ptr<Statement> s1,
                                std::shared_ptr<Statement> s2,
                                bool isDirect) override;

    /*!
     * Adds new Uses Relationship into the PKB
     */
    void addUsesRelationship(std::shared_ptr<Statement> s,
                             std::shared_ptr<Variable> v) override;

    /*!
     * Adds new Call Statement Entity into the PKB
     */
    void addCallStatement(std::shared_ptr<Statement> s) override;

    /*!
     * Adds new If Statement Entity into the PKB
     */
    void addIfStatement(std::shared_ptr<Statement> s) override;

    /*!
     * Adds new While Statement Entity into the PKB
     */
    void addWhileStatement(std::shared_ptr<Statement> s) override;

    /*!
     * Adds new Modifies Relationship into the PKB
     */
    void addModifiesRelationship(std::shared_ptr<Statement> s,
                                 std::shared_ptr<Variable> v) override;

    /*!
     * Adds new Parent Relationship into the PKB
     */
    void addParentRelationship(std::shared_ptr<Statement> s1,
                               std::shared_ptr<Statement> s2,
                               bool isDirect) override;

    /*!
     * Adds new Calls Relationship into the PKB
     */
    void addCallsRelationship(std::shared_ptr<Procedure> p1,
                              std::shared_ptr<Procedure> p2) override;

    /*!
     * Adds new If Pattern into the PKB
     */
    void addIfPattern(
            std::shared_ptr<Statement> s,
            std::shared_ptr<std::vector<std::shared_ptr<Variable>>> v) override;

    /*!
     * Adds new While Pattern into the PKB
     */
    void addWhilePattern(
            std::shared_ptr<Statement> s,
            std::shared_ptr<std::vector<std::shared_ptr<Variable>>> v) override;

    /*!
     * Stores a map of procedures to a vector of statements that modifies/uses
     * whatever the procedure modifies/uses
     */
    void addProcedureToStatementsMap(
            std::shared_ptr<Procedure> p,
            std::vector<std::shared_ptr<Statement>> s) override;

    /*!
     * Triggers transitivity calculation for Relationships
     */
    void triggerTransitiveCalc() override;

    /*!
     * Adds new Modifies (Procedure-Variable) Relationship into the PKB
     */
    void addModifiesProcRelationship(std::shared_ptr<Procedure> p,
                                     std::shared_ptr<Variable> v) override;

    /*!
     * Adds new Uses (Procedure-Variable) Relationship into the PKB
     */
    void addUsesProcRelationship(std::shared_ptr<Procedure> p,
                                 std::shared_ptr<Variable> v) override;

    /*!
     * Adds new Next Relationship into the PKB
     */
    void addNextRelationship(std::shared_ptr<Statement> s1,
                             std::shared_ptr<Statement> s2) override;

    /*!
     * Sets the `cfgMap` received as argument as the CFGs for each procedures
     */
    void setCFGMap(std::unordered_map<ProcedureName, std::shared_ptr<CFGNode>>
                           cfgMap) override;

    /*!
     * Clears any Cache in the PKB that is used for Query Processing
     */
    void clearCache() override;
};