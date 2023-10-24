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

class EntityFactory {
private:
    /**
     * An unordered map to cache Statement subclasses created.
     */
    static std::unordered_map<StatementNumber, std::shared_ptr<Statement>> statementCache;

    /**
     * An unordered map to cache Statement subclasses created.
     */
    static std::unordered_map<VariableName, std::shared_ptr<Variable>> variableCache;

    /**
     * An unordered map to cache Statement subclasses created.
     */
    static std::unordered_map<ProcedureName, std::shared_ptr<Procedure>> procedureCache;

    /**
     * An unordered map of Statement type to the corresponding factory method that takes in a StatementNode.
     */
    static std::unordered_map<StatementType, std::function<std::shared_ptr<Statement>(std::shared_ptr<StatementNode>)>>
            nodeFactoryMethodMap;

    /**
     * An unordered map of Statement type to the corresponding factory method.
     */
    static std::unordered_map<StatementType,
                              std::function<std::shared_ptr<Statement>(StatementNumber, const AttrValue &)>>
            factoryMethodMap;

    /**
     * Creates an AssignStatement from a StatementNode and returns a shared pointer to it.
     * @param node The StatementNode to create an AssignStatement for
     * @return An AssignStatement for the given StatementNode
     */
    static std::shared_ptr<AssignStatement> createAssignStatementFromNode(const std::shared_ptr<StatementNode> &node);

    /**
     * Creates a CallStatement from a StatementNode and returns a shared pointer to it.
     * @param node The StatementNode to create a CallStatement for
     * @return A CallStatement for the given StatementNode
     */
    static std::shared_ptr<CallStatement> createCallStatementFromNode(const std::shared_ptr<StatementNode> &node);

    /**
     * Creates a PrintStatement from a StatementNode and returns a shared pointer to it.
     * @param node The StatementNode to create a PrintStatement for
     * @return A PrintStatement for the given StatementNode
     */
    static std::shared_ptr<PrintStatement> createPrintStatementFromNode(const std::shared_ptr<StatementNode> &node);

    /**
     * Creates a ReadStatement from a StatementNode and returns a shared pointer to it.
     * @param node The StatementNode to create a ReadStatement for
     * @return A ReadStatement for the given StatementNode
     */
    static std::shared_ptr<ReadStatement> createReadStatementFromNode(const std::shared_ptr<StatementNode> &node);

    /**
     * Creates an IfStatement from a StatementNode and returns a shared pointer to it.
     * @param node The StatementNode to create an IfStatement for
     * @return An IfStatement for the given StatementNode
     */
    static std::shared_ptr<IfStatement> createIfStatementFromNode(const std::shared_ptr<StatementNode> &node);

    /**
     * Creates a WhileStatement from a StatementNode and returns a shared pointer to it.
     * @param node The StatementNode to create a WhileStatement for
     * @return A WhileStatement for the given StatementNode
     */
    static std::shared_ptr<WhileStatement> createWhileStatementFromNode(const std::shared_ptr<StatementNode> &node);

    /**
     * Creates an AssignStatement. Some parameters are redundant to conform to the function shape of the
     * factoryMethodMap.
     * @param statementNumber The statement number of the AssignStatement
     * @param attrValue The attribute value of the AssignStatement (Redundant)
     * @return An AssignStatement
     */
    static std::shared_ptr<AssignStatement> createAssignStatement(StatementNumber statementNumber,
                                                                  const AttrValue &attrValue);

    /**
     * Creates a CallStatement. Some parameters are redundant to conform to the function shape of the factoryMethodMap.
     * @param statementNumber The statement number of the CallStatement
     * @param procName The name of the procedure called
     * @return A CallStatement
     */
    static std::shared_ptr<CallStatement> createCallStatement(StatementNumber statementNumber,
                                                              const AttrValue &procName);

    /**
     * Creates a PrintStatement. Some parameters are redundant to conform to the function shape of the factoryMethodMap.
     * @param statementNumber The statement number of the PrintStatement
     * @param varName The attribute value of the PrintStatement
     * @return A PrintStatement
     */
    static std::shared_ptr<PrintStatement> createPrintStatement(StatementNumber statementNumber,
                                                                const AttrValue &varName);

    /**
     * Creates a ReadStatement. Some parameters are redundant to conform to the function shape of the factoryMethodMap.
     * @param statementNumber The statement number of the ReadStatement
     * @param varName The attribute value of the ReadStatement
     * @return A ReadStatement
     */
    static std::shared_ptr<ReadStatement> createReadStatement(StatementNumber statementNumber,
                                                              const AttrValue &varName);

    /**
     * Creates an IfStatement. Some parameters are redundant to conform to the function shape of the factoryMethodMap.
     * @param statementNumber The statement number of the IfStatement
     * @param attrValue The attribute value of the IfStatement (Redundant)
     * @return An IfStatement
     */
    static std::shared_ptr<IfStatement> createIfStatement(StatementNumber statementNumber, const AttrValue &attrValue);

    /**
     * Creates a WhileStatement. Some parameters are redundant to conform to the function shape of the factoryMethodMap.
     * @param statementNumber The statement number of the WhileStatement
     * @param attrValue The attribute value of the WhileStatement (Redundant)
     * @return A WhileStatement
     */
    static std::shared_ptr<WhileStatement> createWhileStatement(StatementNumber statementNumber,
                                                                const AttrValue &attrValue);

public:
    /**
     * Checks the Statement cache for a Statement subclass object corresponding to varName.
     * If it has not been created, creates a Statement subclass from a StatementNode and returns a shared pointer to it.
     * Calls the correct factory method corresponding to the StatementType.
     * @param node The StatementNode to create a Statement for
     * @return A Statement subclass for the given StatementNode
     */
    static std::shared_ptr<Statement> createStatementFromStatementNode(const std::shared_ptr<StatementNode> &node);

    /**
     * Checks the Statement cache for a Statement subclass object corresponding to varName.
     * If it has not been created, creates a Statement subclass and returns a shared pointer to it.
     * Calls the correct factory method corresponding to the StatementType.
     * @param statementNumber The statement number of the Statement
     * @param statementType The type of the Statement
     * @param attrValue The attribute value of the Statement
     * @return A Statement subclass corresponding to the statementType
     */
    static std::shared_ptr<Statement> createStatement(StatementNumber statementNumber, StatementType statementType,
                                                      AttrValue attrValue);

    /**
     * Checks the Variable cache for a Variable object corresponding to varName.
     * If it has not been created, creates a Variable object and returns a shared pointer to it.
     * @param varName The variable name of the Variable object
     * @return The Variable object with the given variable name
     */
    static std::shared_ptr<Variable> createVariable(VariableName varName);

    /**
     * Checks the Procedure cache for a Procedure object corresponding to varName.
     * If it has not been created, creates a Procedure object and returns a shared pointer to it.
     * @param procName The procedure name of the Procedure object
     * @return The Procedure object with the given procedure name
     */
    static std::shared_ptr<Procedure> createProcedure(ProcedureName procName);
};
