#include <cassert>
#include <stack>
#include <utility>

#include "CFGExtractor.h"
#include "Commons/EntityFactory.h"

CFGExtractor::CFGExtractor(std::shared_ptr<PkbWriter> pkbWriter) : pkbWriter(std::move(pkbWriter)) {}

void CFGExtractor::extractRelationships(
        const std::unordered_map<ProcedureName,
                                 std::pair<std::shared_ptr<CFGNode>, std::vector<std::shared_ptr<CFGNode>>>> &cfgMap) {
    saveCFGToPKB(cfgMap);

    for (const auto &[procName, cfgHeadAndNodes]: cfgMap) {
        auto &[cfgHead, cfgNodes] = cfgHeadAndNodes;
        extractNextRelationship(cfgHead, cfgNodes);
    }
}

void CFGExtractor::saveCFGToPKB(
        const std::unordered_map<ProcedureName,
                                 std::pair<std::shared_ptr<CFGNode>, std::vector<std::shared_ptr<CFGNode>>>> &cfgMap) {
    std::unordered_map<ProcedureName, std::shared_ptr<CFGNode>> procedureToCFGHeadMap;
    for (const auto &[procName, cfgHeadAndNodes]: cfgMap) {
        auto &[cfgHead, cfgNodes] = cfgHeadAndNodes;
        procedureToCFGHeadMap[procName] = cfgHead;
    }
    pkbWriter->setCFGMap(procedureToCFGHeadMap);
}

void CFGExtractor::extractNextRelationship(const std::shared_ptr<CFGNode> &head,
                                           const std::vector<std::shared_ptr<CFGNode>> &cfgNodes) {
    std::unordered_set<StatementNumber> isVisited;
    std::unordered_map<StatementNumber, std::shared_ptr<Statement>> statements;

    // Create all shared_ptr<Statement> beforehand
    for (const auto &cfgNode: cfgNodes) {
        StatementNumber stmtNum = cfgNode->getStatementNumber();
        StatementType stmtType = cfgNode->getStatementType();
        AttrValue attrValue = cfgNode->getAttrValue();
        statements[stmtNum] = EntityFactory::createStatement(stmtNum, stmtType, attrValue);
    }

    // DFS for better space efficiency
    std::stack<std::shared_ptr<CFGNode>> frontier;
    frontier.push(head);
    while (!frontier.empty()) {
        auto &currentNode = frontier.top();
        frontier.pop();

        StatementNumber parentStatementNumber = currentNode->getStatementNumber();
        auto &parentStatement = statements[parentStatementNumber];
        for (const auto &child: currentNode->getChildrenNodes()) {
            StatementNumber childStatementNumber = child->getStatementNumber();
            auto &childStatement = statements[childStatementNumber];
            pkbWriter->addNextRelationship(parentStatement, childStatement);

            if (isVisited.find(childStatementNumber) == isVisited.end()) { frontier.push(child); }
        }
        isVisited.insert(parentStatementNumber);
    }
}