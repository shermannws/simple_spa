#include <vector>
#include <iostream>

#include "catch.hpp"
#include "SP/SPParser.h"
#include "SP/SPToken.h"
#include "SP/SPTokenType.h"
#include "SP/AST/Nodes/ProgramNode.h"
#include "SP/AST/Visitors/DesignExtractorVisitor.h"
#include "SP/AST/Visitors/EntityExtractorVisitor.h"
#include "SP/AST/Visitors/FollowsExtractorVisitor.h"
#include "SP/AST/Visitors/UsesExtractorVisitor.h"
#include "SP/AST/Traverser/Traverser.h"
#include "PKB/Pkb.h"
#include "PKB/PkbConcreteWriter.h"

TEST_CASE("Test AST Traverser") {
    SPParser parser;
    std::string varName = "num1";
    std::vector<SPToken> tokens = {
            SPToken(TokenType::NAME, "procedure"),
            SPToken(TokenType::NAME, "doMath"),
            SPToken(TokenType::OPEN_CURLY_PARAN, "{"),
            SPToken(TokenType::NAME, "x"),
            SPToken(TokenType::EQUALS, "="),
            SPToken(TokenType::NAME, "v"),
            SPToken(TokenType::ARITHMETIC_OPERATOR, "+"),
            SPToken(TokenType::INTEGER, "1"),
            SPToken(TokenType::ARITHMETIC_OPERATOR, "*"),
            SPToken(TokenType::NAME, "y"),
            SPToken(TokenType::ARITHMETIC_OPERATOR, "+"),
            SPToken(TokenType::NAME, "z"),
            SPToken(TokenType::ARITHMETIC_OPERATOR, "*"),
            SPToken(TokenType::NAME, "t"),
            SPToken(TokenType::SEMICOLON, ";"),
            SPToken(TokenType::NAME, "read"),
            SPToken(TokenType::NAME, varName),
            SPToken(TokenType::SEMICOLON, ";"),
            SPToken(TokenType::NAME, "print"),
            SPToken(TokenType::NAME, varName),
            SPToken(TokenType::SEMICOLON, ";"),
            SPToken(TokenType::CLOSE_CURLY_PARAN, "}")
    };
    std::shared_ptr<ProgramNode> rootNode = parser.parse(tokens);

    auto assignmentManager = std::make_shared<AssignmentManager>(AssignmentManager());
    auto constantStore = std::make_shared<ConstantStore>(ConstantStore());
    auto procedureStore = std::make_shared<ProcedureStore>(ProcedureStore());
    auto statementStore = std::make_shared<StatementStore>(StatementStore());
    auto variableStore = std::make_shared<VariableStore>(VariableStore());
    auto followsRelationshipManager = std::make_shared<FollowsRelationshipManager>();
    auto usesRelationshipManager = std::make_shared<UsesRelationshipManager>();
    auto pkbWriterManager = std::make_shared<PkbWriterManager>(
            assignmentManager,
            constantStore,
            procedureStore,
            statementStore,
            variableStore,
            followsRelationshipManager,
            usesRelationshipManager
    );
    std::shared_ptr<PkbConcreteWriter> pkbWriter = std::make_shared<PkbConcreteWriter>(pkbWriterManager);

    std::shared_ptr<EntityExtractorVisitor> entityExtractor = std::make_shared<EntityExtractorVisitor>(pkbWriter);
    std::shared_ptr<FollowsExtractorVisitor> followsExtractor = std::make_shared<FollowsExtractorVisitor>(pkbWriter);
    std::shared_ptr<UsesExtractorVisitor> usesExtractor = std::make_shared<UsesExtractorVisitor>(pkbWriter);

    std::vector<std::shared_ptr<DesignExtractorVisitor>> visitors = { entityExtractor, followsExtractor, usesExtractor };

    //Traverse the AST from root node
    Traverser traverser = Traverser(visitors);
    traverser.traverse(rootNode);

    REQUIRE(*(procedureStore->getEntity(std::make_shared<Entity>(Procedure("doMath")))) == *(std::make_shared<Procedure>("doMath")));
    REQUIRE(*(variableStore->getEntity(std::make_shared<Entity>(Variable("x")))) == *(std::make_shared<Variable>("x")));
    REQUIRE(*(variableStore->getEntity(std::make_shared<Entity>(Variable("v")))) == *(std::make_shared<Variable>("v")));
    REQUIRE(*(variableStore->getEntity(std::make_shared<Entity>(Variable("y")))) == *(std::make_shared<Variable>("y")));
    REQUIRE(*(variableStore->getEntity(std::make_shared<Entity>(Variable("z")))) == *(std::make_shared<Variable>("z")));
    REQUIRE(*(variableStore->getEntity(std::make_shared<Entity>(Variable("t")))) == *(std::make_shared<Variable>("t")));
    REQUIRE(*(variableStore->getEntity(std::make_shared<Entity>(Variable("num1")))) == *(std::make_shared<Variable>("num1")));

    REQUIRE(*(statementStore->getEntity(std::make_shared<Entity>(Statement(1,StatementType::Assign)))) == *(std::make_shared<Statement>(1, StatementType::Assign)));
    REQUIRE(*(statementStore->getEntity(std::make_shared<Entity>(Statement(2, StatementType::Read)))) == *(std::make_shared<Statement>(2, StatementType::Read)));
    REQUIRE(*(statementStore->getEntity(std::make_shared<Entity>(Statement(3, StatementType::Print)))) == *(std::make_shared<Statement>(3, StatementType::Print)));

    REQUIRE(*(constantStore->getEntity(std::make_shared<Entity>(Constant(1)))) == *(std::make_shared<Constant>(1)));

    auto VarV = Variable("v");
    auto usesV = usesRelationshipManager->getVariableAssignment(VarV);
    REQUIRE(usesV.size() == 1);
    REQUIRE(usesV.at(0) == Statement(1, StatementType::Assign));

    auto VarY = Variable("y");
    auto usesY = usesRelationshipManager->getVariableAssignment(VarY);
    REQUIRE(usesY.size() == 1);
    REQUIRE(usesY.at(0) == Statement(1, StatementType::Assign));

    auto Stmt1 = Statement(1, StatementType::Assign);
    auto followsRS = followsRelationshipManager->getFollowingStatement(Stmt1);
    REQUIRE(followsRS.size() == 1);
    REQUIRE(followsRS.at(0) == Statement(2, StatementType::Read));

    auto Stmt2 = Statement(2, StatementType::Read);
    auto followsRS2 = followsRelationshipManager->getFollowingStatement(Stmt2);
    REQUIRE(followsRS2.size() == 1);
    REQUIRE(followsRS2.at(0) == Statement(3, StatementType::Print));

    //auto usesVarName = *(usesRelationshipManager->getVariableAssignment(std::make_shared<Variable>(varName)));
    //REQUIRE(usesVarName.size() == 1);
    ////REQUIRE(*(usesVarName.at(0)) == Statement(3, StatementType::Print));
}