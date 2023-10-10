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
    static bool isSameAST(const std::shared_ptr<ProgramNode>& firstAST, const std::shared_ptr<ProgramNode>& secondAST);

    static bool isSameProcedure(const std::shared_ptr<ProcedureNode>& firstProc, const std::shared_ptr<ProcedureNode>& secondProc);

    static bool isSameStatementList(
            const std::shared_ptr<StatementListNode>& firstStatementList,
            const std::shared_ptr<StatementListNode>& secondStatementList);

    static bool isSameAssign(const std::shared_ptr<AssignNode>& firstAssign, const std::shared_ptr<AssignNode>& secondAssign);

    static bool isSamePrint(const std::shared_ptr<PrintNode>& firstPrint, const std::shared_ptr<PrintNode>& secondPrint);

    static bool isSameRead(const std::shared_ptr<ReadNode>& firstRead, const std::shared_ptr<ReadNode>& secondRead);

    static bool isSameWhile(const std::shared_ptr<WhileNode>& firstWhile, const std::shared_ptr<WhileNode>& secondWhile);

    static bool isSameIf(const std::shared_ptr<IfNode>& firstIf, const std::shared_ptr<IfNode>& secondIf);

    static bool isSameCall(const std::shared_ptr<CallNode>& firstCall, const std::shared_ptr<CallNode>& secondCall);

    static bool isSameExpression(const std::shared_ptr<ExpressionNode>& firstExpr, const std::shared_ptr<ExpressionNode>& secondExpr);

    static bool isSameCondExpression(const std::shared_ptr<ConditionalExpressionNode>& firstExpr, const std::shared_ptr<ConditionalExpressionNode>& secondExpr);
private:
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
