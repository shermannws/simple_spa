#pragma once

#include <memory>

#include "PKB/Managers/AssignmentManager.h"
#include "PKB/EntityStorage/ConstantStore.h"
#include "PKB/EntityStorage/ProcedureStore.h"
#include "PKB/EntityStorage/StatementStore.h"
#include "PKB/EntityStorage/VariableStore.h"
#include "PKB/RelationshipStorage/FollowsRelationshipStore.h"
#include "PKB/RelationshipStorage/UsesRelationshipStore.h"
#include "../Commons/Entities/Constant.h"
#include "../Commons/Entities/Procedure.h"
#include "../Commons/Entities/Variable.h"
#include "../Commons/Entities/Statement.h"
#include "PKB/Managers/PkbWriterManager.h"

class PkbWriter {
private:
    std::shared_ptr<PkbWriterManager> writerManager;
public:
    PkbWriter(std::shared_ptr<PkbWriterManager> writerManager);

    void addConstant(std::shared_ptr<Constant> c);
    void addVariable(std::shared_ptr<Variable> v);
    void addProcedure(std::shared_ptr<Procedure> p);

    void addPrintStatement(std::shared_ptr<Statement> s);
    void addReadStatement(std::shared_ptr<Statement> s);
    void addAssignStatement(std::shared_ptr<Statement> s, std::shared_ptr<Variable> lhs, std::shared_ptr<std::string> rhs);

    void addFollowsRelationship(std::shared_ptr<Statement> s1, std::shared_ptr<Statement> s2);
    void addUsesRelalationship(std::shared_ptr<Statement> s, std::shared_ptr<Variable> v);
};