#include <utility>
#include <stack>
#include <cassert>

#include "CFGExtractor.h"

CFGExtractor::CFGExtractor(std::shared_ptr<PkbWriter> pkbWriter) : pkbWriter(std::move(pkbWriter)) {}

void CFGExtractor::extractRelationships(const std::unordered_map<ProcedureName, Statement>& heads,
        const std::unordered_map<ProcedureName, std::unordered_map<Statement, std::shared_ptr<CFGNode>>>& cfgs) {
    saveCFGToPKB(heads, cfgs);
    for (const auto& [procName, cfg] : cfgs) {
        assert(heads.count(procName) == 1);
        const Statement& firstStatement = heads.at(procName);
        auto firstNode = cfg.at(firstStatement);
        extractNextRelationship(firstNode, cfg);
    }
}

void CFGExtractor::saveCFGToPKB(const std::unordered_map<ProcedureName, Statement>& heads,
        const std::unordered_map<ProcedureName, std::unordered_map<Statement, std::shared_ptr<CFGNode>>> &cfgs) {
    // TODO: Call pkbWriter to save CFG
}

void CFGExtractor::extractNextRelationship(const std::shared_ptr<CFGNode>& head,
        const std::unordered_map<Statement, std::shared_ptr<CFGNode>>& cfg) {
    std::vector<bool> isVisited(cfg.size(), false);
    std::unordered_map<StatementNumber, std::shared_ptr<Statement>> statements;

    // Create all shared_ptr<Statement> beforehand
    for (const auto& [statement, cfgNode] : cfg) {
        StatementNumber stmtNum = cfgNode->getStatementNumber();
        statements[stmtNum] = std::make_shared<Statement>(statement);
    }

    StatementNumber firstStatementNumber = head->getStatementNumber();

    // DFS for better space efficiency
    std::stack<std::shared_ptr<CFGNode>> frontier;
    frontier.push(head);
    while (!frontier.empty()) {
        auto& currentNode = frontier.top();
        frontier.pop();

        StatementNumber parentStatementNumber = currentNode->getStatementNumber();
        auto& parentStatement = statements[parentStatementNumber];
        for (const auto& child : currentNode->getChildrenNodes()) {
            StatementNumber childStatementNumber = child->getStatementNumber();
            auto& childStatement = statements[childStatementNumber];
             pkbWriter->addNextRelationship(parentStatement, childStatement);

            int childIndex = childStatementNumber - firstStatementNumber;
            assert(childIndex < isVisited.size());
            if (!isVisited[childIndex]) {
                frontier.push(child);
            }
        }
        int parentIndex = parentStatementNumber-firstStatementNumber;
        isVisited[parentIndex] = true;
    }
}