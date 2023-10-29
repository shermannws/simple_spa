#include <iostream>
#include <vector>

#include "Commons/Entities/AssignStatement.h"
#include "Commons/Entities/PrintStatement.h"
#include "Commons/Entities/ReadStatement.h"
#include "PKB/Pkb.h"
#include "PKB/PkbConcreteWriter.h"
#include "SP/AST/Nodes/ProgramNode.h"
#include "SP/AST/Traverser/Traverser.h"
#include "SP/AST/Visitors/CallsExtractorVisitor.h"
#include "SP/AST/Visitors/DesignExtractorVisitor.h"
#include "SP/AST/Visitors/EntityExtractorVisitor.h"
#include "SP/AST/Visitors/FollowsExtractorVisitor.h"
#include "SP/AST/Visitors/ModifiesExtractorVisitor.h"
#include "SP/AST/Visitors/ParentExtractorVisitor.h"
#include "SP/AST/Visitors/PatternExtractorVisitor.h"
#include "SP/AST/Visitors/UsesExtractorVisitor.h"
#include "SP/CFG/CFGBuilder.h"
#include "SP/CFG/CFGExtractor.h"
#include "SP/SP.h"
#include "SP/SPParser.h"
#include "SP/SPToken.h"
#include "SP/SPTokenType.h"
#include "TestingUtilities/ASTGenerator/ASTGenerator.h"
#include "TestingUtilities/TestFixture/IntegrationTestFixture.h"
#include "catch.hpp"

/*
Test the e2e addition through from SPTraverser to PKB stores
*/
TEST_CASE_METHOD(IntegrationTestFixture, "Test AST Traverser - e2e for Follows and Uses") {
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
    auto affectsRelationshipManager = std::make_shared<AffectsRelationshipManager>();

    auto pkbWriterManager = std::make_shared<PkbWriterManager>(
            assignmentManager, entitiesManager, followsRelationshipManager, usesRelationshipManager,
            modifiesRelationshipManager, parentRelationshipManager, callsRelationshipManager,
            modifiesProcRelationshipManager, usesProcRelationshipManager, ifPatternManager, whilePatternManager,
            nextRelationshipManager, affectsRelationshipManager);
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

    REQUIRE(*(entitiesManager->getStatement(std::make_shared<Statement>(1, StatementType::Assign))) ==
            *(std::make_shared<AssignStatement>(1)));
    REQUIRE(*(entitiesManager->getStatement(std::make_shared<Statement>(2, StatementType::Read))) ==
            *(std::make_shared<ReadStatement>(2, varName)));
    REQUIRE(*(entitiesManager->getStatement(std::make_shared<Statement>(3, StatementType::Print))) ==
            *(std::make_shared<PrintStatement>(3, varName)));

    REQUIRE(*(entitiesManager->getConstant(std::make_shared<Constant>(Constant("1")))) ==
            *(std::make_shared<Constant>("1")));


    auto VarV = Variable("v");
    auto usesV = usesRelationshipManager->getRelationshipTypeIdent(StatementType::Assign, VarV);
    REQUIRE(usesV.size() == 1);
    REQUIRE(usesV.find(AssignStatement(1)) != usesV.end());
    REQUIRE(usesV.find(Statement(1, StatementType::Assign)) != usesV.end());

    auto VarY = Variable("y");
    auto usesY = usesRelationshipManager->getRelationshipTypeIdent(StatementType::Assign, VarY);
    REQUIRE(usesY.size() == 1);
    REQUIRE(usesY.find(AssignStatement(1)) != usesY.end());
    REQUIRE(usesY.find(Statement(1, StatementType::Assign)) != usesY.end());

    auto Stmt1Stmt = Statement(1, StatementType::Assign);
    auto followsRSStmt = followsRelationshipManager->getRelationshipStmtType(Stmt1Stmt, StatementType::Stmt, true);
    REQUIRE(followsRSStmt.size() == 1);
    REQUIRE(followsRSStmt.find(ReadStatement(2, varName)) != followsRSStmt.end());

    auto Stmt1Assign = AssignStatement(1);
    auto followsRSAssign = followsRelationshipManager->getRelationshipStmtType(Stmt1Assign, StatementType::Stmt, true);
    REQUIRE(followsRSAssign.size() == 1);
    REQUIRE(followsRSAssign.find(ReadStatement(2, varName)) != followsRSAssign.end());

    auto Stmt2Stmt = Statement(2, StatementType::Read, varName);
    auto followsRS2Stmt = followsRelationshipManager->getRelationshipStmtType(Stmt2Stmt, StatementType::Stmt, true);
    REQUIRE(followsRS2Stmt.size() == 1);
    REQUIRE(followsRS2Stmt.find(PrintStatement(3, varName)) != followsRS2Stmt.end());

    auto Stmt2Read = ReadStatement(2, varName);
    auto followsRS2Read = followsRelationshipManager->getRelationshipStmtType(Stmt2Read, StatementType::Stmt, true);
    REQUIRE(followsRS2Read.size() == 1);
    REQUIRE(followsRS2Read.find(Statement(3, StatementType::Print, varName)) != followsRS2Read.end());
}


TEST_CASE_METHOD(IntegrationTestFixture, "Test AST Traverser - e2e with nested structure") {
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
    auto affectsRelationshipManager = std::make_shared<AffectsRelationshipManager>();

    auto pkbWriterManager = std::make_shared<PkbWriterManager>(
            assignmentManager, entitiesManager, followsRelationshipManager, usesRelationshipManager,
            modifiesRelationshipManager, parentRelationshipManager, callsRelationshipManager,
            modifiesProcRelationshipManager, usesProcRelationshipManager, ifPatternManager, whilePatternManager,
            nextRelationshipManager, affectsRelationshipManager);
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
    auto stmt5 = Statement(5, StatementType::Read);
    auto stmt6 = Statement(6, StatementType::Print);
    auto stmt7 = Statement(7, StatementType::While);
    auto stmt8 = Statement(8, StatementType::Assign);
    auto stmt9 = Statement(9, StatementType::Read);
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
    CHECK(follows1.find(stmt9) != follows1.end());
    auto follows3 = followsRelationshipManager->getRelationshipStmtType(stmt3, StatementType::Stmt, true);
    CHECK(follows3.size() == 1);
    CHECK(follows3.find(stmt4) != follows3.end());

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


TEST_CASE_METHOD(IntegrationTestFixture, "Test AST Traverser - test modifies and uses with procedure") {
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
    auto affectsRelationshipManager = std::make_shared<AffectsRelationshipManager>();

    auto pkbWriterManager = std::make_shared<PkbWriterManager>(
            assignmentManager, entitiesManager, followsRelationshipManager, usesRelationshipManager,
            modifiesRelationshipManager, parentRelationshipManager, callsRelationshipManager,
            modifiesProcRelationshipManager, usesProcRelationshipManager, ifPatternManager, whilePatternManager,
            nextRelationshipManager, affectsRelationshipManager);
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
    CHECK(*(entitiesManager->getProcedure(std::make_shared<Procedure>(Procedure("kk")))) ==
          *(std::make_shared<Procedure>("kk")));
    CHECK(*(entitiesManager->getProcedure(std::make_shared<Procedure>(Procedure("jj")))) ==
          *(std::make_shared<Procedure>("jj")));

    // Check Modifies with Procedure
    CHECK(modifiesProcRelationshipManager->isRelationship(proc1, varC));
    CHECK(modifiesProcRelationshipManager->isRelationship(proc2, varF));

    CHECK(!modifiesProcRelationshipManager->isRelationship(proc1, varA));
    CHECK(!modifiesProcRelationshipManager->isRelationship(proc1, varB));
    CHECK(!modifiesProcRelationshipManager->isRelationship(proc1, varD));
    CHECK(!modifiesProcRelationshipManager->isRelationship(proc1, varE));
    CHECK(!modifiesProcRelationshipManager->isRelationship(proc1, varF));
    CHECK(!modifiesProcRelationshipManager->isRelationship(proc1, varG));

    CHECK(!modifiesProcRelationshipManager->isRelationship(proc2, varA));
    CHECK(!modifiesProcRelationshipManager->isRelationship(proc2, varB));
    CHECK(!modifiesProcRelationshipManager->isRelationship(proc2, varC));
    CHECK(!modifiesProcRelationshipManager->isRelationship(proc2, varD));
    CHECK(!modifiesProcRelationshipManager->isRelationship(proc2, varE));
    CHECK(!modifiesProcRelationshipManager->isRelationship(proc2, varG));

    // Check Uses with Procedure
    CHECK(usesProcRelationshipManager->isRelationship(proc1, varA));
    CHECK(usesProcRelationshipManager->isRelationship(proc1, varB));
    CHECK(usesProcRelationshipManager->isRelationship(proc1, varD));
    CHECK(usesProcRelationshipManager->isRelationship(proc1, varE));

    CHECK(usesProcRelationshipManager->isRelationship(proc2, varG));

    CHECK(!usesProcRelationshipManager->isRelationship(proc1, varC));
    CHECK(!usesProcRelationshipManager->isRelationship(proc1, varF));
    CHECK(!usesProcRelationshipManager->isRelationship(proc1, varG));

    CHECK(!usesProcRelationshipManager->isRelationship(proc2, varA));
    CHECK(!usesProcRelationshipManager->isRelationship(proc2, varB));
    CHECK(!usesProcRelationshipManager->isRelationship(proc2, varC));
    CHECK(!usesProcRelationshipManager->isRelationship(proc2, varD));
    CHECK(!usesProcRelationshipManager->isRelationship(proc2, varE));
    CHECK(!usesProcRelationshipManager->isRelationship(proc2, varF));
}


TEST_CASE_METHOD(IntegrationTestFixture, "Test CFG Extractor - test Next extraction") {
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
                                "   call Proc1;"// stmt 17
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
    auto affectsRelationshipManager = std::make_shared<AffectsRelationshipManager>();

    auto pkbWriterManager = std::make_shared<PkbWriterManager>(
            assignmentManager, entitiesManager, followsRelationshipManager, usesRelationshipManager,
            modifiesRelationshipManager, parentRelationshipManager, callsRelationshipManager,
            modifiesProcRelationshipManager, usesProcRelationshipManager, ifPatternManager, whilePatternManager,
            nextRelationshipManager, affectsRelationshipManager);
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
    auto statement17 = Statement(17, StatementType::Call);

    // Check stores - positive cases
    CHECK(nextRelationshipManager->isRelationship(statement1, statement2, true));
    CHECK(nextRelationshipManager->isRelationship(statement2, statement3, true));
    CHECK(nextRelationshipManager->isRelationship(statement3, statement4, true));
    CHECK(nextRelationshipManager->isRelationship(statement4, statement5, true));
    CHECK(nextRelationshipManager->isRelationship(statement4, statement6, true));
    CHECK(nextRelationshipManager->isRelationship(statement5, statement7, true));
    CHECK(nextRelationshipManager->isRelationship(statement6, statement7, true));
    CHECK(nextRelationshipManager->isRelationship(statement7, statement8, true));
    CHECK(nextRelationshipManager->isRelationship(statement8, statement7, true));
    CHECK(nextRelationshipManager->isRelationship(statement12, statement13, true));
    CHECK(nextRelationshipManager->isRelationship(statement12, statement14, true));
    CHECK(nextRelationshipManager->isRelationship(statement15, statement16, true));
    CHECK(nextRelationshipManager->isRelationship(statement16, statement15, true));
    CHECK(nextRelationshipManager->isRelationship(statement15, statement17, true));

    // Check stores - negative cases - across procedures
    CHECK_FALSE(nextRelationshipManager->isRelationship(statement1, statement9, true));
    CHECK_FALSE(nextRelationshipManager->isRelationship(statement8, statement9, true));
    CHECK_FALSE(nextRelationshipManager->isRelationship(statement9, statement10, true));
    CHECK_FALSE(nextRelationshipManager->isRelationship(statement10, statement11, true));
    CHECK_FALSE(nextRelationshipManager->isRelationship(statement11, statement12, true));
    CHECK_FALSE(nextRelationshipManager->isRelationship(statement12, statement15, true));

    // Check stores - negative cases - within procedures
    CHECK_FALSE(nextRelationshipManager->isRelationship(statement1, statement1, true));
    CHECK_FALSE(nextRelationshipManager->isRelationship(statement11, statement11, true));
    CHECK_FALSE(nextRelationshipManager->isRelationship(statement1, statement8, true));
    CHECK_FALSE(nextRelationshipManager->isRelationship(statement4, statement7, true));
    CHECK_FALSE(nextRelationshipManager->isRelationship(statement13, statement14, true));
    CHECK_FALSE(nextRelationshipManager->isRelationship(statement1, statement3, true));
    CHECK_FALSE(nextRelationshipManager->isRelationship(statement2, statement4, true));
    CHECK_FALSE(nextRelationshipManager->isRelationship(statement3, statement5, true));
    CHECK_FALSE(nextRelationshipManager->isRelationship(statement3, statement6, true));
    CHECK_FALSE(nextRelationshipManager->isRelationship(statement5, statement8, true));
    CHECK_FALSE(nextRelationshipManager->isRelationship(statement6, statement8, true));
    CHECK_FALSE(nextRelationshipManager->isRelationship(statement16, statement17, true));

    // Check correct Statement subclass saved
    auto statements1 = nextRelationshipManager->getRelationshipStmtType(statement15, StatementType::Call, true);
    CHECK(statements1.size() == 1);
    CHECK(statements1.find(statement17) != statements1.end());
    CHECK(statements1.find(statement17)->getAttrValue() == "Proc1");

    auto statements2 = nextRelationshipManager->getRelationshipStmtType(statement12, StatementType::Print, true);
    CHECK(statements2.size() == 1);
    CHECK(statements2.find(statement13) != statements2.end());
    CHECK(statements2.find(statement13)->getAttrValue() == "p");

    auto statements3 = nextRelationshipManager->getRelationshipStmtType(statement1, StatementType::Read, true);
    CHECK(statements3.size() == 1);
    CHECK(statements3.find(statement2) != statements3.end());
    CHECK(statements3.find(statement2)->getAttrValue() == "x");
}


TEST_CASE_METHOD(IntegrationTestFixture, "Test AST Traverser - simple SIMPLE and exhaustive methods test") {
    std::string sourceCode = "\
        procedure p1 { \
            a = 1; \
		    call p2; \
	        if (b == c) then { \
                while (2 == 3) { \
			        read d; \
			    } \
            } else { \
			    print e; \
		    } \
		}\
        procedure p2 { \
			read f; \
		}";

    auto pkb = Pkb();
    auto pkbWriter = pkb.createPkbWriter();
    auto pkbReader = pkb.createPkbReader();

    auto sp = SP(pkbWriter);
    sp.startSPProcessing(sourceCode);

    // Declare Entities for testing
    auto proc1 = Procedure("p1");
    auto proc2 = Procedure("p2");

    auto stmt1 = Statement(1, StatementType::Assign);
    auto stmt2 = Statement(2, StatementType::Call);
    auto stmt3 = Statement(3, StatementType::If);
    auto stmt4 = Statement(4, StatementType::While);
    auto stmt5 = Statement(5, StatementType::Read);
    auto stmt6 = Statement(6, StatementType::Print);
    auto stmt7 = Statement(7, StatementType::Read);

    auto varA = Variable("a");
    auto varB = Variable("b");
    auto varC = Variable("c");
    auto varD = Variable("d");
    auto varE = Variable("e");
    auto varF = Variable("f");

    // Check each PkbReader Method
    CHECK(pkbReader->getAllVariables().size() == 6);
    CHECK(pkbReader->getAllConstants().size() == 3);
    CHECK(pkbReader->getAllProcedures().size() == 2);
    CHECK(pkbReader->getAllStatements().size() == 7);
    CHECK(pkbReader->getAllRead().size() == 2);
    CHECK(pkbReader->getAllPrint().size() == 1);
    CHECK(pkbReader->getAllWhile().size() == 1);
    CHECK(pkbReader->getAllIf().size() == 1);
    CHECK(pkbReader->getAllCall().size() == 1);
    CHECK(pkbReader->getAllAssign().size() == 1);

    CHECK(pkbReader->getUsesStmtPair(StatementType::Stmt).size() == 4);
    CHECK(pkbReader->getUsesProcPair().size() == 3);
    CHECK(pkbReader->getUsesTypeIdent(StatementType::Read, varE).empty());
    CHECK(pkbReader->getUsesTypeIdent(StatementType::If, varB).size() == 1);
    CHECK(pkbReader->getUsesProcIdent(varE).size() == 1);
    CHECK(pkbReader->getUsesStmt(StatementType::While).empty());
    CHECK(pkbReader->getUsesVar(stmt3).size() == 3);
    CHECK(pkbReader->getUsesVar(proc2).empty());
    CHECK(pkbReader->getUsesProc().size() == 1);
    CHECK(pkbReader->isStmtUsesVar(stmt3, varC));
    CHECK(pkbReader->isProcUsesVar(proc1, varC));
    CHECK(!pkbReader->hasUses(stmt1));
    CHECK(!pkbReader->hasUses(proc2));

    CHECK(pkbReader->getFollowsPair(StatementType::Stmt, StatementType::Stmt).size() == 2);
    CHECK(pkbReader->getFollowsStarPair(StatementType::Assign, StatementType::If).size() == 1);
    CHECK(pkbReader->getFollowsTypeStmt(StatementType::Call, stmt3).size() == 1);
    CHECK(pkbReader->getFollowsStarTypeStmt(StatementType::Call, stmt3).size() == 1);
    CHECK(pkbReader->getFollowsTypeWildcard(StatementType::If).empty());
    CHECK(pkbReader->getFollowsStarTypeWildcard(StatementType::If).empty());
    CHECK(pkbReader->getFollowsStmtType(stmt2, StatementType::Stmt).size() == 1);
    CHECK(pkbReader->getFollowsStarStmtType(stmt1, StatementType::Stmt).size() == 2);
    CHECK(pkbReader->getFollowsWildcardType(StatementType::While).empty());
    CHECK(pkbReader->getFollowsStarWildcardType(StatementType::Call).size() == 1);
    CHECK(pkbReader->isFollows(stmt1, stmt2));
    CHECK(pkbReader->isFollowsStar(stmt1, stmt3));
    CHECK(pkbReader->hasFollows());
    CHECK(pkbReader->hasFollowsStar());
    CHECK(pkbReader->hasLatterStmt(stmt1));
    CHECK(pkbReader->hasFormerStmt(stmt3));
    CHECK(pkbReader->hasLatterStarStmt(stmt2));
    CHECK(pkbReader->hasFormerStarStmt(stmt2));

    CHECK(pkbReader->getModifiesStmtPair(StatementType::Assign).size() == 1);
    CHECK(pkbReader->getModifiesProcPair().size() == 4);
    CHECK(pkbReader->getModifiesTypeIdent(StatementType::Stmt, varF).size() == 2);
    CHECK(pkbReader->getModifiesProcIdent(varF).size() == 2);
    CHECK(pkbReader->getModifiesStmt(StatementType::Stmt).size() == 6);
    CHECK(pkbReader->getModifiesProc().size() == 2);
    CHECK(pkbReader->getModifiesVar(proc2).size() == 1);
    CHECK(pkbReader->getModifiesVar(stmt7).size() == 1);
    CHECK(pkbReader->isStmtModifiesVar(stmt2, varF));
    CHECK(pkbReader->isProcModifiesVar(proc1, varF));
    CHECK(pkbReader->hasModifies(proc1));
    CHECK(pkbReader->hasModifies(stmt3));

    auto expr = Expression("(1)");
    auto wrongExpr = Expression("(2)");
    CHECK(pkbReader->getAllAssign().size() == 1);
    CHECK(pkbReader->getAssignStmtsByRhs(expr, false).size() == 1);
    CHECK(pkbReader->getAssignStmtsByRhs(expr, true).size() == 1);
    CHECK(pkbReader->getAllAssignStmtVarPair().size() == 1);
    CHECK(pkbReader->getAssignStmtsVarPairByRhs(wrongExpr, true).empty());
    CHECK(pkbReader->getAssignStmtsByLhs(varA).size() == 1);
    CHECK(pkbReader->getAssignStmtsByLhsRhs(varA, expr, false).size() == 1);
    CHECK(pkbReader->getAssignStmtsByLhsRhs(varA, wrongExpr, true).empty());

    CHECK(pkbReader->getParentPair(StatementType::Stmt, StatementType::Stmt).size() == 3);
    CHECK(pkbReader->getParentPair(StatementType::Read, StatementType::Stmt).empty());
    CHECK(pkbReader->getParentStarPair(StatementType::Stmt, StatementType::Stmt).size() == 4);
    CHECK(pkbReader->getParentTypeStmt(StatementType::Stmt, stmt4).size() == 1);
    CHECK(pkbReader->getParentStarTypeStmt(StatementType::Stmt, stmt5).size() == 2);
    CHECK(pkbReader->getParentTypeWildcard(StatementType::Stmt).size() == 2);
    CHECK(pkbReader->getParentStarTypeWildcard(StatementType::Stmt).size() == 2);
    CHECK(pkbReader->getParentStmtType(stmt3, StatementType::While).size() == 1);
    CHECK(pkbReader->getParentStarStmtType(stmt3, StatementType::Stmt).size() == 3);
    CHECK(pkbReader->getParentWildcardType(StatementType::Stmt).size() == 3);
    CHECK(pkbReader->getParentStarWildcardType(StatementType::Stmt).size() == 3);
    CHECK(!pkbReader->isParent(stmt1, stmt3));
    CHECK(pkbReader->isParentStar(stmt3, stmt4));
    CHECK(pkbReader->hasParent());
    CHECK(pkbReader->hasParentStar());
    CHECK(pkbReader->hasParentStmt(stmt4));
    CHECK(pkbReader->hasParentStarStmt(stmt6));
    CHECK(pkbReader->hasChildStmt(stmt3));
    CHECK(!pkbReader->hasChildStarStmt(stmt2));

    CHECK(pkbReader->hasCalls());
    CHECK(pkbReader->hasCallsStar());
    CHECK(pkbReader->isCallee(proc2));
    CHECK(pkbReader->isCalleeStar(proc2));
    CHECK(pkbReader->isCaller(proc1));
    CHECK(pkbReader->isCallerStar(proc1));
    CHECK(pkbReader->isCalls(proc1, proc2));
    CHECK(pkbReader->isCallsStar(proc1, proc2));
    CHECK(pkbReader->getCallees().size() == 1);
    CHECK(pkbReader->getCalleesStar().size() == 1);
    CHECK(pkbReader->getCallers().size() == 1);
    CHECK(pkbReader->getCallersStar().size() == 1);
    CHECK(pkbReader->getCallsPair().size() == 1);
    CHECK(pkbReader->getCallsStarPair().size() == 1);
    CHECK(pkbReader->getCallers(proc2).size() == 1);
    CHECK(pkbReader->getCallersStar(proc2).size() == 1);
    CHECK(pkbReader->getCallees(proc1).size() == 1);
    CHECK(pkbReader->getCalleesStar(proc1).size() == 1);

    CHECK(pkbReader->getNextPair(StatementType::If, StatementType::While).size() == 1);
    CHECK(pkbReader->getNextStarPair(StatementType::If, StatementType::While).size() == 1);
    CHECK(pkbReader->getNextStarSameStmt(StatementType::While).size() == 1);
    CHECK(pkbReader->getNextTypeStmt(StatementType::If, stmt4).size() == 1);
    CHECK(pkbReader->getNextStarTypeStmt(StatementType::If, stmt4).size() == 1);
    CHECK(pkbReader->getNextTypeWildcard(StatementType::Call).size() == 1);
    CHECK(pkbReader->getNextStarTypeWildcard(StatementType::Call).size() == 1);
    CHECK(pkbReader->getNextStmtType(stmt1, StatementType::Call).size() == 1);
    CHECK(pkbReader->getNextStarStmtType(stmt1, StatementType::While).size() == 1);
    CHECK(pkbReader->getNextWildcardType(StatementType::Call).size() == 1);
    CHECK(pkbReader->getNextStarWildcardType(StatementType::Call).size() == 1);
    CHECK(pkbReader->isNext(stmt1, stmt2));
    CHECK(pkbReader->isNextStar(stmt1, stmt6));
    CHECK(pkbReader->hasNext());
    CHECK(pkbReader->hasNextStar());
    CHECK(pkbReader->hasBeforeStmt(stmt2));
    CHECK(pkbReader->hasBeforeStarStmt(stmt3));
    CHECK(pkbReader->hasAfterStmt(stmt1));
    CHECK(pkbReader->hasAfterStarStmt(stmt1));

    CHECK(pkbReader->getAllIfPatternStmts().size() == 1);
    CHECK(pkbReader->getIfStmtsByVar(varB).size() == 1);
    CHECK(pkbReader->getAllIfStmtVarPair().size() == 2);

    CHECK(pkbReader->getAllWhilePatternStmts().empty());
    CHECK(pkbReader->getWhileStmtsByVar(varB).empty());
    CHECK(pkbReader->getAllWhileStmtVarPair().empty());

    CHECK(pkbReader->getAffectsPair(StatementType::Assign, StatementType::Assign).empty());
    CHECK(pkbReader->getAffectsTypeStmt(StatementType::Assign, stmt2).empty());
    CHECK(pkbReader->getAffectsTypeWildcard(StatementType::Stmt).empty());
    CHECK(pkbReader->getAffectsStmtType(stmt1, StatementType::Assign).empty());
    CHECK(pkbReader->getAffectsWildcardType(StatementType::Assign).empty());
    CHECK(!pkbReader->isAffects(stmt1, stmt2));
    CHECK(!pkbReader->hasAffects());
    CHECK(!pkbReader->hasAffectedStmt(stmt1));
    CHECK(!pkbReader->hasAffectsStmt(stmt1));
}