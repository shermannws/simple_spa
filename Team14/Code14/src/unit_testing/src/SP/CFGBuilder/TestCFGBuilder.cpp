#include <memory>
#include <unordered_map>

#include "Commons/Entities/StatementType.h"
#include "SP/CFG/CFGBuilder.h"
#include "SP/SPParser.h"
#include "SP/SPTokenizer.h"
#include "catch.hpp"

/**
 * Helper function to compare vector of CFGNodes with a vector of StatementNumbers
 * @param parents Vector of CFGNodes
 * @param correctParentStmtNums Vector of StatementNumbers
 * @return
 */
bool isSameStatements(const std::vector<std::shared_ptr<CFGNode>> &parents,
                      std::vector<StatementNumber> correctParentStmtNums) {
    if (parents.size() != correctParentStmtNums.size()) { return false; }
    std::vector<StatementNumber> parentStmtNums((int) parents.size());
    std::transform(parents.begin(), parents.end(), parentStmtNums.begin(),
                   [&](const std::shared_ptr<CFGNode> &node) { return node->getStatementNumber(); });
    std::sort(parentStmtNums.begin(), parentStmtNums.end());
    std::sort(correctParentStmtNums.begin(), correctParentStmtNums.end());
    return parentStmtNums == correctParentStmtNums;
}

TEST_CASE("Test single procedure") {
    std::string sourceProgram = "procedure Proc1 {"
                                "x = 1 + 2 * y - (1 / var) % 5;"// stmt 1
                                "read x;"                       // stmt 2
                                "print y;"                      // stmt 3
                                "if (x > 1) then {"             // stmt 4
                                "z = y;"                        // stmt 5
                                "} else {"
                                "var1 = 5;"// stmt 6
                                "} "
                                "while (1 != 3) {"// stmt 7
                                "print c;"        // stmt 8
                                "}"
                                "}";
    SPTokenizer tokenizer = SPTokenizer(sourceProgram);
    auto tokens = tokenizer.tokenize();
    SPParser parser;
    auto rootNode = parser.parse(tokens);

    std::unordered_map<ProcedureName, std::unordered_map<Statement, std::shared_ptr<CFGNode>>> cfgs =
            CFGBuilder::buildAllCFG(rootNode);
    REQUIRE(cfgs.size() == 1);
    REQUIRE(cfgs.count("Proc1") == 1);

    std::unordered_map<Statement, std::shared_ptr<CFGNode>> proc1CFG = cfgs["Proc1"];
    REQUIRE(proc1CFG.size() == 8);

    // map stmtnum to stmttype
    std::vector<std::pair<StatementNumber, StatementType>> numToTypeVector = {
            {1, StatementType::Assign}, {2, StatementType::Read},   {3, StatementType::Print},
            {4, StatementType::If},     {5, StatementType::Assign}, {6, StatementType::Assign},
            {7, StatementType::While},  {8, StatementType::Print},
    };

    for (auto [stmtNum, stmtType]: numToTypeVector) {
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
    REQUIRE(isSameStatements(node1->getChildrenNodes(), {2}));

    // Statement 2
    REQUIRE(node2->getStatementType() == StatementType::Read);
    REQUIRE(node2->getStatementNumber() == 2);
    REQUIRE(node2->getParentNodes().size() == 1);
    REQUIRE(isSameStatements(node2->getParentNodes(), {1}));
    REQUIRE(node2->getChildrenNodes().size() == 1);
    REQUIRE(isSameStatements(node2->getChildrenNodes(), {3}));

    // Statement 3
    REQUIRE(node3->getStatementType() == StatementType::Print);
    REQUIRE(node3->getStatementNumber() == 3);
    REQUIRE(node3->getParentNodes().size() == 1);
    REQUIRE(isSameStatements(node3->getParentNodes(), {2}));
    REQUIRE(node3->getChildrenNodes().size() == 1);
    REQUIRE(isSameStatements(node3->getChildrenNodes(), {4}));

    // Statement 4
    REQUIRE(node4->getStatementType() == StatementType::If);
    REQUIRE(node4->getStatementNumber() == 4);
    REQUIRE(node4->getParentNodes().size() == 1);
    REQUIRE(isSameStatements(node4->getParentNodes(), {3}));
    REQUIRE(node4->getChildrenNodes().size() == 2);
    REQUIRE(isSameStatements(node4->getChildrenNodes(), {5, 6}));


    // Statement 5
    REQUIRE(node5->getStatementType() == StatementType::Assign);
    REQUIRE(node5->getStatementNumber() == 5);
    REQUIRE(node5->getParentNodes().size() == 1);
    REQUIRE(isSameStatements(node5->getParentNodes(), {4}));
    REQUIRE(node5->getChildrenNodes().size() == 1);
    REQUIRE(isSameStatements(node5->getChildrenNodes(), {7}));

    // Statement 6
    REQUIRE(node6->getStatementType() == StatementType::Assign);
    REQUIRE(node6->getStatementNumber() == 6);
    REQUIRE(node6->getParentNodes().size() == 1);
    REQUIRE(isSameStatements(node6->getParentNodes(), {4}));
    REQUIRE(node6->getChildrenNodes().size() == 1);
    REQUIRE(isSameStatements(node6->getChildrenNodes(), {7}));

    // Statement 7
    REQUIRE(node7->getStatementType() == StatementType::While);
    REQUIRE(node7->getStatementNumber() == 7);
    REQUIRE(node7->getParentNodes().size() == 3);
    REQUIRE(isSameStatements(node7->getParentNodes(), {5, 6, 8}));
    REQUIRE(node7->getChildrenNodes().size() == 1);
    REQUIRE(isSameStatements(node7->getChildrenNodes(), {8}));

    // Statement 8
    REQUIRE(node8->getStatementType() == StatementType::Print);
    REQUIRE(node8->getStatementNumber() == 8);
    REQUIRE(node8->getParentNodes().size() == 1);
    REQUIRE(isSameStatements(node8->getParentNodes(), {7}));
    REQUIRE(node8->getChildrenNodes().size() == 1);
    REQUIRE(isSameStatements(node8->getChildrenNodes(), {7}));
    // parent and child should be the same
    REQUIRE(node8->getParentNodes().front() == node8->getChildrenNodes().front());
}

TEST_CASE("Test multiple procedures") {
    std::string sourceProgram = "procedure Proc1 { x = 1; }"
                                "procedure Proc2 { read x; }"
                                "procedure Proc3 { print y; }"
                                "procedure Proc4 { call Proc1; }"
                                "procedure Proc5 { if (z > 1) then { print p; } else { read r; } }"
                                "procedure Proc6 { while (z <= w) { x = 2; } }";
    SPTokenizer tokenizer = SPTokenizer(sourceProgram);
    auto tokens = tokenizer.tokenize();
    SPParser parser;
    auto rootNode = parser.parse(tokens);

    std::unordered_map<ProcedureName, std::unordered_map<Statement, std::shared_ptr<CFGNode>>> cfgs =
            CFGBuilder::buildAllCFG(rootNode);
    REQUIRE(cfgs.size() == 6);

    SECTION("Test Proc1") {
        REQUIRE(cfgs.count("Proc1") == 1);
        std::unordered_map<Statement, std::shared_ptr<CFGNode>> proc1CFG = cfgs["Proc1"];
        REQUIRE(proc1CFG.size() == 1);

        auto stmt = Statement(1, StatementType::Assign);
        REQUIRE(proc1CFG.count(stmt) == 1);
        auto node1 = proc1CFG[stmt];

        REQUIRE(node1->getStatementType() == StatementType::Assign);
        REQUIRE(node1->getStatementNumber() == 1);
        REQUIRE(node1->getParentNodes().empty());
        REQUIRE(node1->getChildrenNodes().empty());
    }

    SECTION("Test Proc2") {
        REQUIRE(cfgs.count("Proc2") == 1);
        std::unordered_map<Statement, std::shared_ptr<CFGNode>> proc2CFG = cfgs["Proc2"];
        REQUIRE(proc2CFG.size() == 1);

        auto stmt = Statement(2, StatementType::Read);
        REQUIRE(proc2CFG.count(stmt) == 1);
        auto node2 = proc2CFG[stmt];

        REQUIRE(node2->getStatementType() == StatementType::Read);
        REQUIRE(node2->getStatementNumber() == 2);
        REQUIRE(node2->getParentNodes().empty());
        REQUIRE(node2->getChildrenNodes().empty());
    }

    SECTION("Test Proc3") {
        REQUIRE(cfgs.count("Proc3") == 1);
        std::unordered_map<Statement, std::shared_ptr<CFGNode>> proc3CFG = cfgs["Proc3"];
        REQUIRE(proc3CFG.size() == 1);

        auto stmt = Statement(3, StatementType::Print);
        REQUIRE(proc3CFG.count(stmt) == 1);
        auto node3 = proc3CFG[stmt];

        REQUIRE(node3->getStatementType() == StatementType::Print);
        REQUIRE(node3->getStatementNumber() == 3);
        REQUIRE(node3->getParentNodes().empty());
        REQUIRE(node3->getChildrenNodes().empty());
    }

    SECTION("Test Proc4") {
        REQUIRE(cfgs.count("Proc4") == 1);
        std::unordered_map<Statement, std::shared_ptr<CFGNode>> proc4CFG = cfgs["Proc4"];
        REQUIRE(proc4CFG.size() == 1);

        auto stmt = Statement(4, StatementType::Call);
        REQUIRE(proc4CFG.count(stmt) == 1);
        auto node4 = proc4CFG[stmt];

        REQUIRE(node4->getStatementType() == StatementType::Call);
        REQUIRE(node4->getStatementNumber() == 4);
        REQUIRE(node4->getParentNodes().empty());
        REQUIRE(node4->getChildrenNodes().empty());
    }

    SECTION("Test Proc5") {
        REQUIRE(cfgs.count("Proc5") == 1);
        std::unordered_map<Statement, std::shared_ptr<CFGNode>> proc5CFG = cfgs["Proc5"];
        REQUIRE(proc5CFG.size() == 3);

        auto stmtIf = Statement(5, StatementType::If);
        auto stmtThen = Statement(6, StatementType::Print);
        auto stmtElse = Statement(7, StatementType::Read);
        REQUIRE(proc5CFG.count(stmtIf) == 1);
        REQUIRE(proc5CFG.count(stmtThen) == 1);
        REQUIRE(proc5CFG.count(stmtElse) == 1);
        auto node5 = proc5CFG[stmtIf];
        auto node6 = proc5CFG[stmtThen];
        auto node7 = proc5CFG[stmtElse];

        REQUIRE(node5->getStatementType() == StatementType::If);
        REQUIRE(node5->getStatementNumber() == 5);
        REQUIRE(node5->getParentNodes().empty());
        REQUIRE(node5->getChildrenNodes().size() == 2);
        REQUIRE(isSameStatements(node5->getChildrenNodes(), {6, 7}));


        REQUIRE(node6->getStatementType() == StatementType::Print);
        REQUIRE(node6->getStatementNumber() == 6);
        REQUIRE(node6->getParentNodes().size() == 1);
        REQUIRE(isSameStatements(node6->getParentNodes(), {5}));
        REQUIRE(node6->getChildrenNodes().empty());

        REQUIRE(node7->getStatementType() == StatementType::Read);
        REQUIRE(node7->getStatementNumber() == 7);
        REQUIRE(node7->getParentNodes().size() == 1);
        REQUIRE(isSameStatements(node7->getParentNodes(), {5}));
        REQUIRE(node7->getChildrenNodes().empty());
    }

    SECTION("Test Proc6") {
        REQUIRE(cfgs.count("Proc6") == 1);
        std::unordered_map<Statement, std::shared_ptr<CFGNode>> proc6CFG = cfgs["Proc6"];
        REQUIRE(proc6CFG.size() == 2);

        auto stmtWhile = Statement(8, StatementType::While);
        auto stmtAssign = Statement(9, StatementType::Assign);
        REQUIRE(proc6CFG.count(stmtWhile) == 1);
        REQUIRE(proc6CFG.count(stmtAssign) == 1);
        auto node8 = proc6CFG[stmtWhile];
        auto node9 = proc6CFG[stmtAssign];

        REQUIRE(node8->getStatementType() == StatementType::While);
        REQUIRE(node8->getStatementNumber() == 8);
        REQUIRE(node8->getParentNodes().size() == 1);
        REQUIRE(isSameStatements(node8->getParentNodes(), {9}));
        REQUIRE(node8->getChildrenNodes().size() == 1);
        REQUIRE(isSameStatements(node8->getChildrenNodes(), {9}));
        // child and parent should be the same
        REQUIRE(node8->getChildrenNodes().front() == node8->getParentNodes().front());

        REQUIRE(node9->getStatementType() == StatementType::Assign);
        REQUIRE(node9->getStatementNumber() == 9);
        REQUIRE(node9->getParentNodes().size() == 1);
        REQUIRE(isSameStatements(node9->getParentNodes(), {8}));
        REQUIRE(node9->getChildrenNodes().size() == 1);
        REQUIRE(isSameStatements(node9->getChildrenNodes(), {8}));
        // child and parent should be the same
        REQUIRE(node9->getChildrenNodes().front() == node9->getParentNodes().front());
    }
}

TEST_CASE("Test nested ifs - with one leaf/tail node") {
    // 12 stmts
    std::string sourceProgram = "procedure Proc1 { "
                                "   if (z > 1) then { "    // 1
                                "       if (z > 1) then { "// 2
                                "           print p; "     // 3
                                "       } else { "
                                "           if (z > 1) then { "// 4
                                "               print p; "     // 5
                                "           } else { "
                                "               if (z > 1) then { "// 6
                                "                   print p; "     // 7
                                "               } else { "
                                "                   read r; "// 8
                                "               } "
                                "           }"
                                "       }"
                                "   } else { "
                                "       if (z > 1) then { "// 9
                                "           print p; "     // 10
                                "       } else { "
                                "           read r; "// 11
                                "       }"
                                "   } "
                                "   x = 1;"// 12
                                "}";
    SPTokenizer tokenizer = SPTokenizer(sourceProgram);
    auto tokens = tokenizer.tokenize();
    SPParser parser;
    auto rootNode = parser.parse(tokens);

    std::unordered_map<ProcedureName, std::unordered_map<Statement, std::shared_ptr<CFGNode>>> cfgs =
            CFGBuilder::buildAllCFG(rootNode);
    REQUIRE(cfgs.size() == 1);

    REQUIRE(cfgs.count("Proc1") == 1);
    std::unordered_map<Statement, std::shared_ptr<CFGNode>> proc1CFG = cfgs["Proc1"];
    REQUIRE(proc1CFG.size() == 12);

    // stmt 1
    auto stmt1 = Statement(1, StatementType::If);
    REQUIRE(proc1CFG.count(stmt1) == 1);
    auto node1 = proc1CFG[stmt1];
    REQUIRE(node1->getStatementType() == StatementType::If);
    REQUIRE(node1->getStatementNumber() == 1);
    REQUIRE(node1->getParentNodes().empty());
    REQUIRE(node1->getChildrenNodes().size() == 2);
    REQUIRE(isSameStatements(node1->getChildrenNodes(), {2, 9}));


    // stmt 2
    auto stmt2 = Statement(2, StatementType::If);
    REQUIRE(proc1CFG.count(stmt2) == 1);
    auto node2 = proc1CFG[stmt2];
    REQUIRE(node2->getStatementType() == StatementType::If);
    REQUIRE(node2->getStatementNumber() == 2);
    REQUIRE(node2->getParentNodes().size() == 1);
    REQUIRE(isSameStatements(node2->getParentNodes(), {1}));
    REQUIRE(node2->getChildrenNodes().size() == 2);
    REQUIRE(isSameStatements(node2->getChildrenNodes(), {3, 4}));


    // stmt 3
    auto stmt3 = Statement(3, StatementType::Print);
    REQUIRE(proc1CFG.count(stmt3) == 1);
    auto node3 = proc1CFG[stmt3];
    REQUIRE(node3->getStatementType() == StatementType::Print);
    REQUIRE(node3->getStatementNumber() == 3);
    REQUIRE(node3->getParentNodes().size() == 1);
    REQUIRE(isSameStatements(node3->getParentNodes(), {2}));
    REQUIRE(node3->getChildrenNodes().size() == 1);
    REQUIRE(isSameStatements(node3->getChildrenNodes(), {12}));

    // stmt 4
    auto stmt4 = Statement(4, StatementType::If);
    REQUIRE(proc1CFG.count(stmt4) == 1);
    auto node4 = proc1CFG[stmt4];
    REQUIRE(node4->getStatementType() == StatementType::If);
    REQUIRE(node4->getStatementNumber() == 4);
    REQUIRE(node4->getParentNodes().size() == 1);
    REQUIRE(isSameStatements(node4->getParentNodes(), {2}));
    REQUIRE(node4->getChildrenNodes().size() == 2);
    REQUIRE(isSameStatements(node4->getChildrenNodes(), {5, 6}));


    // stmt 5
    auto stmt5 = Statement(5, StatementType::Print);
    REQUIRE(proc1CFG.count(stmt5) == 1);
    auto node5 = proc1CFG[stmt5];
    REQUIRE(node5->getStatementType() == StatementType::Print);
    REQUIRE(node5->getStatementNumber() == 5);
    REQUIRE(node5->getParentNodes().size() == 1);
    REQUIRE(isSameStatements(node5->getParentNodes(), {4}));
    REQUIRE(node5->getChildrenNodes().size() == 1);
    REQUIRE(isSameStatements(node5->getChildrenNodes(), {12}));

    // stmt 6
    auto stmt6 = Statement(6, StatementType::If);
    REQUIRE(proc1CFG.count(stmt6) == 1);
    auto node6 = proc1CFG[stmt6];
    REQUIRE(node6->getStatementType() == StatementType::If);
    REQUIRE(node6->getStatementNumber() == 6);
    REQUIRE(node6->getParentNodes().size() == 1);
    REQUIRE(isSameStatements(node6->getParentNodes(), {4}));
    REQUIRE(node6->getChildrenNodes().size() == 2);
    REQUIRE(isSameStatements(node6->getChildrenNodes(), {7, 8}));


    // stmt 7
    auto stmt7 = Statement(7, StatementType::Print);
    REQUIRE(proc1CFG.count(stmt7) == 1);
    auto node7 = proc1CFG[stmt7];
    REQUIRE(node7->getStatementType() == StatementType::Print);
    REQUIRE(node7->getStatementNumber() == 7);
    REQUIRE(node7->getParentNodes().size() == 1);
    REQUIRE(isSameStatements(node7->getParentNodes(), {6}));
    REQUIRE(node7->getChildrenNodes().size() == 1);
    REQUIRE(isSameStatements(node7->getChildrenNodes(), {12}));

    // stmt 8
    auto stmt8 = Statement(8, StatementType::Read);
    REQUIRE(proc1CFG.count(stmt8) == 1);
    auto node8 = proc1CFG[stmt8];
    REQUIRE(node8->getStatementType() == StatementType::Read);
    REQUIRE(node8->getStatementNumber() == 8);
    REQUIRE(node8->getParentNodes().size() == 1);
    REQUIRE(isSameStatements(node8->getParentNodes(), {6}));
    REQUIRE(node8->getChildrenNodes().size() == 1);
    REQUIRE(isSameStatements(node8->getChildrenNodes(), {12}));

    // stmt 9
    auto stmt9 = Statement(9, StatementType::If);
    REQUIRE(proc1CFG.count(stmt9) == 1);
    auto node9 = proc1CFG[stmt9];
    REQUIRE(node9->getStatementType() == StatementType::If);
    REQUIRE(node9->getStatementNumber() == 9);
    REQUIRE(node9->getParentNodes().size() == 1);
    REQUIRE(isSameStatements(node9->getParentNodes(), {1}));
    REQUIRE(node9->getChildrenNodes().size() == 2);
    REQUIRE(isSameStatements(node9->getChildrenNodes(), {10, 11}));


    // stmt 10
    auto stmt10 = Statement(10, StatementType::Print);
    REQUIRE(proc1CFG.count(stmt10) == 1);
    auto node10 = proc1CFG[stmt10];
    REQUIRE(node10->getStatementType() == StatementType::Print);
    REQUIRE(node10->getStatementNumber() == 10);
    REQUIRE(node10->getParentNodes().size() == 1);
    REQUIRE(isSameStatements(node10->getParentNodes(), {9}));
    REQUIRE(node10->getChildrenNodes().size() == 1);
    REQUIRE(isSameStatements(node10->getChildrenNodes(), {12}));

    // stmt 11
    auto stmt11 = Statement(11, StatementType::Read);
    REQUIRE(proc1CFG.count(stmt11) == 1);
    auto node11 = proc1CFG[stmt11];
    REQUIRE(node11->getStatementType() == StatementType::Read);
    REQUIRE(node11->getStatementNumber() == 11);
    REQUIRE(node11->getParentNodes().size() == 1);
    REQUIRE(isSameStatements(node11->getParentNodes(), {9}));
    REQUIRE(node11->getChildrenNodes().size() == 1);
    REQUIRE(isSameStatements(node11->getChildrenNodes(), {12}));

    // stmt 12
    auto stmt12 = Statement(12, StatementType::Assign);
    REQUIRE(proc1CFG.count(stmt12) == 1);
    auto node12 = proc1CFG[stmt12];
    REQUIRE(node12->getStatementType() == StatementType::Assign);
    REQUIRE(node12->getStatementNumber() == 12);
    REQUIRE(node12->getParentNodes().size() == 6);
    REQUIRE(isSameStatements(node12->getParentNodes(), {3, 5, 7, 8, 10, 11}));
    REQUIRE(node12->getChildrenNodes().empty());
}

TEST_CASE("Test nested ifs - with multiple leaf/tail nodes") {
    // Repeat of previous test case but without the last assign statement,
    // so there is no common last statement in the CFG.
    // The last statement depends on which branches are taken.
    // This test case only tests the leaf CFG nodes that previously pointed to the common last statement
    // but that now have no children
    // 11 stmts
    std::string sourceProgram = "procedure Proc1 { "
                                "   if (z > 1) then { "    // 1
                                "       if (z > 1) then { "// 2
                                "           print p; "     // 3
                                "       } else { "
                                "           if (z > 1) then { "// 4
                                "               print p; "     // 5
                                "           } else { "
                                "               if (z > 1) then { "// 6
                                "                   print p; "     // 7
                                "               } else { "
                                "                   read r; "// 8
                                "               } "
                                "           }"
                                "       }"
                                "   } else { "
                                "       if (z > 1) then { "// 9
                                "           print p; "     // 10
                                "       } else { "
                                "           read r; "// 11
                                "       }"
                                "   } "
                                "}";
    SPTokenizer tokenizer = SPTokenizer(sourceProgram);
    auto tokens = tokenizer.tokenize();
    SPParser parser;
    auto rootNode = parser.parse(tokens);

    std::unordered_map<ProcedureName, std::unordered_map<Statement, std::shared_ptr<CFGNode>>> cfgs =
            CFGBuilder::buildAllCFG(rootNode);
    REQUIRE(cfgs.size() == 1);

    REQUIRE(cfgs.count("Proc1") == 1);
    std::unordered_map<Statement, std::shared_ptr<CFGNode>> proc1CFG = cfgs["Proc1"];
    REQUIRE(proc1CFG.size() == 11);

    // stmt 3
    auto stmt3 = Statement(3, StatementType::Print);
    REQUIRE(proc1CFG.count(stmt3) == 1);
    auto node3 = proc1CFG[stmt3];
    REQUIRE(node3->getStatementType() == StatementType::Print);
    REQUIRE(node3->getStatementNumber() == 3);
    REQUIRE(node3->getParentNodes().size() == 1);
    REQUIRE(isSameStatements(node3->getParentNodes(), {2}));
    REQUIRE(node3->getChildrenNodes().empty());

    // stmt 5
    auto stmt5 = Statement(5, StatementType::Print);
    REQUIRE(proc1CFG.count(stmt5) == 1);
    auto node5 = proc1CFG[stmt5];
    REQUIRE(node5->getStatementType() == StatementType::Print);
    REQUIRE(node5->getStatementNumber() == 5);
    REQUIRE(node5->getParentNodes().size() == 1);
    REQUIRE(isSameStatements(node5->getParentNodes(), {4}));
    REQUIRE(node5->getChildrenNodes().empty());

    // stmt 7
    auto stmt7 = Statement(7, StatementType::Print);
    REQUIRE(proc1CFG.count(stmt7) == 1);
    auto node7 = proc1CFG[stmt7];
    REQUIRE(node7->getStatementType() == StatementType::Print);
    REQUIRE(node7->getStatementNumber() == 7);
    REQUIRE(node7->getParentNodes().size() == 1);
    REQUIRE(isSameStatements(node7->getParentNodes(), {6}));
    REQUIRE(node7->getChildrenNodes().empty());

    // stmt 8
    auto stmt8 = Statement(8, StatementType::Read);
    REQUIRE(proc1CFG.count(stmt8) == 1);
    auto node8 = proc1CFG[stmt8];
    REQUIRE(node8->getStatementType() == StatementType::Read);
    REQUIRE(node8->getStatementNumber() == 8);
    REQUIRE(node8->getParentNodes().size() == 1);
    REQUIRE(isSameStatements(node8->getParentNodes(), {6}));
    REQUIRE(node8->getChildrenNodes().empty());

    // stmt 10
    auto stmt10 = Statement(10, StatementType::Print);
    REQUIRE(proc1CFG.count(stmt10) == 1);
    auto node10 = proc1CFG[stmt10];
    REQUIRE(node10->getStatementType() == StatementType::Print);
    REQUIRE(node10->getStatementNumber() == 10);
    REQUIRE(node10->getParentNodes().size() == 1);
    REQUIRE(isSameStatements(node10->getParentNodes(), {9}));
    REQUIRE(node10->getChildrenNodes().empty());

    // stmt 11
    auto stmt11 = Statement(11, StatementType::Read);
    REQUIRE(proc1CFG.count(stmt11) == 1);
    auto node11 = proc1CFG[stmt11];
    REQUIRE(node11->getStatementType() == StatementType::Read);
    REQUIRE(node11->getStatementNumber() == 11);
    REQUIRE(node11->getParentNodes().size() == 1);
    REQUIRE(isSameStatements(node11->getParentNodes(), {9}));
    REQUIRE(node11->getChildrenNodes().empty());
}

TEST_CASE("Test nested whiles") {
    std::string sourceProgram = "procedure Proc1 { "
                                "   while (z > 1) { "            // 1
                                "       while (z > 1) { "        // 2
                                "           print p; "           // 3
                                "           while (z > 1) { "    // 4
                                "               print p; "       // 5
                                "               while (z > 1) { "// 6
                                "                   print p; "   // 7
                                "                   read r; "    // 8
                                "               } "
                                "           }"
                                "           x = 1;"// 9
                                "       }"
                                "       while (z > 1) { "// 10
                                "           print p; "   // 11
                                "           read r; "    // 12
                                "       }"
                                "   } "
                                "}";
    SPTokenizer tokenizer = SPTokenizer(sourceProgram);
    auto tokens = tokenizer.tokenize();
    SPParser parser;
    auto rootNode = parser.parse(tokens);

    std::unordered_map<ProcedureName, std::unordered_map<Statement, std::shared_ptr<CFGNode>>> cfgs =
            CFGBuilder::buildAllCFG(rootNode);
    REQUIRE(cfgs.size() == 1);

    REQUIRE(cfgs.count("Proc1") == 1);
    std::unordered_map<Statement, std::shared_ptr<CFGNode>> proc1CFG = cfgs["Proc1"];
    REQUIRE(proc1CFG.size() == 12);

    // stmt 1
    auto stmt1 = Statement(1, StatementType::While);
    REQUIRE(proc1CFG.count(stmt1) == 1);
    auto node1 = proc1CFG[stmt1];
    REQUIRE(node1->getStatementType() == StatementType::While);
    REQUIRE(node1->getStatementNumber() == 1);
    REQUIRE(node1->getParentNodes().size() == 1);
    REQUIRE(isSameStatements(node1->getParentNodes(), {10}));
    REQUIRE(node1->getChildrenNodes().size() == 1);
    REQUIRE(isSameStatements(node1->getChildrenNodes(), {2}));

    // stmt 2
    auto stmt2 = Statement(2, StatementType::While);
    REQUIRE(proc1CFG.count(stmt2) == 1);
    auto node2 = proc1CFG[stmt2];
    REQUIRE(node2->getStatementType() == StatementType::While);
    REQUIRE(node2->getStatementNumber() == 2);
    REQUIRE(node2->getParentNodes().size() == 2);
    REQUIRE(isSameStatements(node2->getParentNodes(), {1, 9}));
    REQUIRE(node2->getChildrenNodes().size() == 2);
    REQUIRE(isSameStatements(node2->getChildrenNodes(), {3, 10}));

    // stmt 3
    auto stmt3 = Statement(3, StatementType::Print);
    REQUIRE(proc1CFG.count(stmt3) == 1);
    auto node3 = proc1CFG[stmt3];
    REQUIRE(node3->getStatementType() == StatementType::Print);
    REQUIRE(node3->getStatementNumber() == 3);
    REQUIRE(node3->getParentNodes().size() == 1);
    REQUIRE(isSameStatements(node3->getParentNodes(), {2}));
    REQUIRE(node3->getChildrenNodes().size() == 1);
    REQUIRE(isSameStatements(node3->getChildrenNodes(), {4}));

    // stmt 4
    auto stmt4 = Statement(4, StatementType::While);
    REQUIRE(proc1CFG.count(stmt4) == 1);
    auto node4 = proc1CFG[stmt4];
    REQUIRE(node4->getStatementType() == StatementType::While);
    REQUIRE(node4->getStatementNumber() == 4);
    REQUIRE(node4->getParentNodes().size() == 2);
    REQUIRE(isSameStatements(node4->getParentNodes(), {3, 6}));
    REQUIRE(node4->getChildrenNodes().size() == 2);
    REQUIRE(isSameStatements(node4->getChildrenNodes(), {5, 9}));

    // stmt 5
    auto stmt5 = Statement(5, StatementType::Print);
    REQUIRE(proc1CFG.count(stmt5) == 1);
    auto node5 = proc1CFG[stmt5];
    REQUIRE(node5->getStatementType() == StatementType::Print);
    REQUIRE(node5->getStatementNumber() == 5);
    REQUIRE(node5->getParentNodes().size() == 1);
    REQUIRE(isSameStatements(node5->getParentNodes(), {4}));
    REQUIRE(node5->getChildrenNodes().size() == 1);
    REQUIRE(isSameStatements(node5->getChildrenNodes(), {6}));

    // stmt 6
    auto stmt6 = Statement(6, StatementType::While);
    REQUIRE(proc1CFG.count(stmt6) == 1);
    auto node6 = proc1CFG[stmt6];
    REQUIRE(node6->getStatementType() == StatementType::While);
    REQUIRE(node6->getStatementNumber() == 6);
    REQUIRE(node6->getParentNodes().size() == 2);
    REQUIRE(isSameStatements(node6->getParentNodes(), {5, 8}));
    REQUIRE(node6->getChildrenNodes().size() == 2);
    REQUIRE(isSameStatements(node6->getChildrenNodes(), {4, 7}));

    // stmt 7
    auto stmt7 = Statement(7, StatementType::Print);
    REQUIRE(proc1CFG.count(stmt7) == 1);
    auto node7 = proc1CFG[stmt7];
    REQUIRE(node7->getStatementType() == StatementType::Print);
    REQUIRE(node7->getStatementNumber() == 7);
    REQUIRE(node7->getParentNodes().size() == 1);
    REQUIRE(isSameStatements(node7->getParentNodes(), {6}));
    REQUIRE(node7->getChildrenNodes().size() == 1);
    REQUIRE(isSameStatements(node7->getChildrenNodes(), {8}));

    // stmt 8
    auto stmt8 = Statement(8, StatementType::Read);
    REQUIRE(proc1CFG.count(stmt8) == 1);
    auto node8 = proc1CFG[stmt8];
    REQUIRE(node8->getStatementType() == StatementType::Read);
    REQUIRE(node8->getStatementNumber() == 8);
    REQUIRE(node8->getParentNodes().size() == 1);
    REQUIRE(isSameStatements(node8->getParentNodes(), {7}));
    REQUIRE(node8->getChildrenNodes().size() == 1);
    REQUIRE(isSameStatements(node8->getChildrenNodes(), {6}));

    // stmt 9
    auto stmt9 = Statement(9, StatementType::Assign);
    REQUIRE(proc1CFG.count(stmt9) == 1);
    auto node9 = proc1CFG[stmt9];
    REQUIRE(node9->getStatementType() == StatementType::Assign);
    REQUIRE(node9->getStatementNumber() == 9);
    REQUIRE(node9->getParentNodes().size() == 1);
    REQUIRE(isSameStatements(node9->getParentNodes(), {4}));
    REQUIRE(node9->getChildrenNodes().size() == 1);
    REQUIRE(isSameStatements(node9->getChildrenNodes(), {2}));

    // stmt 10
    auto stmt10 = Statement(10, StatementType::While);
    REQUIRE(proc1CFG.count(stmt10) == 1);
    auto node10 = proc1CFG[stmt10];
    REQUIRE(node10->getStatementType() == StatementType::While);
    REQUIRE(node10->getStatementNumber() == 10);
    REQUIRE(node10->getParentNodes().size() == 2);
    REQUIRE(isSameStatements(node10->getParentNodes(), {2, 12}));
    REQUIRE(node10->getChildrenNodes().size() == 2);
    REQUIRE(isSameStatements(node10->getChildrenNodes(), {1, 11}));

    // stmt 11
    auto stmt11 = Statement(11, StatementType::Print);
    REQUIRE(proc1CFG.count(stmt11) == 1);
    auto node11 = proc1CFG[stmt11];
    REQUIRE(node11->getStatementType() == StatementType::Print);
    REQUIRE(node11->getStatementNumber() == 11);
    REQUIRE(node11->getParentNodes().size() == 1);
    REQUIRE(isSameStatements(node11->getParentNodes(), {10}));
    REQUIRE(node11->getChildrenNodes().size() == 1);
    REQUIRE(isSameStatements(node11->getChildrenNodes(), {12}));

    // stmt 12
    auto stmt12 = Statement(12, StatementType::Read);
    REQUIRE(proc1CFG.count(stmt12) == 1);
    auto node12 = proc1CFG[stmt12];
    REQUIRE(node12->getStatementType() == StatementType::Read);
    REQUIRE(node12->getStatementNumber() == 12);
    REQUIRE(node12->getParentNodes().size() == 1);
    REQUIRE(isSameStatements(node12->getParentNodes(), {11}));
    REQUIRE(node12->getChildrenNodes().size() == 1);
    REQUIRE(isSameStatements(node12->getChildrenNodes(), {10}));
}

TEST_CASE("Test nested whiles and ifs") {
    // Covers if-while and while-if nestings
    std::string sourceProgram = "procedure Proc1 { "
                                "   if (z > 1) then { "          // 1
                                "       while (z > 1) { "        // 2
                                "           print p; "           // 3
                                "           if (z > 1) then { "  // 4
                                "               while (z > 1) { "// 5
                                "                   print p; "   // 6
                                "                   read r; "    // 7
                                "               } "
                                "           } else { "
                                "               x = 1;"// 8
                                "           }"
                                "       }"
                                "       while (z > 1) { "// 9
                                "           print p; "   // 10
                                "           read r; "    // 11
                                "       }"
                                "   } else { "
                                "       while (x != v) { "// 12
                                "           read r; "     // 13
                                "       } "
                                "   }"
                                "}";
    SPTokenizer tokenizer = SPTokenizer(sourceProgram);
    auto tokens = tokenizer.tokenize();
    SPParser parser;
    auto rootNode = parser.parse(tokens);

    std::unordered_map<ProcedureName, std::unordered_map<Statement, std::shared_ptr<CFGNode>>> cfgs =
            CFGBuilder::buildAllCFG(rootNode);
    REQUIRE(cfgs.size() == 1);

    REQUIRE(cfgs.count("Proc1") == 1);
    std::unordered_map<Statement, std::shared_ptr<CFGNode>> proc1CFG = cfgs["Proc1"];
    REQUIRE(proc1CFG.size() == 13);

    // stmt 1
    auto stmt1 = Statement(1, StatementType::If);
    REQUIRE(proc1CFG.count(stmt1) == 1);
    auto node1 = proc1CFG[stmt1];
    REQUIRE(node1->getStatementType() == StatementType::If);
    REQUIRE(node1->getStatementNumber() == 1);
    REQUIRE(node1->getParentNodes().empty());
    REQUIRE(node1->getChildrenNodes().size() == 2);
    REQUIRE(isSameStatements(node1->getChildrenNodes(), {2, 12}));

    // stmt 2
    auto stmt2 = Statement(2, StatementType::While);
    REQUIRE(proc1CFG.count(stmt2) == 1);
    auto node2 = proc1CFG[stmt2];
    REQUIRE(node2->getStatementType() == StatementType::While);
    REQUIRE(node2->getStatementNumber() == 2);
    REQUIRE(node2->getParentNodes().size() == 3);
    REQUIRE(isSameStatements(node2->getParentNodes(), {1, 5, 8}));
    REQUIRE(node2->getChildrenNodes().size() == 2);
    REQUIRE(isSameStatements(node2->getChildrenNodes(), {3, 9}));

    // stmt 3
    auto stmt3 = Statement(3, StatementType::Print);
    REQUIRE(proc1CFG.count(stmt3) == 1);
    auto node3 = proc1CFG[stmt3];
    REQUIRE(node3->getStatementType() == StatementType::Print);
    REQUIRE(node3->getStatementNumber() == 3);
    REQUIRE(node3->getParentNodes().size() == 1);
    REQUIRE(isSameStatements(node3->getParentNodes(), {2}));
    REQUIRE(node3->getChildrenNodes().size() == 1);
    REQUIRE(isSameStatements(node3->getChildrenNodes(), {4}));

    // stmt 4
    auto stmt4 = Statement(4, StatementType::If);
    REQUIRE(proc1CFG.count(stmt4) == 1);
    auto node4 = proc1CFG[stmt4];
    REQUIRE(node4->getStatementType() == StatementType::If);
    REQUIRE(node4->getStatementNumber() == 4);
    REQUIRE(node4->getParentNodes().size() == 1);
    REQUIRE(isSameStatements(node4->getParentNodes(), {3}));
    REQUIRE(node4->getChildrenNodes().size() == 2);
    REQUIRE(isSameStatements(node4->getChildrenNodes(), {5, 8}));

    // stmt 5
    auto stmt5 = Statement(5, StatementType::While);
    REQUIRE(proc1CFG.count(stmt5) == 1);
    auto node5 = proc1CFG[stmt5];
    REQUIRE(node5->getStatementType() == StatementType::While);
    REQUIRE(node5->getStatementNumber() == 5);
    REQUIRE(node5->getParentNodes().size() == 2);
    REQUIRE(isSameStatements(node5->getParentNodes(), {4, 7}));
    REQUIRE(node5->getChildrenNodes().size() == 2);
    REQUIRE(isSameStatements(node5->getChildrenNodes(), {2, 6}));

    // stmt 6
    auto stmt6 = Statement(6, StatementType::Print);
    REQUIRE(proc1CFG.count(stmt6) == 1);
    auto node6 = proc1CFG[stmt6];
    REQUIRE(node6->getStatementType() == StatementType::Print);
    REQUIRE(node6->getStatementNumber() == 6);
    REQUIRE(node6->getParentNodes().size() == 1);
    REQUIRE(isSameStatements(node6->getParentNodes(), {5}));
    REQUIRE(node6->getChildrenNodes().size() == 1);
    REQUIRE(isSameStatements(node6->getChildrenNodes(), {7}));

    // stmt 7
    auto stmt7 = Statement(7, StatementType::Read);
    REQUIRE(proc1CFG.count(stmt7) == 1);
    auto node7 = proc1CFG[stmt7];
    REQUIRE(node7->getStatementType() == StatementType::Read);
    REQUIRE(node7->getStatementNumber() == 7);
    REQUIRE(node7->getParentNodes().size() == 1);
    REQUIRE(isSameStatements(node7->getParentNodes(), {6}));
    REQUIRE(node7->getChildrenNodes().size() == 1);
    REQUIRE(isSameStatements(node7->getChildrenNodes(), {5}));

    // stmt 8
    auto stmt8 = Statement(8, StatementType::Assign);
    REQUIRE(proc1CFG.count(stmt8) == 1);
    auto node8 = proc1CFG[stmt8];
    REQUIRE(node8->getStatementType() == StatementType::Assign);
    REQUIRE(node8->getStatementNumber() == 8);
    REQUIRE(node8->getParentNodes().size() == 1);
    REQUIRE(isSameStatements(node8->getParentNodes(), {4}));
    REQUIRE(node8->getChildrenNodes().size() == 1);
    REQUIRE(isSameStatements(node8->getChildrenNodes(), {2}));

    // stmt 9
    auto stmt9 = Statement(9, StatementType::While);
    REQUIRE(proc1CFG.count(stmt9) == 1);
    auto node9 = proc1CFG[stmt9];
    REQUIRE(node9->getStatementType() == StatementType::While);
    REQUIRE(node9->getStatementNumber() == 9);
    REQUIRE(node9->getParentNodes().size() == 2);
    REQUIRE(isSameStatements(node9->getParentNodes(), {2, 11}));
    REQUIRE(node9->getChildrenNodes().size() == 1);
    REQUIRE(isSameStatements(node9->getChildrenNodes(), {10}));

    // stmt 10
    auto stmt10 = Statement(10, StatementType::Print);
    REQUIRE(proc1CFG.count(stmt10) == 1);
    auto node10 = proc1CFG[stmt10];
    REQUIRE(node10->getStatementType() == StatementType::Print);
    REQUIRE(node10->getStatementNumber() == 10);
    REQUIRE(node10->getParentNodes().size() == 1);
    REQUIRE(isSameStatements(node10->getParentNodes(), {9}));
    REQUIRE(node10->getChildrenNodes().size() == 1);
    REQUIRE(isSameStatements(node10->getChildrenNodes(), {11}));

    // stmt 11
    auto stmt11 = Statement(11, StatementType::Read);
    REQUIRE(proc1CFG.count(stmt11) == 1);
    auto node11 = proc1CFG[stmt11];
    REQUIRE(node11->getStatementType() == StatementType::Read);
    REQUIRE(node11->getStatementNumber() == 11);
    REQUIRE(node11->getParentNodes().size() == 1);
    REQUIRE(isSameStatements(node11->getParentNodes(), {10}));
    REQUIRE(node11->getChildrenNodes().size() == 1);
    REQUIRE(isSameStatements(node11->getChildrenNodes(), {9}));

    // stmt 12
    auto stmt12 = Statement(12, StatementType::While);
    REQUIRE(proc1CFG.count(stmt12) == 1);
    auto node12 = proc1CFG[stmt12];
    REQUIRE(node12->getStatementType() == StatementType::While);
    REQUIRE(node12->getStatementNumber() == 12);
    REQUIRE(node12->getParentNodes().size() == 2);
    REQUIRE(isSameStatements(node12->getParentNodes(), {1, 13}));
    REQUIRE(node12->getChildrenNodes().size() == 1);
    REQUIRE(isSameStatements(node12->getChildrenNodes(), {13}));

    // stmt 13
    auto stmt13 = Statement(13, StatementType::Read);
    REQUIRE(proc1CFG.count(stmt13) == 1);
    auto node13 = proc1CFG[stmt13];
    REQUIRE(node13->getStatementType() == StatementType::Read);
    REQUIRE(node13->getStatementNumber() == 13);
    REQUIRE(node13->getParentNodes().size() == 1);
    REQUIRE(isSameStatements(node13->getParentNodes(), {12}));
    REQUIRE(node13->getChildrenNodes().size() == 1);
    REQUIRE(isSameStatements(node13->getChildrenNodes(), {12}));
    // parent and child should be the same
    REQUIRE(node13->getChildrenNodes().front() == node13->getParentNodes().front());
}