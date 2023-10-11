#include "CFGBuilder.h"
#include "Commons/StatementTypeFactory.h"
#include "Commons/CFG/DummyCFGNode.h"
#include "SP/AST/Nodes/StatementNode.h"

std::unordered_map<ProcedureName, std::unordered_map<Statement, std::shared_ptr<CFGNode>>>
CFGBuilder::buildAllCFG(const std::shared_ptr<ProgramNode>& ASTRootNode) {
    std::unordered_map<ProcedureName, std::unordered_map<Statement, std::shared_ptr<CFGNode>>> procedureToCFGMap;
    for (auto& procedureNode : ASTRootNode->getProcedures()) {
        ProcedureName procedureName = procedureNode->getProcedureName();
        procedureToCFGMap[procedureName] = buildCFGForProcedure(procedureNode);
    }

    return procedureToCFGMap;
}

std::unordered_map<Statement, std::shared_ptr<CFGNode>>
CFGBuilder::buildCFGForProcedure(const std::shared_ptr<ProcedureNode>& procedureNode) {
    std::unordered_map<Statement, std::shared_ptr<CFGNode>> statementToCFGNodeMap;
    buildStatementListSubgraph(statementToCFGNodeMap, procedureNode->getStatementList());

    return statementToCFGNodeMap;
}

std::pair<std::shared_ptr<CFGNode>, std::shared_ptr<CFGNode>>
CFGBuilder::buildStatementListSubgraph(std::unordered_map<Statement, std::shared_ptr<CFGNode>> &map,
                                       const std::shared_ptr<StatementListNode> &statementListNode) {
    // Used to save head and tail nodes of this subgraph to be returned
    std::shared_ptr<CFGNode> head;
    std::shared_ptr<CFGNode> tail;  // also used as a pointer to the previous tail, see below

    // Intermediate nodes used for processing
    std::shared_ptr<CFGNode> childHead;
    std::shared_ptr<CFGNode> childTail;

    for (const auto& statementNode : statementListNode->getStatements()) {
        if (statementNode->getStatementType() == StatementNodeType::If) {
            std::tie(childHead, childTail) = buildIfSubgraph(map, std::static_pointer_cast<IfNode>(statementNode));
        } else if (statementNode->getStatementType() == StatementNodeType::While) {
            std::tie(childHead, childTail) = buildWhileSubgraph(map, std::static_pointer_cast<WhileNode>(statementNode));
        } else {
            std::tie(childHead, childTail) = buildStatementSubgraph(map, statementNode);
        }

        if (tail) {
            // if previous tail was a dummy tail, merge it with current childhead
            if (auto dummyTail = std::dynamic_pointer_cast<DummyCFGNode>(tail)) {
                for (const auto& parent : dummyTail->getParentNodes()) {
                    childHead->addParentNode(parent);
                    parent->addChildNode(childHead);
                    // delete dummyTail from parent
                    parent->removeChildNode(dummyTail);
                }
            } else { // else, attach previous tail with (current) child head
                tail->addChildNode(childHead);
                childHead->addParentNode(tail);
            }
        }

        // update head and tails
        if (head == nullptr) {
            head = childHead;
        }
        tail = childTail;
    }

    return {head, tail};
}

std::pair<std::shared_ptr<CFGNode>, std::shared_ptr<CFGNode>>
CFGBuilder::buildStatementSubgraph(std::unordered_map<Statement, std::shared_ptr<CFGNode>> &map,
                                               const std::shared_ptr<StatementNode> &statementNode) {
    StatementType statementType = StatementTypeFactory::getStatementTypeFrom(statementNode->getStatementType());
    Statement statement = Statement(statementNode->getStatementNumber(), statementType);
    auto cfgNode = std::make_shared<CFGNode>(statementNode->getStatementNumber(), statementType);
    map[statement] = cfgNode;
    return {cfgNode, cfgNode};
}

std::pair<std::shared_ptr<CFGNode>, std::shared_ptr<CFGNode>>
CFGBuilder::buildIfSubgraph(std::unordered_map<Statement, std::shared_ptr<CFGNode>> &map,
                            const std::shared_ptr<IfNode> &ifNode) {
    auto [cfgNode, _] = buildStatementSubgraph(map, ifNode);

    auto [thenHeadNode, thenTailNode] = buildStatementListSubgraph(map, ifNode->getThenStatementList());
    auto [elseHeadNode, elseTailNode] = buildStatementListSubgraph(map, ifNode->getElseStatementList());

    auto dummyTail = std::make_shared<DummyCFGNode>();

    // add if to then stmtlst edge
    cfgNode->addChildNode(thenHeadNode);
    thenHeadNode->addParentNode(cfgNode);

    // add if to else stmtlst edge
    cfgNode->addChildNode(elseHeadNode);
    elseHeadNode->addParentNode(cfgNode);

    // add end of then stmtlst to dummy tail edge
    thenTailNode->addChildNode(dummyTail);
    dummyTail->addParentNode(thenTailNode);

    // add end of else stmtlst to dummy tail edge
    elseTailNode->addChildNode(dummyTail);
    dummyTail->addParentNode(elseTailNode);

    return {cfgNode, dummyTail};
}

std::pair<std::shared_ptr<CFGNode>, std::shared_ptr<CFGNode>>
CFGBuilder::buildWhileSubgraph(std::unordered_map<Statement, std::shared_ptr<CFGNode>> &map,
                               const std::shared_ptr<WhileNode> &whileNode) {
    auto [cfgNode, _] = buildStatementSubgraph(map, whileNode);

    auto [headNode, tailNode] = buildStatementListSubgraph(map, whileNode->getStatementList());

    // add while to stmtlst edge
    cfgNode->addChildNode(headNode);
    headNode->addParentNode(cfgNode);

    // add end of stmtlst to while edge
    tailNode->addChildNode(cfgNode);
    cfgNode->addParentNode(tailNode);

    return {cfgNode, cfgNode};
}