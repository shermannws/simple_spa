#include "CFGBuilder.h"
#include "Commons/CFG/DummyCFGNode.h"
#include "Commons/StatementFactory.h"
#include "SP/AST/Nodes/StatementNode.h"

std::unordered_map<ProcedureName, std::pair<std::shared_ptr<CFGNode>, std::vector<std::shared_ptr<CFGNode>>>>
CFGBuilder::buildAllCFG(const std::shared_ptr<ProgramNode> &astRootNode) {
    std::unordered_map<ProcedureName, std::pair<std::shared_ptr<CFGNode>, std::vector<std::shared_ptr<CFGNode>>>>
            cfgMap;
    for (auto &procedureNode: astRootNode->getProcedures()) {
        ProcedureName procedureName = procedureNode->getProcedureName();
        cfgMap[procedureName] = buildCFGForProcedure(procedureNode);
    }

    return cfgMap;
}

std::pair<std::shared_ptr<CFGNode>, std::vector<std::shared_ptr<CFGNode>>>
CFGBuilder::buildCFGForProcedure(const std::shared_ptr<ProcedureNode> &procedureNode) {
    std::vector<std::shared_ptr<CFGNode>> cfgNodes;
    auto [head, tail] = buildStatementListSubgraph(cfgNodes, procedureNode->getStatementList());

    // remove dummy tail if the last statement of the procedure is an if statement
    if (auto dummyTail = std::dynamic_pointer_cast<DummyCFGNode>(tail)) {
        for (const auto &parent: dummyTail->getParentNodes()) {
            // delete dummyTail from parent
            parent->removeChildNode(dummyTail);
        }
    }
    return std::make_pair(head, cfgNodes);
}

std::pair<std::shared_ptr<CFGNode>, std::shared_ptr<CFGNode>>
CFGBuilder::buildStatementListSubgraph(std::vector<std::shared_ptr<CFGNode>> &cfgNodes,
                                       const std::shared_ptr<StatementListNode> &statementListNode) {
    // Used to save head and tail nodes of this subgraph to be returned
    std::shared_ptr<CFGNode> head;
    std::shared_ptr<CFGNode> tail;// also used as a pointer to the previous tail, see below

    // Intermediate nodes used for processing
    std::shared_ptr<CFGNode> childHead;
    std::shared_ptr<CFGNode> childTail;

    for (const auto &statementNode: statementListNode->getStatements()) {
        if (statementNode->getStatementType() == StatementNodeType::If) {
            std::tie(childHead, childTail) = buildIfSubgraph(cfgNodes, std::static_pointer_cast<IfNode>(statementNode));
        } else if (statementNode->getStatementType() == StatementNodeType::While) {
            std::tie(childHead, childTail) =
                    buildWhileSubgraph(cfgNodes, std::static_pointer_cast<WhileNode>(statementNode));
        } else {
            std::tie(childHead, childTail) = buildStatementSubgraph(cfgNodes, statementNode);
        }

        if (tail) {
            // if previous tail was a dummy tail, merge it with current childhead
            if (auto dummyTail = std::dynamic_pointer_cast<DummyCFGNode>(tail)) {
                for (const auto &parent: dummyTail->getParentNodes()) {
                    childHead->addParentNode(parent);
                    parent->addChildNode(childHead);
                    // delete dummyTail from parent
                    parent->removeChildNode(dummyTail);
                }
            } else {// else, attach previous tail with (current) child head
                tail->addChildNode(childHead);
                childHead->addParentNode(tail);
            }
        }

        // update head and tails
        if (head == nullptr) { head = childHead; }
        tail = childTail;
    }

    return {head, tail};
}

std::pair<std::shared_ptr<CFGNode>, std::shared_ptr<CFGNode>>
CFGBuilder::buildStatementSubgraph(std::vector<std::shared_ptr<CFGNode>> &cfgNodes,
                                   const std::shared_ptr<StatementNode> &statementNode) {
    auto statement = StatementFactory::createStatementFromStatementNode(statementNode);
    auto cfgNode = std::make_shared<CFGNode>(statementNode->getStatementNumber(), statement->getStatementType(),
                                             statement->getAttrValue());
    cfgNodes.push_back(cfgNode);
    return {cfgNode, cfgNode};
}

std::pair<std::shared_ptr<CFGNode>, std::shared_ptr<CFGNode>>
CFGBuilder::buildIfSubgraph(std::vector<std::shared_ptr<CFGNode>> &cfgNodes, const std::shared_ptr<IfNode> &ifNode) {
    auto [cfgNode, _] = buildStatementSubgraph(cfgNodes, ifNode);

    auto [thenHeadNode, thenTailNode] = buildStatementListSubgraph(cfgNodes, ifNode->getThenStatementList());
    auto [elseHeadNode, elseTailNode] = buildStatementListSubgraph(cfgNodes, ifNode->getElseStatementList());

    auto dummyTail = std::make_shared<DummyCFGNode>();

    // connect if to then stmtlst
    cfgNode->addChildNode(thenHeadNode);
    thenHeadNode->addParentNode(cfgNode);

    // connect if to else stmtlst
    cfgNode->addChildNode(elseHeadNode);
    elseHeadNode->addParentNode(cfgNode);

    // connect end of then stmtlst to dummy tail
    if (auto dummyThenTail = std::dynamic_pointer_cast<DummyCFGNode>(thenTailNode)) {
        for (const auto &parent: dummyThenTail->getParentNodes()) {
            dummyTail->addParentNode(parent);
            parent->addChildNode(dummyTail);
            // delete dummyTail from parent
            parent->removeChildNode(dummyThenTail);
        }
    } else {
        thenTailNode->addChildNode(dummyTail);
        dummyTail->addParentNode(thenTailNode);
    }

    // connect end of else stmtlst to dummy tail
    if (auto dummyElseTail = std::dynamic_pointer_cast<DummyCFGNode>(elseTailNode)) {
        for (const auto &parent: dummyElseTail->getParentNodes()) {
            dummyTail->addParentNode(parent);
            parent->addChildNode(dummyTail);
            // delete dummyTail from parent
            parent->removeChildNode(dummyElseTail);
        }
    } else {
        elseTailNode->addChildNode(dummyTail);
        dummyTail->addParentNode(elseTailNode);
    }

    return {cfgNode, dummyTail};
}

std::pair<std::shared_ptr<CFGNode>, std::shared_ptr<CFGNode>>
CFGBuilder::buildWhileSubgraph(std::vector<std::shared_ptr<CFGNode>> &cfgNodes,
                               const std::shared_ptr<WhileNode> &whileNode) {
    auto [cfgNode, _] = buildStatementSubgraph(cfgNodes, whileNode);

    auto [headNode, tailNode] = buildStatementListSubgraph(cfgNodes, whileNode->getStatementList());

    // connect while to head of stmtlst
    cfgNode->addChildNode(headNode);
    headNode->addParentNode(cfgNode);

    // connect end of stmtlst to while
    if (auto dummyTail = std::dynamic_pointer_cast<DummyCFGNode>(tailNode)) {
        for (const auto &parent: dummyTail->getParentNodes()) {
            cfgNode->addParentNode(parent);
            parent->addChildNode(cfgNode);
            // delete dummyTail from parent
            parent->removeChildNode(dummyTail);
        }
    } else {
        tailNode->addChildNode(cfgNode);
        cfgNode->addParentNode(tailNode);
    }

    return {cfgNode, cfgNode};
}
