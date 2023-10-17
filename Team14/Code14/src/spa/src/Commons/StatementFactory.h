#pragma once

#include <functional>
#include <memory>
#include <unordered_map>

#include "Commons/Entities/AssignStatement.h"
#include "Commons/Entities/CallStatement.h"
#include "Commons/Entities/IfStatement.h"
#include "Commons/Entities/PrintStatement.h"
#include "Commons/Entities/ReadStatement.h"
#include "Commons/Entities/Statement.h"
#include "Commons/Entities/StatementType.h"
#include "Commons/Entities/WhileStatement.h"
#include "SP/AST/Nodes/StatementNode.h"

class StatementFactory {
private:
    static std::unordered_map<StatementType, std::function<std::shared_ptr<Statement>(std::shared_ptr<StatementNode>)>>
            factoryMethodMap;

    static std::shared_ptr<AssignStatement> createAssignStatement(const std::shared_ptr<StatementNode> &node);

    static std::shared_ptr<CallStatement> createCallStatement(const std::shared_ptr<StatementNode> &node);

    static std::shared_ptr<PrintStatement> createPrintStatement(const std::shared_ptr<StatementNode> &node);

    static std::shared_ptr<ReadStatement> createReadStatement(const std::shared_ptr<StatementNode> &node);

    static std::shared_ptr<IfStatement> createIfStatement(const std::shared_ptr<StatementNode> &node);

    static std::shared_ptr<WhileStatement> createWhileStatement(const std::shared_ptr<StatementNode> &node);

public:
    static std::shared_ptr<Statement> createStatementFromStatementNode(const std::shared_ptr<StatementNode> &node);
};
