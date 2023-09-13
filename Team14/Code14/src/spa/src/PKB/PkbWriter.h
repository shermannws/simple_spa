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
private:
    std::shared_ptr<PkbWriterManager> writerManager;
public:
    /*!
     * Constructor for PkbWrtier Class
     */
    PkbWriter(std::shared_ptr<PkbWriterManager> writerManager);

    /*!
     * Adds new Constant Entity into the PKB
     */
    void addConstant(std::shared_ptr<Constant> c);

    /*!
     * Adds new Variable Entity into the PKB
     */
    void addVariable(std::shared_ptr<Variable> v);

    /*!
     * Adds new Procedure Entity into the PKB
     */
    void addProcedure(std::shared_ptr<Procedure> p);

    /*!
     * Adds new Print Statement Entity into the PKB
     */
    void addPrintStatement(std::shared_ptr<Statement> s);

    /*!
     * Adds new Read Statement Entity into the PKB
     */
    void addReadStatement(std::shared_ptr<Statement> s);

    /*!
     * Adds new Assign Statement Entity into the PKB
     */
    void addAssignStatement(std::shared_ptr<Statement> s, std::shared_ptr<Variable> lhs, std::shared_ptr<std::string> rhs);

    /*!
     * Adds new Follows Relationship into the PKB
     */
    void addFollowsRelationship(std::shared_ptr<Statement> s1, std::shared_ptr<Statement> s2);

    /*!
     * Adds new Uses Relationship into the PKB
     */
    void addUsesRelationship(std::shared_ptr<Statement> s, std::shared_ptr<Variable> v);
};