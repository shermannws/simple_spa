#pragma once

#include <memory>

#include "PKB/Managers/PkbWriterManager.h"
#include "PKB/PkbWriter.h"
#include "PKB/PkbTypes.h"

/**
 * @brief The facade class is responsible for writing from the PKB.
 */
class PkbConcreteWriter : public PkbWriter {
private:
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
    void addAssignStatement(std::shared_ptr<Statement> s, std::shared_ptr<Variable> lhs, std::shared_ptr<Expression> rhs) override;

    /*!
     * Adds new Follows Relationship into the PKB
     */
    void addFollowsRelationship(std::shared_ptr<Statement> s1, std::shared_ptr<Statement> s2, bool isDirect) override;

    /*!
     * Adds new Uses Relationship into the PKB
     */
    void addUsesRelationship(std::shared_ptr<Statement> s, std::shared_ptr<Variable> v) override;

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
    void addModifiesRelationship(std::shared_ptr<Statement> s, std::shared_ptr<Variable> v) override;

    /*!
     * Adds new Parent Relationship into the PKB
     */
    void addParentRelationship(std::shared_ptr<Statement> s1, std::shared_ptr<Statement> s2, bool isDirect) override;

    /*!
	 * Adds new Calls Relationship into the PKB
	 */
    void addCallsRelationship(std::shared_ptr<Procedure> p1, std::shared_ptr<Procedure> p2) override;

    /*!
     * Stores a map of procedures to a vector of statements that modifies/uses whatever the procedure modifies/uses
     */
    virtual void addProcedureToStatementsMap(std::shared_ptr<Procedure> p, std::vector<std::shared_ptr<Statement>> s) override;

    /*!
     * Triggers transitivity calculation for Relationships (Calls*)
     */
    virtual void triggerTransitiveCalc() override;

    /*!
     * Adds new Modifies (Procedure-Variable) Relationship into the PKB
     */
    void addModifiesProcRelationship(std::shared_ptr<Procedure> p, std::shared_ptr<Variable> v) override;

    /*!
     * Adds new Uses (Procedure-Variable) Relationship into the PKB
     */
    void addUsesProcRelationship(std::shared_ptr<Procedure> p, std::shared_ptr<Variable> v) override;

};