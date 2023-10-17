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
    /**
     * An unordered map of Statement type to the corresponding factory method.
     */
    static std::unordered_map<StatementType, std::function<std::shared_ptr<Statement>(std::shared_ptr<StatementNode>)>>
            factoryMethodMap;

    /**
     * Creates an AssignStatement from a StatementNode and returns a shared pointer to it.
     * @param node The StatementNode to create an AssignStatement for
     * @return An AssignStatement for the given StatementNode
     */
    static std::shared_ptr<AssignStatement> createAssignStatement(const std::shared_ptr<StatementNode> &node);

    /**
     * Creates a CallStatement from a StatementNode and returns a shared pointer to it.
     * @param node The StatementNode to create a CallStatement for
     * @return A CallStatement for the given StatementNode
     */
    static std::shared_ptr<CallStatement> createCallStatement(const std::shared_ptr<StatementNode> &node);

    /**
     * Creates a PrintStatement from a StatementNode and returns a shared pointer to it.
     * @param node The StatementNode to create a PrintStatement for
     * @return A PrintStatement for the given StatementNode
     */
    static std::shared_ptr<PrintStatement> createPrintStatement(const std::shared_ptr<StatementNode> &node);

    /**
     * Creates a ReadStatement from a StatementNode and returns a shared pointer to it.
     * @param node The StatementNode to create a ReadStatement for
     * @return A ReadStatement for the given StatementNode
     */
    static std::shared_ptr<ReadStatement> createReadStatement(const std::shared_ptr<StatementNode> &node);

    /**
     * Creates an IfStatement from a StatementNode and returns a shared pointer to it.
     * @param node The StatementNode to create an IfStatement for
     * @return An IfStatement for the given StatementNode
     */
    static std::shared_ptr<IfStatement> createIfStatement(const std::shared_ptr<StatementNode> &node);

    /**
     * Creates a WhileStatement from a StatementNode and returns a shared pointer to it.
     * @param node The StatementNode to create a WhileStatement for
     * @return A WhileStatement for the given StatementNode
     */
    static std::shared_ptr<WhileStatement> createWhileStatement(const std::shared_ptr<StatementNode> &node);

public:
    /**
     * Creates a Statement subclass from a StatementNode and returns a shared pointer to it.
     * Calls the correct factory method corresponding to the StatementType.
     * @param node The StatementNode to create a Statement for
     * @return A Statement subclass for the given StatementNode
     */
    static std::shared_ptr<Statement> createStatementFromStatementNode(const std::shared_ptr<StatementNode> &node);
};
