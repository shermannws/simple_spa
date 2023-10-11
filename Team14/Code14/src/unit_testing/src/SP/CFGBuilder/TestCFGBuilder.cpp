#include <memory>
#include <unordered_map>
#include <unordered_set>

#include "catch.hpp"
#include "Commons/Entities/StatementType.h"
#include "SP/CFG/CFGBuilder.h"
#include "SP/SPTokenizer.h"
#include "SP/SPParser.h"

TEST_CASE("Test single procedure") {
    std::string sourceProgram =
            "procedure Proc1 {"
                "x = 1 + 2 * y - (1 / var) % 5;"    // stmt 1
                "read x;"                           // stmt 2
                "print y;"                          // stmt 3
                "if (x > 1) then {"                 // stmt 4
                    "z = y;"                        // stmt 5
                "} else {"
                    "var1 = 5;"                     // stmt 6
                "} "
                "while (1 != 3) {"                  // stmt 7
                    "print c;"                      // stmt 8
                "}"
            "}";
    SPTokenizer tokenizer = SPTokenizer(sourceProgram);
    auto tokens = tokenizer.tokenize();
    SPParser parser;
    auto rootNode = parser.parse(tokens);

    CFGBuilder builder;
    std::unordered_map<ProcedureName, std::unordered_map<Statement, std::shared_ptr<CFGNode>>>
            cfgs = builder.buildAllCFG(rootNode);
    REQUIRE(cfgs.size() == 1);
    REQUIRE(cfgs.count("Proc1") == 1);

    std::unordered_map<Statement, std::shared_ptr<CFGNode>> proc1CFG = cfgs["Proc1"];
    REQUIRE(proc1CFG.size() == 8);

    // map stmtnum to stmttype
    std::vector<std::pair<StatementNumber, StatementType>> numToTypeVector = {
            { 1, StatementType::Assign },
            { 2, StatementType::Read },
            { 3, StatementType::Print },
            { 4, StatementType::If },
            { 5, StatementType::Assign },
            { 6, StatementType::Assign },
            { 7, StatementType::While },
            { 8, StatementType::Print },
    };

    for (auto [stmtNum, stmtType] : numToTypeVector) {
        auto stmt = Statement(stmtNum, stmtType);
        REQUIRE(proc1CFG.count(stmt) == 1);
    }
    auto node1 = proc1CFG[Statement(1, StatementType::Assign)];
    auto node2 = proc1CFG[Statement(2, StatementType::Read)];
    auto node3 = proc1CFG[Statement(3, StatementType::Print)];
    auto node4 = proc1CFG[Statement(4, StatementType::If)];
    auto node5 = proc1CFG[Statement(5, StatementType::Assign)];
    auto node6 = proc1CFG[Statement(6, StatementType::Assign)];
    auto node7 = proc1CFG[Statement(7, StatementType::While)];
    auto node8 = proc1CFG[Statement(8, StatementType::Print)];

    // Statement 1
    REQUIRE(node1->getStatementType() == StatementType::Assign);
    REQUIRE(node1->getStatementNumber() == 1);
    REQUIRE(node1->getParentNodes().empty());
    REQUIRE(node1->getChildrenNodes().size() == 1);
    REQUIRE(node1->getChildrenNodes().front()->getStatementNumber() == 2);

    // Statement 2
    REQUIRE(node2->getStatementType() == StatementType::Read);
    REQUIRE(node2->getStatementNumber() == 2);
    REQUIRE(node2->getParentNodes().size() == 1);
    REQUIRE(node2->getParentNodes().front()->getStatementNumber() == 1);
    REQUIRE(node2->getChildrenNodes().size() == 1);
    REQUIRE(node2->getChildrenNodes().front()->getStatementNumber() == 3);

    // Statement 3
    REQUIRE(node3->getStatementType() == StatementType::Print);
    REQUIRE(node3->getStatementNumber() == 3);
    REQUIRE(node3->getParentNodes().size() == 1);
    REQUIRE(node3->getParentNodes().front()->getStatementNumber() == 2);
    REQUIRE(node3->getChildrenNodes().size() == 1);
    REQUIRE(node3->getChildrenNodes().front()->getStatementNumber() == 4);

    // Statement 4
    REQUIRE(node4->getStatementType() == StatementType::If);
    REQUIRE(node4->getStatementNumber() == 4);
    REQUIRE(node4->getParentNodes().size() == 1);
    REQUIRE(node4->getParentNodes().front()->getStatementNumber() == 3);
    REQUIRE(node4->getChildrenNodes().size() == 2);
    REQUIRE(node4->getChildrenNodes().front()->getStatementNumber() == 5);
    REQUIRE(node4->getChildrenNodes().back()->getStatementNumber() == 6);

    // Statement 5
    REQUIRE(node5->getStatementType() == StatementType::Assign);
    REQUIRE(node5->getStatementNumber() == 5);
    REQUIRE(node5->getParentNodes().size() == 1);
    REQUIRE(node5->getParentNodes().front()->getStatementNumber() == 4);
    REQUIRE(node5->getChildrenNodes().size() == 1);
    REQUIRE(node5->getChildrenNodes().front()->getStatementNumber() == 7);

    // Statement 6
    REQUIRE(node6->getStatementType() == StatementType::Assign);
    REQUIRE(node6->getStatementNumber() == 6);
    REQUIRE(node6->getParentNodes().size() == 1);
    REQUIRE(node6->getParentNodes().front()->getStatementNumber() == 4);
    REQUIRE(node6->getChildrenNodes().size() == 1);
    REQUIRE(node6->getChildrenNodes().front()->getStatementNumber() == 7);

    // Statement 7
    REQUIRE(node7->getStatementType() == StatementType::While);
    REQUIRE(node7->getStatementNumber() == 7);
    REQUIRE(node7->getParentNodes().size() == 3);
    auto parents = node7->getParentNodes();
    std::vector<StatementNumber> parentStmtNums(3); // size 3
    std::transform(parents.begin(),
                   parents.end(),
                   parentStmtNums.begin(),
                   [](const std::shared_ptr<CFGNode>& node) { return node->getStatementNumber(); });
    std::sort(parentStmtNums.begin(), parentStmtNums.end());
    std::vector<StatementNumber> correctParentStmtNums =  { 5, 6, 8 };
    REQUIRE(parentStmtNums == correctParentStmtNums);
    REQUIRE(node7->getChildrenNodes().size() == 1);
    REQUIRE(node7->getChildrenNodes().front()->getStatementNumber() == 8);

    // Statement 8
    REQUIRE(node8->getStatementType() == StatementType::Print);
    REQUIRE(node8->getStatementNumber() == 8);
    REQUIRE(node8->getParentNodes().size() == 1);
    REQUIRE(node8->getParentNodes().front()->getStatementNumber() == 7);
    REQUIRE(node8->getChildrenNodes().size() == 1);
    REQUIRE(node8->getChildrenNodes().front()->getStatementNumber() == 7);
}

TEST_CASE("Test multiple procedures") {

}

TEST_CASE("Test nested ifs") {

}

TEST_CASE("Test nested whiles") {

}