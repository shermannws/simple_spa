#pragma once

#include <memory>
#include <unordered_map>
#include <functional>

#include "Commons/AppConstants.h"
#include "SP/AST/Nodes/ProgramNode.h"
#include "SP/AST/Nodes/ProcedureNode.h"
#include "SP/AST/Nodes/StatementListNode.h"
#include "SP/AST/Nodes/AssignNode.h"
#include "SP/AST/Nodes/PrintNode.h"
#include "SP/AST/Nodes/ReadNode.h"
#include "SP/AST/Nodes/WhileNode.h"
#include "SP/AST/Nodes/IfNode.h"
#include "SP/AST/Nodes/CallNode.h"
#include "SP/AST/Nodes/ExpressionNode.h"
#include "SP/AST/Nodes/ConditionalExpressionNode.h"

class ASTComparer {
public:
    /**
     * Checks if two ASTs are equivalent.
     * @param firstAST Root node of the first AST
     * @param secondAST Root node of the second AST
     * @return True if both are equivalent, else false
     */
    static bool isSameAST(const std::shared_ptr<ProgramNode>& firstAST, const std::shared_ptr<ProgramNode>& secondAST);

    /**
     * Checks if the two procedures are equivalent.
     * @param firstProc Root node of the first procedure
     * @param secondProc Root node of the second procedure
     * @return True if both are equivalent, else false
     */
    static bool isSameProcedure(const std::shared_ptr<ProcedureNode>& firstProc, const std::shared_ptr<ProcedureNode>& secondProc);

    /**
     * Checks if the two statement lists are equivalent.
     * @param firstStatementList Root node of the first statement list
     * @param secondStatementList Root node of the second statement list
     * @return True if both are equivalent, else false
     */
    static bool isSameStatementList(
            const std::shared_ptr<StatementListNode>& firstStatementList,
            const std::shared_ptr<StatementListNode>& secondStatementList);

    /**
     * Checks if the two assign statements are equivalent.
     * @param firstAssign Root node of the first assign statement
     * @param secondAssign Root node of the second assign statement
     * @return True if both are equivalent, else false
     */
    static bool isSameAssign(const std::shared_ptr<AssignNode>& firstAssign, const std::shared_ptr<AssignNode>& secondAssign);

    /**
     * Checks if the two print statements are equivalent.
     * @param firstPrint Root node of the first print statement
     * @param secondPrint Root node of the second print statement
     * @return True if both are equivalent, else false
     */
    static bool isSamePrint(const std::shared_ptr<PrintNode>& firstPrint, const std::shared_ptr<PrintNode>& secondPrint);

    /**
     * Checks if the two read statements are equivalent.
     * @param firstRead Root node of the first read statement
     * @param secondRead Root node of the second read statement
     * @return True if both are equivalent, else false
     */
    static bool isSameRead(const std::shared_ptr<ReadNode>& firstRead, const std::shared_ptr<ReadNode>& secondRead);

    /**
     * Checks if the two while statements are equivalent.
     * @param firstWhile Root node of the first while statement
     * @param secondWhile Root node of the second while statement
     * @return True if both are equivalent, else false
     */
    static bool isSameWhile(const std::shared_ptr<WhileNode>& firstWhile, const std::shared_ptr<WhileNode>& secondWhile);

    /**
     * Checks if the two if statements are equivalent.
     * @param firstIf Root node of the first if statement
     * @param secondIf Root node of the second if statement
     * @return True if both are equivalent, else false
     */
    static bool isSameIf(const std::shared_ptr<IfNode>& firstIf, const std::shared_ptr<IfNode>& secondIf);

    /**
     * Checks if the two call statements are equivalent.
     * @param firstCall Root node of the first call statement
     * @param secondCall Root node of the second call statement
     * @return True if both are equivalent, else false
     */
    static bool isSameCall(const std::shared_ptr<CallNode>& firstCall, const std::shared_ptr<CallNode>& secondCall);

    /**
     * Checks if the two expressions are equivalent.
     * @param firstExpr Root node of the first expression
     * @param secondExpr Root node of the second expression
     * @return True if both are equivalent, else false
     */
    static bool isSameExpression(const std::shared_ptr<ExpressionNode>& firstExpr, const std::shared_ptr<ExpressionNode>& secondExpr);

    /**
     * Checks if the two conditional expressions are equivalent.
     * @param firstExpr Root node of the first conditional expression
     * @param secondExpr Root node of the second conditional expression
     * @return True if both are equivalent, else false
     */
    static bool isSameCondExpression(const std::shared_ptr<ConditionalExpressionNode>& firstExpr, const std::shared_ptr<ConditionalExpressionNode>& secondExpr);

private:
    /**
     * Checks if the two statements have the same statement numbers.
     * @param firstStatement Root node of the first statement
     * @param secondStatement Root node of the second statement
     * @return True if both are equivalent, else false
     */
    static bool isSameStatementNumber(const std::shared_ptr<StatementNode>& firstStatement, const std::shared_ptr<StatementNode>& secondStatement);

    /**
     * Map of StatementNodeType to its corresponding isSame* methods.
     * The lambda functions cast the StatementNode arguments to the correct type before passing it to the isSame* methods.
     */
    inline static std::unordered_map<StatementNodeType, std::function<bool(std::shared_ptr<StatementNode>, std::shared_ptr<StatementNode>)>>
    statementNodeTypeToStatementComparer = {
            { StatementNodeType::Assign, [](const std::shared_ptr<StatementNode>& s1, const std::shared_ptr<StatementNode>& s2) -> bool {
                    return isSameAssign(std::dynamic_pointer_cast<AssignNode>(s1), std::dynamic_pointer_cast<AssignNode>(s2));
                }
            },
            { StatementNodeType::Print, [](const std::shared_ptr<StatementNode> &s1, const std::shared_ptr<StatementNode> &s2) -> bool {
                    return isSamePrint(std::dynamic_pointer_cast<PrintNode>(s1), std::dynamic_pointer_cast<PrintNode>(s2));
                }
            },
            { StatementNodeType::Read, [](const std::shared_ptr<StatementNode>& s1, const std::shared_ptr<StatementNode>& s2) -> bool {
                    return isSameRead(std::dynamic_pointer_cast<ReadNode>(s1), std::dynamic_pointer_cast<ReadNode>(s2));
                }
            },
            { StatementNodeType::If, [](const std::shared_ptr<StatementNode>& s1, const std::shared_ptr<StatementNode>& s2) -> bool {
                    return isSameIf(std::dynamic_pointer_cast<IfNode>(s1), std::dynamic_pointer_cast<IfNode>(s2));
                }
            },
            { StatementNodeType::While, [](const std::shared_ptr<StatementNode>& s1, const std::shared_ptr<StatementNode>& s2) -> bool {
                    return isSameWhile(std::dynamic_pointer_cast<WhileNode>(s1), std::dynamic_pointer_cast<WhileNode>(s2));
                }
            },
            { StatementNodeType::Call, [](const std::shared_ptr<StatementNode>& s1, const std::shared_ptr<StatementNode>& s2) -> bool {
                    return isSameCall(std::dynamic_pointer_cast<CallNode>(s1), std::dynamic_pointer_cast<CallNode>(s2));
                }
            }
    };
};
