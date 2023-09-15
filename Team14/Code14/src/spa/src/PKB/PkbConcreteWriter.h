#pragma once

#include <memory>

#include "PKB/Managers/PkbWriterManager.h"
#include "PKB/PkbWriter.h"

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
    void addAssignStatement(std::shared_ptr<Statement> s, std::shared_ptr<Variable> lhs, std::shared_ptr<std::string> rhs) override;

    /*!
     * Adds new Follows Relationship into the PKB
     */
    void addFollowsRelationship(std::shared_ptr<Statement> s1, std::shared_ptr<Statement> s2) override;

    /*!
     * Adds new Uses Relationship into the PKB
     */
    void addUsesRelationship(std::shared_ptr<Statement> s, std::shared_ptr<Variable> v) override;
};