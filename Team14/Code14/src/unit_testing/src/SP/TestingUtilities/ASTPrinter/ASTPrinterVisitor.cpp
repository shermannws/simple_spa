#include <iostream>
#include <unordered_map>

#include "ASTPrinterVisitor.h"

ASTPrinterVisitor::ASTPrinterVisitor(std::shared_ptr<PkbWriter> pkbWriter) { this->pkbWriter = pkbWriter; }

void ASTPrinterVisitor::visitProgramNode(ProgramNode *node, std::vector<std::shared_ptr<Statement>> parents,
                                         std::shared_ptr<ASTNode> proc) const {
    std::cout << "main:program\n";
}

void ASTPrinterVisitor::visitProcedureNode(ProcedureNode *node, std::vector<std::shared_ptr<Statement>> parents,
                                           std::shared_ptr<ASTNode> proc) const {
    std::cout << node->getProcedureName() + ":proc\n";
}

void ASTPrinterVisitor::visitStatementListNode(StatementListNode *node, std::vector<std::shared_ptr<Statement>> parents,
                                               std::shared_ptr<ASTNode> proc) const {
    std::cout << ":stmtLst\n";
}

void ASTPrinterVisitor::visitAssignNode(AssignNode *node, std::vector<std::shared_ptr<Statement>> parents,
                                        std::shared_ptr<ASTNode> proc) const {
    std::cout << ":assign\n";
}

void ASTPrinterVisitor::visitReadNode(ReadNode *node, std::vector<std::shared_ptr<Statement>> parents,
                                      std::shared_ptr<ASTNode> proc) const {
    std::cout << ":read\n";
}

void ASTPrinterVisitor::visitPrintNode(PrintNode *node, std::vector<std::shared_ptr<Statement>> parents,
                                       std::shared_ptr<ASTNode> proc) const {
    std::cout << ":print\n";
}

void ASTPrinterVisitor::visitVariableNode(VariableNode *node, std::vector<std::shared_ptr<Statement>> parents,
                                          std::shared_ptr<ASTNode> proc) const {
    std::cout << node->getVarName() + ":var\n";
}

void ASTPrinterVisitor::visitConstantNode(ConstantNode *node, std::vector<std::shared_ptr<Statement>> parents,
                                          std::shared_ptr<ASTNode> proc) const {
    std::cout << node->getValue() + ":const\n";
}

void ASTPrinterVisitor::visitCallNode(CallNode *node, std::vector<std::shared_ptr<Statement>> parents,
                                      std::shared_ptr<ASTNode> proc) const {
    std::cout << node->getProcedureName() + ":call\n";
}

void ASTPrinterVisitor::visitIfNode(IfNode *node, std::vector<std::shared_ptr<Statement>> parents,
                                    std::shared_ptr<ASTNode> proc) const {
    std::cout << ":if\n";
}

void ASTPrinterVisitor::visitWhileNode(WhileNode *node, std::vector<std::shared_ptr<Statement>> parents,
                                       std::shared_ptr<ASTNode> proc) const {
    std::cout << ":while\n";
}

void ASTPrinterVisitor::visitArithmeticExpressionNode(ArithmeticExpressionNode *node,
                                                      std::vector<std::shared_ptr<Statement>> parents,
                                                      std::shared_ptr<ASTNode> proc) const {
    std::unordered_map<ArithmeticOperatorType, std::string> stringMap = {{ArithmeticOperatorType::Plus, ":plus"},
                                                                         {ArithmeticOperatorType::Minus, ":minus"},
                                                                         {ArithmeticOperatorType::Times, ":times"},
                                                                         {ArithmeticOperatorType::Divide, ":divide"},
                                                                         {ArithmeticOperatorType::Modulo, ":modulo"}};
    assert(stringMap.find(node->getOperatorType()) != stringMap.end());
    std::cout << stringMap[node->getOperatorType()] << "\n";
}

void ASTPrinterVisitor::visitBinaryConditionalExpressionNode(BinaryConditionalExpressionNode *node,
                                                             std::vector<std::shared_ptr<Statement>> parents,
                                                             std::shared_ptr<ASTNode> proc) const {
    std::cout << (node->getBinaryConditionalExpressionType() == BinaryConditionalExpressionType::And ? ":and" : ":or")
              << "\n";
}

void ASTPrinterVisitor::visitUnaryConditionalExpressionNode(UnaryConditionalExpressionNode *node,
                                                            std::vector<std::shared_ptr<Statement>> parents,
                                                            std::shared_ptr<ASTNode> proc) const {
    std::cout << ":not\n";
}

void ASTPrinterVisitor::visitRelativeExpressionNode(RelativeExpressionNode *node,
                                                    std::vector<std::shared_ptr<Statement>> parents,
                                                    std::shared_ptr<ASTNode> proc) const {
    std::unordered_map<ComparisonOperatorType, std::string> stringMap = {
            {ComparisonOperatorType::GreaterThan, ":greater"},
            {ComparisonOperatorType::GreaterThanEqual, ":greaterEqual"},
            {ComparisonOperatorType::LessThan, ":less"},
            {ComparisonOperatorType::LessThanEqual, ":lessEqual"},
            {ComparisonOperatorType::Equal, ":eq"},
            {ComparisonOperatorType::NotEqual, ":neq"}};
    assert(stringMap.find(node->getComparisonOperatorType()) != stringMap.end());
    std::cout << stringMap[node->getComparisonOperatorType()] << "\n";
}