#include <iostream>
#include <unordered_map>

#include "ASTPrinterVisitor.h"

ASTPrinterVisitor::ASTPrinterVisitor(std::shared_ptr<PkbWriter> pkbWriter) { this->pkbWriter = pkbWriter; }


void ASTPrinterVisitor::visitProgramNode(const std::shared_ptr<ProgramNode> &node,
                                         std::vector<std::shared_ptr<Statement>> parents,
                                         std::shared_ptr<Procedure> proc) const {
    std::cout << "main:program\n";
}

void ASTPrinterVisitor::visitProcedureNode(const std::shared_ptr<ProcedureNode> &node,
                                           std::vector<std::shared_ptr<Statement>> parents,
                                           std::shared_ptr<Procedure> proc) const {
    std::cout << node->getProcedureName() + ":proc\n";
}

void ASTPrinterVisitor::visitStatementListNode(const std::shared_ptr<StatementListNode> &node,
                                               std::vector<std::shared_ptr<Statement>> parents,
                                               std::shared_ptr<Procedure> proc) const {
    std::cout << ":stmtLst\n";
}

void ASTPrinterVisitor::visitAssignNode(const std::shared_ptr<AssignNode> &node,
                                        std::vector<std::shared_ptr<Statement>> parents,
                                        std::shared_ptr<Procedure> proc) const {
    std::cout << ":assign\n";
}

void ASTPrinterVisitor::visitReadNode(const std::shared_ptr<ReadNode> &node,
                                      std::vector<std::shared_ptr<Statement>> parents,
                                      std::shared_ptr<Procedure> proc) const {
    std::cout << ":read\n";
}

void ASTPrinterVisitor::visitPrintNode(const std::shared_ptr<PrintNode> &node,
                                       std::vector<std::shared_ptr<Statement>> parents,
                                       std::shared_ptr<Procedure> proc) const {
    std::cout << ":print\n";
}

void ASTPrinterVisitor::visitVariableNode(const std::shared_ptr<VariableNode> &node,
                                          std::vector<std::shared_ptr<Statement>> parents,
                                          std::shared_ptr<Procedure> proc) const {
    std::cout << node->getVarName() + ":var\n";
}

void ASTPrinterVisitor::visitConstantNode(const std::shared_ptr<ConstantNode> &node,
                                          std::vector<std::shared_ptr<Statement>> parents,
                                          std::shared_ptr<Procedure> proc) const {
    std::cout << node->getValue() + ":const\n";
}

void ASTPrinterVisitor::visitCallNode(const std::shared_ptr<CallNode> &node,
                                      std::vector<std::shared_ptr<Statement>> parents,
                                      std::shared_ptr<Procedure> proc) const {
    std::cout << node->getProcedureName() + ":call\n";
}

void ASTPrinterVisitor::visitIfNode(const std::shared_ptr<IfNode> &node,
                                    std::vector<std::shared_ptr<Statement>> parents,
                                    std::shared_ptr<Procedure> proc) const {
    std::cout << ":if\n";
}

void ASTPrinterVisitor::visitWhileNode(const std::shared_ptr<WhileNode> &node,
                                       std::vector<std::shared_ptr<Statement>> parents,
                                       std::shared_ptr<Procedure> proc) const {
    std::cout << ":while\n";
}

void ASTPrinterVisitor::visitArithmeticExpressionNode(const std::shared_ptr<ArithmeticExpressionNode> &node,
                                                      std::vector<std::shared_ptr<Statement>> parents,
                                                      std::shared_ptr<Procedure> proc) const {
    std::unordered_map<ArithmeticOperatorType, std::string> stringMap = {{ArithmeticOperatorType::Plus, ":plus"},
                                                                         {ArithmeticOperatorType::Minus, ":minus"},
                                                                         {ArithmeticOperatorType::Times, ":times"},
                                                                         {ArithmeticOperatorType::Divide, ":divide"},
                                                                         {ArithmeticOperatorType::Modulo, ":modulo"}};
    assert(stringMap.find(node->getOperatorType()) != stringMap.end());
    std::cout << stringMap[node->getOperatorType()] << "\n";
}

void ASTPrinterVisitor::visitBinaryConditionalExpressionNode(
        const std::shared_ptr<BinaryConditionalExpressionNode> &node, std::vector<std::shared_ptr<Statement>> parents,
        std::shared_ptr<Procedure> proc) const {
    std::cout << (node->getBinaryConditionalExpressionType() == BinaryConditionalExpressionType::And ? ":and" : ":or")
              << "\n";
}

void ASTPrinterVisitor::visitUnaryConditionalExpressionNode(const std::shared_ptr<UnaryConditionalExpressionNode> &node,
                                                            std::vector<std::shared_ptr<Statement>> parents,
                                                            std::shared_ptr<Procedure> proc) const {
    std::cout << ":not\n";
}

void ASTPrinterVisitor::visitRelativeExpressionNode(const std::shared_ptr<RelativeExpressionNode> &node,
                                                    std::vector<std::shared_ptr<Statement>> parents,
                                                    std::shared_ptr<Procedure> proc) const {
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