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
#include "SP/AST/Visitors/ModifiesExtractorVisitor.h"
#include "SP/AST/Visitors/ParentExtractorVisitor.h"
#include "SP/AST/Traverser/Traverser.h"
#include "PKB/Pkb.h"
#include "PKB/PkbConcreteWriter.h"
#include "ASTGenerator.h"

/*
Test the e2e addition through from SPTraverser to PKB stores
*/
TEST_CASE("Test AST Traverser - e2e for Follows and Uses") {
    SPParser parser;
    VariableName varName = "num1";
    std::vector<SPToken> tokens = {
            SPToken(TokenType::Name, "procedure"),
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
            SPToken(TokenType::CloseCurlyParenthesis, "}")
    };

    std::shared_ptr<ProgramNode> rootNode = parser.parse(tokens);

    auto assignmentManager = std::make_shared<AssignmentManager>(AssignmentManager());
    auto entitiesManager = std::make_shared<EntitiesManager>(EntitiesManager());
    auto followsRelationshipManager = std::make_shared<FollowsRelationshipManager>();
    auto usesRelationshipManager = std::make_shared<UsesRelationshipManager>();
    auto modifiesRelationshipManager = std::make_shared<ModifiesRelationshipManager>();
    auto parentRelationshipManager = std::make_shared<ParentRelationshipManager>();
    auto pkbWriterManager = std::make_shared<PkbWriterManager>(
            assignmentManager,
            entitiesManager,
            followsRelationshipManager,
            usesRelationshipManager,
            modifiesRelationshipManager,
            parentRelationshipManager
    );
    std::shared_ptr<PkbConcreteWriter> pkbWriter = std::make_shared<PkbConcreteWriter>(pkbWriterManager);

    std::shared_ptr<EntityExtractorVisitor> entityExtractor = std::make_shared<EntityExtractorVisitor>(pkbWriter);
    std::shared_ptr<FollowsExtractorVisitor> followsExtractor = std::make_shared<FollowsExtractorVisitor>(pkbWriter);
    std::shared_ptr<UsesExtractorVisitor> usesExtractor = std::make_shared<UsesExtractorVisitor>(pkbWriter);
    std::shared_ptr<ModifiesExtractorVisitor> modifiesExtractor = std::make_shared<ModifiesExtractorVisitor>(pkbWriter);

    std::vector<std::shared_ptr<DesignExtractorVisitor>> visitors = { entityExtractor, followsExtractor, usesExtractor, modifiesExtractor };

    //Traverse the AST from root node
    Traverser traverser = Traverser(visitors);
    traverser.traverse(rootNode);

    REQUIRE(*(entitiesManager->getProcedure(std::make_shared<Procedure>(Procedure("doMath")))) == *(std::make_shared<Procedure>("doMath")));
    REQUIRE(*(entitiesManager->getVariable(std::make_shared<Variable>(Variable("x")))) == *(std::make_shared<Variable>("x")));
    REQUIRE(*(entitiesManager->getVariable(std::make_shared<Variable>(Variable("v")))) == *(std::make_shared<Variable>("v")));
    REQUIRE(*(entitiesManager->getVariable(std::make_shared<Variable>(Variable("y")))) == *(std::make_shared<Variable>("y")));
    REQUIRE(*(entitiesManager->getVariable(std::make_shared<Variable>(Variable("z")))) == *(std::make_shared<Variable>("z")));
    REQUIRE(*(entitiesManager->getVariable(std::make_shared<Variable>(Variable("t")))) == *(std::make_shared<Variable>("t")));
    REQUIRE(*(entitiesManager->getVariable(std::make_shared<Variable>(Variable("num1")))) == *(std::make_shared<Variable>("num1")));

    REQUIRE(*(entitiesManager->getStatement(std::make_shared<Statement>(Statement(1,StatementType::Assign)))) == *(std::make_shared<Statement>(1, StatementType::Assign)));
    REQUIRE(*(entitiesManager->getStatement(std::make_shared<Statement>(Statement(2, StatementType::Read)))) == *(std::make_shared<Statement>(2, StatementType::Read)));
    REQUIRE(*(entitiesManager->getStatement(std::make_shared<Statement>(Statement(3, StatementType::Print)))) == *(std::make_shared<Statement>(3, StatementType::Print)));

    REQUIRE(*(entitiesManager->getConstant(std::make_shared<Constant>(Constant("1")))) == *(std::make_shared<Constant>("1")));

    auto VarV = Variable("v");
    auto usesV = usesRelationshipManager->getUsesTypeIdent(StatementType::Assign, VarV);
    REQUIRE(usesV.size() == 1);
    REQUIRE(usesV.at(0) == Statement(1, StatementType::Assign));

    auto VarY = Variable("y");
    auto usesY = usesRelationshipManager->getUsesTypeIdent(StatementType::Assign, VarY);
    REQUIRE(usesY.size() == 1);
    REQUIRE(usesY.at(0) == Statement(1, StatementType::Assign));

    auto Stmt1 = Statement(1, StatementType::Assign);
    auto followsRS = followsRelationshipManager->getFollowsStmtType(Stmt1, StatementType::Stmt, true);
    REQUIRE(followsRS.size() == 1);
    REQUIRE(followsRS.at(0) == Statement(2, StatementType::Read));

    auto Stmt2 = Statement(2, StatementType::Read);
    auto followsRS2 = followsRelationshipManager->getFollowsStmtType(Stmt2, StatementType::Stmt, true);
    REQUIRE(followsRS2.size() == 1);
    REQUIRE(followsRS2.at(0) == Statement(3, StatementType::Print));
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

    auto assignmentManager = std::make_shared<AssignmentManager>(AssignmentManager());
    auto entitiesStore = std::make_shared<EntitiesManager>(EntitiesManager());
    auto followsRelationshipManager = std::make_shared<FollowsRelationshipManager>();
    auto usesRelationshipManager = std::make_shared<UsesRelationshipManager>();
    auto modifiesRelationshipManager = std::make_shared<ModifiesRelationshipManager>();
    auto parentRelationshipManager = std::make_shared<ParentRelationshipManager>();
    auto pkbWriterManager = std::make_shared<PkbWriterManager>(
        assignmentManager,
        entitiesStore,
        followsRelationshipManager,
        usesRelationshipManager,
        modifiesRelationshipManager,
        parentRelationshipManager
    );
    std::shared_ptr<PkbConcreteWriter> pkbWriter = std::make_shared<PkbConcreteWriter>(pkbWriterManager);

    std::shared_ptr<EntityExtractorVisitor> entityExtractor = std::make_shared<EntityExtractorVisitor>(pkbWriter);
    std::shared_ptr<FollowsExtractorVisitor> followsExtractor = std::make_shared<FollowsExtractorVisitor>(pkbWriter);
    std::shared_ptr<UsesExtractorVisitor> usesExtractor = std::make_shared<UsesExtractorVisitor>(pkbWriter);
    std::shared_ptr<ModifiesExtractorVisitor> modifiesExtractor = std::make_shared<ModifiesExtractorVisitor>(pkbWriter);
    std::shared_ptr<ParentExtractorVisitor> parentExtractor = std::make_shared<ParentExtractorVisitor>(pkbWriter);

    std::vector<std::shared_ptr<DesignExtractorVisitor>> visitors = { entityExtractor, followsExtractor, usesExtractor, modifiesExtractor, parentExtractor };

    //Traverse the AST from root node
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
    REQUIRE(*(entitiesStore->getProcedure(std::make_shared<Procedure>(Procedure("kk")))) == *(std::make_shared<Procedure>("kk")));
    
    // Check Follows
    auto follows1 = followsRelationshipManager->getFollowsStmtType(stmt1, StatementType::Stmt, true);
    REQUIRE(follows1.size() == 1);
    REQUIRE(follows1.at(0) == stmt9);
    auto follows3 = followsRelationshipManager->getFollowsStmtType(stmt3, StatementType::Stmt, true);
    REQUIRE(follows3.size() == 1);
    REQUIRE(follows3.at(0) == Statement(4, StatementType::Assign));

    
    // Check Follows*
    auto follows1star = followsRelationshipManager->getFollowsStmtType(stmt1, StatementType::Stmt, false);
    REQUIRE(follows1star.size() == 2);
    REQUIRE(std::find(follows1star.begin(), follows1star.end(), stmt9) != follows1star.end());
    REQUIRE(std::find(follows1star.begin(), follows1star.end(), stmt10) != follows1star.end());
    
    // Check Uses exhaustively
    REQUIRE(usesRelationshipManager->getUsesStmtPair(StatementType::Stmt).size() == 17);
    REQUIRE(usesRelationshipManager->isStmtUsesVar(stmt1, varA));
    REQUIRE(usesRelationshipManager->isStmtUsesVar(stmt1, varB));
    REQUIRE(usesRelationshipManager->isStmtUsesVar(stmt1, varC));
    REQUIRE(usesRelationshipManager->isStmtUsesVar(stmt1, varD));
    REQUIRE(usesRelationshipManager->isStmtUsesVar(stmt1, varF));
    REQUIRE(usesRelationshipManager->isStmtUsesVar(stmt1, varI));
    REQUIRE(usesRelationshipManager->isStmtUsesVar(stmt1, varJ));
    REQUIRE(usesRelationshipManager->isStmtUsesVar(stmt1, varK));
    REQUIRE(usesRelationshipManager->isStmtUsesVar(stmt1, varC));
    REQUIRE(usesRelationshipManager->isStmtUsesVar(stmt1, varD));
    REQUIRE(usesRelationshipManager->isStmtUsesVar(stmt1, varF));
    REQUIRE(usesRelationshipManager->isStmtUsesVar(stmt3, varF));
    REQUIRE(usesRelationshipManager->isStmtUsesVar(stmt6, varI));
    REQUIRE(usesRelationshipManager->isStmtUsesVar(stmt7, varJ));
    REQUIRE(usesRelationshipManager->isStmtUsesVar(stmt7, varK));
    REQUIRE(usesRelationshipManager->isStmtUsesVar(stmt10, varX));
    REQUIRE(usesRelationshipManager->isStmtUsesVar(stmt10, varC));
    
    REQUIRE(!usesRelationshipManager->isStmtUsesVar(stmt5, varH));
    REQUIRE(!usesRelationshipManager->isStmtUsesVar(stmt8, varA));
    REQUIRE(!usesRelationshipManager->isStmtUsesVar(stmt10, varM));

    
    // Check Modifies
    REQUIRE(modifiesRelationshipManager->isStmtModifiesVar(stmt1, varE));
    REQUIRE(modifiesRelationshipManager->isStmtModifiesVar(stmt1, varG));
    REQUIRE(modifiesRelationshipManager->isStmtModifiesVar(stmt1, varH));
    REQUIRE(modifiesRelationshipManager->isStmtModifiesVar(stmt1, varA));

    REQUIRE(modifiesRelationshipManager->isStmtModifiesVar(stmt2, varE));
    REQUIRE(modifiesRelationshipManager->isStmtModifiesVar(stmt2, varG));
    REQUIRE(modifiesRelationshipManager->isStmtModifiesVar(stmt2, varH));

    REQUIRE(modifiesRelationshipManager->isStmtModifiesVar(stmt3, varE));
    REQUIRE(modifiesRelationshipManager->isStmtModifiesVar(stmt4, varG));
    REQUIRE(modifiesRelationshipManager->isStmtModifiesVar(stmt5, varH));

    REQUIRE(modifiesRelationshipManager->isStmtModifiesVar(stmt7, varA));
    REQUIRE(modifiesRelationshipManager->isStmtModifiesVar(stmt8, varA));

    REQUIRE(modifiesRelationshipManager->isStmtModifiesVar(stmt9, varJ));
    REQUIRE(modifiesRelationshipManager->isStmtModifiesVar(stmt10, varM));

    REQUIRE(!modifiesRelationshipManager->isStmtModifiesVar(stmt1, varB));
    REQUIRE(!modifiesRelationshipManager->isStmtModifiesVar(stmt10, varX));
 
    // Check Parent
    REQUIRE(parentRelationshipManager->isParent(stmt1, stmt2, true));
    REQUIRE(parentRelationshipManager->isParent(stmt1, stmt6, true));
    REQUIRE(parentRelationshipManager->isParent(stmt1, stmt7, true));
    REQUIRE(parentRelationshipManager->isParent(stmt2, stmt3, true));
    REQUIRE(parentRelationshipManager->isParent(stmt2, stmt4, true));
    REQUIRE(parentRelationshipManager->isParent(stmt2, stmt5, true));
    REQUIRE(parentRelationshipManager->isParent(stmt7, stmt8, true));

    // Check Parent*
    REQUIRE(parentRelationshipManager->isParent(stmt1, stmt3, false));
    REQUIRE(parentRelationshipManager->isParent(stmt1, stmt4, false));
    REQUIRE(parentRelationshipManager->isParent(stmt1, stmt5, false));
    REQUIRE(parentRelationshipManager->isParent(stmt1, stmt8, false));
}