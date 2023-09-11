#include <vector>

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
#
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
            SPToken(TokenType::NAME, "x"),
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
    std::shared_ptr<PkbWriter> pkbWriter = std::make_shared<PkbWriter>(pkbWriterManager);

    std::shared_ptr<EntityExtractorVisitor> entityExtractor = std::make_shared<EntityExtractorVisitor>(pkbWriter);
    std::shared_ptr<FollowsExtractorVisitor> followsExtractor = std::make_shared<FollowsExtractorVisitor>(pkbWriter);
    std::shared_ptr<UsesExtractorVisitor> usesExtractor = std::make_shared<UsesExtractorVisitor>(pkbWriter);

    std::vector<std::shared_ptr<DesignExtractorVisitor>> visitors = { entityExtractor, followsExtractor, usesExtractor };

    //Traverse the AST from root node
    Traverser traverser = Traverser(visitors);
    //traverser.traverse(rootNode);

    //REQUIRE(procedureStore->getEntity(std::make_shared<Procedure>("procedure")) == std::make_shared<Procedure>("procedure"));
    
}