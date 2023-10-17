#include <iostream>
#include <vector>

#include "ASTGenerator.h"
#include "Commons/Entities/AssignStatement.h"
#include "Commons/Entities/CallStatement.h"
#include "Commons/Entities/IfStatement.h"
#include "Commons/Entities/PrintStatement.h"
#include "Commons/Entities/ReadStatement.h"
#include "Commons/Entities/WhileStatement.h"
#include "PKB/Pkb.h"
#include "PKB/PkbConcreteWriter.h"
#include "SP/AST/Nodes/ProgramNode.h"
#include "SP/AST/Traverser/Traverser.h"
#include "SP/AST/Visitors/DesignExtractorVisitor.h"
#include "SP/AST/Visitors/EntityExtractorVisitor.h"
#include "SP/AST/Visitors/FollowsExtractorVisitor.h"
#include "SP/AST/Visitors/ModifiesExtractorVisitor.h"
#include "SP/AST/Visitors/ParentExtractorVisitor.h"
#include "SP/AST/Visitors/UsesExtractorVisitor.h"
#include "SP/CFG/CFGBuilder.h"
#include "SP/CFG/CFGExtractor.h"
#include "SP/SPParser.h"
#include "SP/SPToken.h"
#include "SP/SPTokenType.h"
#include "catch.hpp"

/*
Test the e2e addition through from SPTraverser to PKB stores
*/
TEST_CASE("Test AST Traverser - e2e for Follows and Uses") {
    SPParser parser;
    VariableName varName = "num1";
    std::vector<SPToken> tokens = {SPToken(TokenType::Name, "procedure"),
                                   SPToken(TokenType::Name, "doMath"),
                                   SPToken(TokenType::OpenCurlyParenthesis, "{"),
                                   SPToken(TokenType::Name, "x"),
                                   SPToken(TokenType::Equals, "="),
                                   SPToken(TokenType::Name, "v"),
                                   SPToken(TokenType::ArithmeticOperator, "+"),
                                   SPToken(TokenType::Integer, "1"),
                                   SPToken(TokenType::ArithmeticOperator, "*"),
                                   SPToken(TokenType::Name, "y"),
                                   SPToken(TokenType::ArithmeticOperator, "+"),
                                   SPToken(TokenType::Name, "z"),
                                   SPToken(TokenType::ArithmeticOperator, "*"),
                                   SPToken(TokenType::Name, "t"),
                                   SPToken(TokenType::Semicolon, ";"),
                                   SPToken(TokenType::Name, "read"),
                                   SPToken(TokenType::Name, varName),
                                   SPToken(TokenType::Semicolon, ";"),
                                   SPToken(TokenType::Name, "print"),
                                   SPToken(TokenType::Name, varName),
                                   SPToken(TokenType::Semicolon, ";"),
                                   SPToken(TokenType::CloseCurlyParenthesis, "}")};

    std::shared_ptr<ProgramNode> rootNode = parser.parse(tokens);

    auto assignmentManager = std::make_shared<AssignPatternManager>(AssignPatternManager());
    auto entitiesManager = std::make_shared<EntitiesManager>(EntitiesManager());
    auto followsRelationshipManager = std::make_shared<FollowsRelationshipManager>();
    auto usesRelationshipManager = std::make_shared<UsesRelationshipManager>();
    auto modifiesRelationshipManager = std::make_shared<ModifiesRelationshipManager>();
    auto parentRelationshipManager = std::make_shared<ParentRelationshipManager>();
    auto callsRelationshipManager = std::make_shared<CallsRelationshipManager>();
    auto modifiesProcRelationshipManager = std::make_shared<ModifiesProcRelationshipManager>();
    auto usesProcRelationshipManager = std::make_shared<UsesProcRelationshipManager>();
    auto ifPatternManager = std::make_shared<IfPatternManager>(IfPatternManager());
    auto whilePatternManager = std::make_shared<WhilePatternManager>(WhilePatternManager());
    auto nextRelationshipManager = std::make_shared<NextRelationshipManager>();
    auto cfgManager = std::make_shared<CFGManager>();

    auto pkbWriterManager = std::make_shared<PkbWriterManager>(
            assignmentManager, entitiesManager, followsRelationshipManager, usesRelationshipManager,
            modifiesRelationshipManager, parentRelationshipManager, callsRelationshipManager,
            modifiesProcRelationshipManager, usesProcRelationshipManager, ifPatternManager, whilePatternManager,
            nextRelationshipManager, cfgManager);
    std::shared_ptr<PkbConcreteWriter> pkbWriter = std::make_shared<PkbConcreteWriter>(pkbWriterManager);

    std::shared_ptr<EntityExtractorVisitor> entityExtractor = std::make_shared<EntityExtractorVisitor>(pkbWriter);
    std::shared_ptr<FollowsExtractorVisitor> followsExtractor = std::make_shared<FollowsExtractorVisitor>(pkbWriter);
    std::shared_ptr<UsesExtractorVisitor> usesExtractor = std::make_shared<UsesExtractorVisitor>(pkbWriter);
    std::shared_ptr<ModifiesExtractorVisitor> modifiesExtractor = std::make_shared<ModifiesExtractorVisitor>(pkbWriter);

    std::vector<std::shared_ptr<DesignExtractorVisitor>> visitors = {entityExtractor, followsExtractor, usesExtractor,
                                                                     modifiesExtractor};

    // Traverse the AST from root node
    Traverser traverser = Traverser(visitors);
    traverser.traverse(rootNode);

    REQUIRE(*(entitiesManager->getProcedure(std::make_shared<Procedure>(Procedure("doMath")))) ==
            *(std::make_shared<Procedure>("doMath")));
    REQUIRE(*(entitiesManager->getVariable(std::make_shared<Variable>(Variable("x")))) ==
            *(std::make_shared<Variable>("x")));
    REQUIRE(*(entitiesManager->getVariable(std::make_shared<Variable>(Variable("v")))) ==
            *(std::make_shared<Variable>("v")));
    REQUIRE(*(entitiesManager->getVariable(std::make_shared<Variable>(Variable("y")))) ==
            *(std::make_shared<Variable>("y")));
    REQUIRE(*(entitiesManager->getVariable(std::make_shared<Variable>(Variable("z")))) ==
            *(std::make_shared<Variable>("z")));
    REQUIRE(*(entitiesManager->getVariable(std::make_shared<Variable>(Variable("t")))) ==
            *(std::make_shared<Variable>("t")));
    REQUIRE(*(entitiesManager->getVariable(std::make_shared<Variable>(Variable("num1")))) ==
            *(std::make_shared<Variable>("num1")));

    REQUIRE(*(entitiesManager->getStatement(std::make_shared<Statement>(AssignStatement(1)))) ==
            *(std::make_shared<AssignStatement>(1)));
    REQUIRE(*(entitiesManager->getStatement(std::make_shared<Statement>(ReadStatement(2, varName)))) ==
            *(std::make_shared<ReadStatement>(2, varName)));
    REQUIRE(*(entitiesManager->getStatement(std::make_shared<Statement>(PrintStatement(3, varName)))) ==
            *(std::make_shared<PrintStatement>(3, varName)));

    REQUIRE(*(entitiesManager->getConstant(std::make_shared<Constant>(Constant("1")))) ==
            *(std::make_shared<Constant>("1")));


    auto VarV = Variable("v");
    auto usesV = usesRelationshipManager->getRelationshipTypeIdent(StatementType::Assign, VarV);
    REQUIRE(usesV.size() == 1);
    REQUIRE(usesV.at(0) == AssignStatement(1));
    REQUIRE(usesV.at(0) == Statement(1, StatementType::Assign));

    auto VarY = Variable("y");
    auto usesY = usesRelationshipManager->getRelationshipTypeIdent(StatementType::Assign, VarY);
    REQUIRE(usesY.size() == 1);
    REQUIRE(usesY.at(0) == AssignStatement(1));
    REQUIRE(usesY.at(0) == Statement(1, StatementType::Assign));

    auto Stmt1Stmt = Statement(1, StatementType::Assign);
    auto followsRSStmt = followsRelationshipManager->getRelationshipStmtType(Stmt1Stmt, StatementType::Stmt, true);
    REQUIRE(followsRSStmt.size() == 1);
    REQUIRE(followsRSStmt.at(0) == ReadStatement(2, varName));
    auto Stmt1Assign = AssignStatement(1);
    auto followsRSAssign = followsRelationshipManager->getRelationshipStmtType(Stmt1Assign, StatementType::Stmt, true);
    REQUIRE(followsRSAssign.size() == 1);
    REQUIRE(followsRSAssign.at(0) == Statement(2, StatementType::Read, varName));

    auto Stmt2Stmt = Statement(2, StatementType::Read, varName);
    auto followsRS2Stmt = followsRelationshipManager->getRelationshipStmtType(Stmt2Stmt, StatementType::Stmt, true);
    REQUIRE(followsRS2Stmt.size() == 1);
    REQUIRE(followsRS2Stmt.at(0) == PrintStatement(3, varName));
    auto Stmt2Read = ReadStatement(2, varName);
    auto followsRS2Read = followsRelationshipManager->getRelationshipStmtType(Stmt2Read, StatementType::Stmt, true);
    REQUIRE(followsRS2Read.size() == 1);
    REQUIRE(followsRS2Read.at(0) == Statement(3, StatementType::Print, varName));
}


TEST_CASE("Test AST Traverser - e2e with nested structure") {
    std::string sourceCode = "\
        procedure kk { \
        if (a < b) then { \
            if (c<d) then { \
            e = f; \
            g = 1; \
            } else { \
            read h; \
            } \
        } else { \
            print i; \
            while ( j<k ) { \
                a = 1; \
            } \
        } \
        read j; \
        m = x + c;\
        }";

    std::shared_ptr<ProgramNode> rootNode = ASTGenerator::generate(sourceCode);

    auto assignmentManager = std::make_shared<AssignPatternManager>(AssignPatternManager());
    auto entitiesManager = std::make_shared<EntitiesManager>(EntitiesManager());
    auto followsRelationshipManager = std::make_shared<FollowsRelationshipManager>();
    auto usesRelationshipManager = std::make_shared<UsesRelationshipManager>();
    auto modifiesRelationshipManager = std::make_shared<ModifiesRelationshipManager>();
    auto parentRelationshipManager = std::make_shared<ParentRelationshipManager>();
    auto callsRelationshipManager = std::make_shared<CallsRelationshipManager>();
    auto modifiesProcRelationshipManager = std::make_shared<ModifiesProcRelationshipManager>();
    auto usesProcRelationshipManager = std::make_shared<UsesProcRelationshipManager>();
    auto ifPatternManager = std::make_shared<IfPatternManager>(IfPatternManager());
    auto whilePatternManager = std::make_shared<WhilePatternManager>(WhilePatternManager());
    auto nextRelationshipManager = std::make_shared<NextRelationshipManager>();
    auto cfgManager = std::make_shared<CFGManager>();

    auto pkbWriterManager = std::make_shared<PkbWriterManager>(
            assignmentManager, entitiesManager, followsRelationshipManager, usesRelationshipManager,
            modifiesRelationshipManager, parentRelationshipManager, callsRelationshipManager,
            modifiesProcRelationshipManager, usesProcRelationshipManager, ifPatternManager, whilePatternManager,
            nextRelationshipManager, cfgManager);
    std::shared_ptr<PkbConcreteWriter> pkbWriter = std::make_shared<PkbConcreteWriter>(pkbWriterManager);

    std::shared_ptr<EntityExtractorVisitor> entityExtractor = std::make_shared<EntityExtractorVisitor>(pkbWriter);
    std::shared_ptr<FollowsExtractorVisitor> followsExtractor = std::make_shared<FollowsExtractorVisitor>(pkbWriter);
    std::shared_ptr<UsesExtractorVisitor> usesExtractor = std::make_shared<UsesExtractorVisitor>(pkbWriter);
    std::shared_ptr<ModifiesExtractorVisitor> modifiesExtractor = std::make_shared<ModifiesExtractorVisitor>(pkbWriter);
    std::shared_ptr<ParentExtractorVisitor> parentExtractor = std::make_shared<ParentExtractorVisitor>(pkbWriter);

    std::vector<std::shared_ptr<DesignExtractorVisitor>> visitors = {entityExtractor, followsExtractor, usesExtractor,
                                                                     modifiesExtractor, parentExtractor};

    // Traverse the AST from root node
    Traverser traverser = Traverser(visitors);
    traverser.traverse(rootNode);

    // Declare Entities for testing
    auto stmt1 = Statement(1, StatementType::If);
    auto stmt2 = Statement(2, StatementType::If);
    auto stmt3 = Statement(3, StatementType::Assign);
    auto stmt4 = Statement(4, StatementType::Assign);
    auto stmt5 = Statement(5, StatementType::Read, "h");
    auto stmt6 = Statement(6, StatementType::Print, "i");
    auto stmt7 = Statement(7, StatementType::While);
    auto stmt8 = Statement(8, StatementType::Assign);
    auto stmt9 = Statement(9, StatementType::Read, "j");
    auto stmt10 = Statement(10, StatementType::Assign);

    auto varA = Variable("a");
    auto varB = Variable("b");
    auto varC = Variable("c");
    auto varD = Variable("d");
    auto varE = Variable("e");
    auto varF = Variable("f");
    auto varG = Variable("g");
    auto varH = Variable("h");
    auto varI = Variable("i");
    auto varJ = Variable("j");
    auto varK = Variable("k");
    auto varX = Variable("x");
    auto varM = Variable("m");

    // Check Procedure
    CHECK(*(entitiesManager->getProcedure(std::make_shared<Procedure>(Procedure("kk")))) ==
          *(std::make_shared<Procedure>("kk")));

    // Check Follows
    auto follows1 = followsRelationshipManager->getRelationshipStmtType(stmt1, StatementType::Stmt, true);
    CHECK(follows1.size() == 1);
    CHECK(follows1.at(0) == stmt9);
    auto follows3 = followsRelationshipManager->getRelationshipStmtType(stmt3, StatementType::Stmt, true);
    CHECK(follows3.size() == 1);
    CHECK(follows3.at(0) == Statement(4, StatementType::Assign));


    // Check Follows*
    auto follows1star = followsRelationshipManager->getRelationshipStmtType(stmt1, StatementType::Stmt, false);
    CHECK(follows1star.size() == 2);
    CHECK(std::find(follows1star.begin(), follows1star.end(), stmt9) != follows1star.end());
    CHECK(std::find(follows1star.begin(), follows1star.end(), stmt10) != follows1star.end());

    // Check Uses exhaustively
    CHECK(usesRelationshipManager->getRelationshipStmtPair(StatementType::Stmt).size() == 17);
    CHECK(usesRelationshipManager->isRelationship(stmt1, varA));
    CHECK(usesRelationshipManager->isRelationship(stmt1, varB));
    CHECK(usesRelationshipManager->isRelationship(stmt1, varC));
    CHECK(usesRelationshipManager->isRelationship(stmt1, varD));
    CHECK(usesRelationshipManager->isRelationship(stmt1, varF));
    CHECK(usesRelationshipManager->isRelationship(stmt1, varI));
    CHECK(usesRelationshipManager->isRelationship(stmt1, varJ));
    CHECK(usesRelationshipManager->isRelationship(stmt1, varK));
    CHECK(usesRelationshipManager->isRelationship(stmt1, varC));
    CHECK(usesRelationshipManager->isRelationship(stmt1, varD));
    CHECK(usesRelationshipManager->isRelationship(stmt1, varF));
    CHECK(usesRelationshipManager->isRelationship(stmt3, varF));
    CHECK(usesRelationshipManager->isRelationship(stmt6, varI));
    CHECK(usesRelationshipManager->isRelationship(stmt7, varJ));
    CHECK(usesRelationshipManager->isRelationship(stmt7, varK));
    CHECK(usesRelationshipManager->isRelationship(stmt10, varX));
    CHECK(usesRelationshipManager->isRelationship(stmt10, varC));

    CHECK(!usesRelationshipManager->isRelationship(stmt5, varH));
    CHECK(!usesRelationshipManager->isRelationship(stmt8, varA));
    CHECK(!usesRelationshipManager->isRelationship(stmt10, varM));


    // Check Modifies
    CHECK(modifiesRelationshipManager->isRelationship(stmt1, varE));
    CHECK(modifiesRelationshipManager->isRelationship(stmt1, varG));
    CHECK(modifiesRelationshipManager->isRelationship(stmt1, varH));
    CHECK(modifiesRelationshipManager->isRelationship(stmt1, varA));

    CHECK(modifiesRelationshipManager->isRelationship(stmt2, varE));
    CHECK(modifiesRelationshipManager->isRelationship(stmt2, varG));
    CHECK(modifiesRelationshipManager->isRelationship(stmt2, varH));

    CHECK(modifiesRelationshipManager->isRelationship(stmt3, varE));
    CHECK(modifiesRelationshipManager->isRelationship(stmt4, varG));
    CHECK(modifiesRelationshipManager->isRelationship(stmt5, varH));

    CHECK(modifiesRelationshipManager->isRelationship(stmt7, varA));
    CHECK(modifiesRelationshipManager->isRelationship(stmt8, varA));

    CHECK(modifiesRelationshipManager->isRelationship(stmt9, varJ));
    CHECK(modifiesRelationshipManager->isRelationship(stmt10, varM));

    CHECK(!modifiesRelationshipManager->isRelationship(stmt1, varB));
    CHECK(!modifiesRelationshipManager->isRelationship(stmt10, varX));

    // Check Parent
    CHECK(parentRelationshipManager->isRelationship(stmt1, stmt2, true));
    CHECK(parentRelationshipManager->isRelationship(stmt1, stmt6, true));
    CHECK(parentRelationshipManager->isRelationship(stmt1, stmt7, true));
    CHECK(parentRelationshipManager->isRelationship(stmt2, stmt3, true));
    CHECK(parentRelationshipManager->isRelationship(stmt2, stmt4, true));
    CHECK(parentRelationshipManager->isRelationship(stmt2, stmt5, true));
    CHECK(parentRelationshipManager->isRelationship(stmt7, stmt8, true));

    // Check Parent*
    CHECK(parentRelationshipManager->isRelationship(stmt1, stmt3, false));
    CHECK(parentRelationshipManager->isRelationship(stmt1, stmt4, false));
    CHECK(parentRelationshipManager->isRelationship(stmt1, stmt5, false));
    CHECK(parentRelationshipManager->isRelationship(stmt1, stmt8, false));
}


TEST_CASE("Test AST Traverser - test modifies and uses with procedure") {
    std::string sourceCode = "\
        procedure kk { \
        if (a < b) then { \
            c = d; \
        } else { \
            print e; \
        } \
        }\
        procedure jj { \
        f = g; \
        }\
        ";

    std::shared_ptr<ProgramNode> rootNode = ASTGenerator::generate(sourceCode);

    auto assignmentManager = std::make_shared<AssignPatternManager>(AssignPatternManager());
    auto entitiesManager = std::make_shared<EntitiesManager>(EntitiesManager());
    auto followsRelationshipManager = std::make_shared<FollowsRelationshipManager>();
    auto usesRelationshipManager = std::make_shared<UsesRelationshipManager>();
    auto modifiesRelationshipManager = std::make_shared<ModifiesRelationshipManager>();
    auto parentRelationshipManager = std::make_shared<ParentRelationshipManager>();
    auto callsRelationshipManager = std::make_shared<CallsRelationshipManager>();
    auto modifiesProcRelationshipManager = std::make_shared<ModifiesProcRelationshipManager>();
    auto usesProcRelationshipManager = std::make_shared<UsesProcRelationshipManager>();
    auto ifPatternManager = std::make_shared<IfPatternManager>(IfPatternManager());
    auto whilePatternManager = std::make_shared<WhilePatternManager>(WhilePatternManager());
    auto nextRelationshipManager = std::make_shared<NextRelationshipManager>();
    auto cfgManager = std::make_shared<CFGManager>();

    auto pkbWriterManager = std::make_shared<PkbWriterManager>(
            assignmentManager, entitiesManager, followsRelationshipManager, usesRelationshipManager,
            modifiesRelationshipManager, parentRelationshipManager, callsRelationshipManager,
            modifiesProcRelationshipManager, usesProcRelationshipManager, ifPatternManager, whilePatternManager,
            nextRelationshipManager, cfgManager);
    std::shared_ptr<PkbConcreteWriter> pkbWriter = std::make_shared<PkbConcreteWriter>(pkbWriterManager);

    std::shared_ptr<EntityExtractorVisitor> entityExtractor = std::make_shared<EntityExtractorVisitor>(pkbWriter);
    std::shared_ptr<FollowsExtractorVisitor> followsExtractor = std::make_shared<FollowsExtractorVisitor>(pkbWriter);
    std::shared_ptr<UsesExtractorVisitor> usesExtractor = std::make_shared<UsesExtractorVisitor>(pkbWriter);
    std::shared_ptr<ModifiesExtractorVisitor> modifiesExtractor = std::make_shared<ModifiesExtractorVisitor>(pkbWriter);
    std::shared_ptr<ParentExtractorVisitor> parentExtractor = std::make_shared<ParentExtractorVisitor>(pkbWriter);

    std::vector<std::shared_ptr<DesignExtractorVisitor>> visitors = {entityExtractor, followsExtractor, usesExtractor,
                                                                     modifiesExtractor, parentExtractor};

    // Traverse the AST from root node
    Traverser traverser = Traverser(visitors);
    traverser.traverse(rootNode);

    // Declare Entities for testing
    auto proc1 = Procedure("kk");
    auto proc2 = Procedure("jj");

    auto varA = Variable("a");
    auto varB = Variable("b");
    auto varC = Variable("c");
    auto varD = Variable("d");
    auto varE = Variable("e");
    auto varF = Variable("f");
    auto varG = Variable("g");

    // Check Procedure
    REQUIRE(*(entitiesManager->getProcedure(std::make_shared<Procedure>(Procedure("kk")))) ==
            *(std::make_shared<Procedure>("kk")));
    REQUIRE(*(entitiesManager->getProcedure(std::make_shared<Procedure>(Procedure("jj")))) ==
            *(std::make_shared<Procedure>("jj")));

    // Check Modifies with Procedure
    REQUIRE(modifiesProcRelationshipManager->isRelationship(proc1, varC));
    REQUIRE(modifiesProcRelationshipManager->isRelationship(proc2, varF));

    REQUIRE(!modifiesProcRelationshipManager->isRelationship(proc1, varA));
    REQUIRE(!modifiesProcRelationshipManager->isRelationship(proc1, varB));
    REQUIRE(!modifiesProcRelationshipManager->isRelationship(proc1, varD));
    REQUIRE(!modifiesProcRelationshipManager->isRelationship(proc1, varE));
    REQUIRE(!modifiesProcRelationshipManager->isRelationship(proc1, varF));
    REQUIRE(!modifiesProcRelationshipManager->isRelationship(proc1, varG));

    REQUIRE(!modifiesProcRelationshipManager->isRelationship(proc2, varA));
    REQUIRE(!modifiesProcRelationshipManager->isRelationship(proc2, varB));
    REQUIRE(!modifiesProcRelationshipManager->isRelationship(proc2, varC));
    REQUIRE(!modifiesProcRelationshipManager->isRelationship(proc2, varD));
    REQUIRE(!modifiesProcRelationshipManager->isRelationship(proc2, varE));
    REQUIRE(!modifiesProcRelationshipManager->isRelationship(proc2, varG));

    // Check Uses with Procedure
    REQUIRE(usesProcRelationshipManager->isRelationship(proc1, varA));
    REQUIRE(usesProcRelationshipManager->isRelationship(proc1, varB));
    REQUIRE(usesProcRelationshipManager->isRelationship(proc1, varD));
    REQUIRE(usesProcRelationshipManager->isRelationship(proc1, varE));

    REQUIRE(usesProcRelationshipManager->isRelationship(proc2, varG));

    REQUIRE(!usesProcRelationshipManager->isRelationship(proc1, varC));
    REQUIRE(!usesProcRelationshipManager->isRelationship(proc1, varF));
    REQUIRE(!usesProcRelationshipManager->isRelationship(proc1, varG));

    REQUIRE(!usesProcRelationshipManager->isRelationship(proc2, varA));
    REQUIRE(!usesProcRelationshipManager->isRelationship(proc2, varB));
    REQUIRE(!usesProcRelationshipManager->isRelationship(proc2, varC));
    REQUIRE(!usesProcRelationshipManager->isRelationship(proc2, varD));
    REQUIRE(!usesProcRelationshipManager->isRelationship(proc2, varE));
    REQUIRE(!usesProcRelationshipManager->isRelationship(proc2, varF));
}


TEST_CASE("Test CFG Extractor - test Next extraction") {
    std::string sourceProgram = "procedure Proc1 {"
                                "   x = 1 + 2 * y - (1 / var) % 5;"// stmt 1
                                "   read x;"                       // stmt 2
                                "   print y;"                      // stmt 3
                                "   if (x > 1) then {"             // stmt 4
                                "       z = y;"                    // stmt 5
                                "   } else {"
                                "       var1 = 5;"// stmt 6
                                "   } "
                                "   while (1 != 3) {"// stmt 7
                                "       print c;"    // stmt 8
                                "   }"
                                "}"
                                "procedure Proc2 { "
                                "   read x; "// stmt 9
                                "}"
                                "procedure Proc3 { "
                                "   print y; "// stmt 10
                                "}"
                                "procedure Proc4 { "
                                "   call Proc1; "// stmt 11
                                "}"
                                "procedure Proc5 { "
                                "   if (z > 1) then { "// stmt 12
                                "       print p; "     // stmt 13
                                "   } else { "
                                "       read r; "// stmt 14
                                "   } "
                                "}"
                                "procedure Proc6 { "
                                "   while (z <= w) { "// stmt 15
                                "       x = 2; "      // stmt 16
                                "   } "
                                "}";

    std::shared_ptr<ProgramNode> rootNode = ASTGenerator::generate(sourceProgram);

    // Create PkbWriter manually to allow checking of individual managers
    auto assignmentManager = std::make_shared<AssignPatternManager>(AssignPatternManager());
    auto entitiesManager = std::make_shared<EntitiesManager>(EntitiesManager());
    auto followsRelationshipManager = std::make_shared<FollowsRelationshipManager>();
    auto usesRelationshipManager = std::make_shared<UsesRelationshipManager>();
    auto modifiesRelationshipManager = std::make_shared<ModifiesRelationshipManager>();
    auto parentRelationshipManager = std::make_shared<ParentRelationshipManager>();
    auto callsRelationshipManager = std::make_shared<CallsRelationshipManager>();
    auto modifiesProcRelationshipManager = std::make_shared<ModifiesProcRelationshipManager>();
    auto usesProcRelationshipManager = std::make_shared<UsesProcRelationshipManager>();
    auto ifPatternManager = std::make_shared<IfPatternManager>(IfPatternManager());
    auto whilePatternManager = std::make_shared<WhilePatternManager>(WhilePatternManager());
    auto nextRelationshipManager = std::make_shared<NextRelationshipManager>();
    auto cfgManager = std::make_shared<CFGManager>();

    auto pkbWriterManager = std::make_shared<PkbWriterManager>(
            assignmentManager, entitiesManager, followsRelationshipManager, usesRelationshipManager,
            modifiesRelationshipManager, parentRelationshipManager, callsRelationshipManager,
            modifiesProcRelationshipManager, usesProcRelationshipManager, ifPatternManager, whilePatternManager,
            nextRelationshipManager, cfgManager);
    std::shared_ptr<PkbConcreteWriter> pkbWriter = std::make_shared<PkbConcreteWriter>(pkbWriterManager);

    auto cfgs = CFGBuilder::buildAllCFG(rootNode);
    CFGExtractor cfgExtractor(pkbWriter);
    cfgExtractor.extractRelationships(cfgs);

    // Create Statements
    auto statement1 = Statement(1, StatementType::Assign);
    auto statement2 = Statement(2, StatementType::Read);
    auto statement3 = Statement(3, StatementType::Print);
    auto statement4 = Statement(4, StatementType::If);
    auto statement5 = Statement(5, StatementType::Assign);
    auto statement6 = Statement(6, StatementType::Assign);
    auto statement7 = Statement(7, StatementType::While);
    auto statement8 = Statement(8, StatementType::Print);
    auto statement9 = Statement(9, StatementType::Read);
    auto statement10 = Statement(10, StatementType::Print);
    auto statement11 = Statement(11, StatementType::Call);
    auto statement12 = Statement(12, StatementType::If);
    auto statement13 = Statement(13, StatementType::Print);
    auto statement14 = Statement(14, StatementType::Read);
    auto statement15 = Statement(15, StatementType::While);
    auto statement16 = Statement(16, StatementType::Assign);

    // Check stores - positive cases
    REQUIRE(nextRelationshipManager->isRelationship(statement1, statement2, true));
    REQUIRE(nextRelationshipManager->isRelationship(statement2, statement3, true));
    REQUIRE(nextRelationshipManager->isRelationship(statement3, statement4, true));
    REQUIRE(nextRelationshipManager->isRelationship(statement4, statement5, true));
    REQUIRE(nextRelationshipManager->isRelationship(statement4, statement6, true));
    REQUIRE(nextRelationshipManager->isRelationship(statement5, statement7, true));
    REQUIRE(nextRelationshipManager->isRelationship(statement6, statement7, true));
    REQUIRE(nextRelationshipManager->isRelationship(statement7, statement8, true));
    REQUIRE(nextRelationshipManager->isRelationship(statement8, statement7, true));
    REQUIRE(nextRelationshipManager->isRelationship(statement12, statement13, true));
    REQUIRE(nextRelationshipManager->isRelationship(statement12, statement14, true));
    REQUIRE(nextRelationshipManager->isRelationship(statement15, statement16, true));
    REQUIRE(nextRelationshipManager->isRelationship(statement16, statement15, true));

    // Check stores - negative cases - across procedures
    REQUIRE_FALSE(nextRelationshipManager->isRelationship(statement1, statement9, true));
    REQUIRE_FALSE(nextRelationshipManager->isRelationship(statement8, statement9, true));
    REQUIRE_FALSE(nextRelationshipManager->isRelationship(statement9, statement10, true));
    REQUIRE_FALSE(nextRelationshipManager->isRelationship(statement10, statement11, true));
    REQUIRE_FALSE(nextRelationshipManager->isRelationship(statement11, statement12, true));
    REQUIRE_FALSE(nextRelationshipManager->isRelationship(statement12, statement15, true));

    // Check stores - negative cases - within procedures
    REQUIRE_FALSE(nextRelationshipManager->isRelationship(statement1, statement1, true));
    REQUIRE_FALSE(nextRelationshipManager->isRelationship(statement11, statement11, true));
    REQUIRE_FALSE(nextRelationshipManager->isRelationship(statement1, statement8, true));
    REQUIRE_FALSE(nextRelationshipManager->isRelationship(statement4, statement7, true));
    REQUIRE_FALSE(nextRelationshipManager->isRelationship(statement13, statement14, true));
    REQUIRE_FALSE(nextRelationshipManager->isRelationship(statement1, statement3, true));
    REQUIRE_FALSE(nextRelationshipManager->isRelationship(statement2, statement4, true));
    REQUIRE_FALSE(nextRelationshipManager->isRelationship(statement3, statement5, true));
    REQUIRE_FALSE(nextRelationshipManager->isRelationship(statement3, statement6, true));
    REQUIRE_FALSE(nextRelationshipManager->isRelationship(statement5, statement8, true));
    REQUIRE_FALSE(nextRelationshipManager->isRelationship(statement6, statement8, true));
}