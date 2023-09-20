#pragma once

#include <memory>

#include "PKB/Managers/AssignmentManager.h"
#include "PKB/EntityStores/ConstantStore.h"
#include "PKB/EntityStores/ProcedureStore.h"
#include "PKB/EntityStores/StatementStore.h"
#include "PKB/EntityStores/VariableStore.h"
#include "PKB/RelationshipStores/FollowsRelationshipStore.h"
#include "PKB/RelationshipStores/UsesRelationshipStore.h"
#include "../Commons/Entities/Constant.h"
#include "../Commons/Entities/Procedure.h"
#include "../Commons/Entities/Variable.h"
#include "../Commons/Entities/Statement.h"
#include "PKB/Managers/PkbWriterManager.h"

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
    virtual void addAssignStatement(std::shared_ptr<Statement> s, std::shared_ptr<Variable> lhs, std::shared_ptr<std::string> rhs) = 0;

    /*!
     * Adds new Follows Relationship into the PKB
     */
    virtual void addFollowsRelationship(std::shared_ptr<Statement> s1, std::shared_ptr<Statement> s2, bool isDirect) = 0;

    /*!
     * Adds new Uses Relationship into the PKB
     */
    virtual void addUsesRelationship(std::shared_ptr<Statement> s, std::shared_ptr<Variable> v) = 0;

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
    virtual void addModifiesRelationship(std::shared_ptr<Statement> s, std::shared_ptr<Variable> v) = 0;
};