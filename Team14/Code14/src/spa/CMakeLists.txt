file(GLOB srcs "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB headers "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp")
add_library(spa ${srcs} ${headers}

    "src/Commons/Entities/Statement.h"
    "src/Commons/Entities/Statement.cpp" 
    "src/Commons/Entities/Procedure.h"
    "src/Commons/Entities/Procedure.cpp"
    "src/Commons/Entities/Constant.h"
    "src/Commons/Entities/Constant.cpp"
    "src/Commons/Entities/Variable.h"
    "src/Commons/Entities/Variable.cpp"
    "src/Commons/Entities/Entity.h"
    "src/Commons/Entities/Entity.cpp"
    "src/Commons/HashableKey.h"
    "src/Commons/Entities/WildCard.h"
    "src/Commons/Entities/WildCard.cpp"

    "src/PKB/Relationships/RelationshipType.h"
    "src/PKB/Relationships/Relationship.h"
    "src/PKB/Relationships/UsesRelationship.h"
    "src/PKB/Relationships/Relationship.cpp"
    "src/PKB/Relationships/UsesRelationship.cpp"
    "src/PKB/RelationshipStorage/RelationshipStorage.h"
    "src/PKB/RelationshipStorage/RelationshipStorage.cpp"
    "src/PKB/RelationshipStorage/UsesRelationshipStore.h"
    "src/PKB/RelationshipStorage/UsesRelationshipStore.cpp"
    "src/PKB/Relationships/FollowsRelationship.h"
    "src/PKB/Relationships/FollowsRelationship.cpp"
    "src/PKB/RelationshipStorage/FollowsRelationshipStore.h"
    "src/PKB/RelationshipStorage/FollowsRelationshipStore.cpp"
    "src/PKB/EntityStorage/EntityStorage.h"
    "src/PKB/EntityStorage/EntityStorage.cpp"
    "src/PKB/EntityStorage/ConstantStore.h"
    "src/PKB/EntityStorage/ConstantStore.cpp"
    "src/PKB/EntityStorage/ProcedureStore.h"
    "src/PKB/EntityStorage/ProcedureStore.cpp"
    "src/PKB/EntityStorage/StatementStore.h"
    "src/PKB/EntityStorage/StatementStore.cpp"
    "src/PKB/EntityStorage/VariableStore.h"
    "src/PKB/EntityStorage/VariableStore.cpp"
    "src/PKB/AssignmentPatternStore/Assignment.h"
    "src/PKB/AssignmentPatternStore/Assignment.cpp"
    "src/PKB/AssignmentPatternStore/AssignmentPatternStore.h"
    "src/PKB/AssignmentPatternStore/AssignmentPatternStore.cpp"
    "src/PKB/Managers/AssignmentManager.h"
    "src/PKB/Managers/AssignmentManager.cpp"
    "src/PKB/Pkb.h"
    "src/PKB/Pkb.cpp"
    "src/PKB/PkbReader.h"
    "src/PKB/PkbWriter.cpp"
    "src/PKB/PkbWriter.h"
    "src/PKB/PkbReader.cpp"
    src/SP/AST/Nodes/ASTNode.h
    src/SP/AST/Visitors/DesignExtractorVisitor.h
    src/SP/AST/Nodes/ProgramNode.h
    src/SP/AST/Nodes/ProcedureNode.h
    src/SP/AST/Nodes/StatementNode.h
    src/SP/AST/Nodes/StatementListNode.h
    src/SP/AST/Nodes/ReadNode.h
    src/SP/AST/Nodes/PrintNode.h
    src/SP/AST/Nodes/AssignNode.h
    src/SP/AST/Nodes/VariableNode.h
    src/SP/AST/Nodes/ExpressionNode.h
    src/SP/AST/Nodes/ConstantNode.h
    src/SP/AST/Nodes/ArithmeticExpressionNode.h
    src/SP/AST/Nodes/ArithmeticOperatorType.h
    src/SP/AST/Nodes/ConstantNode.cpp
    src/SP/AST/Nodes/VariableNode.cpp
    src/SP/AST/Nodes/ArithmeticExpressionNode.cpp
    src/SP/AST/Nodes/ReadNode.cpp
    src/SP/AST/Nodes/StatementNode.cpp
    src/SP/AST/Nodes/PrintNode.cpp
    src/SP/AST/Nodes/AssignNode.cpp
    src/SP/AST/Nodes/StatementListNode.cpp
    src/SP/AST/Nodes/ProcedureNode.cpp
    src/SP/AST/Nodes/ProgramNode.cpp
    src/SP/AST/Visitors/EntityExtractorVisitor.h
    src/SP/AST/Visitors/FollowsExtractorVisitor.h
    src/SP/AST/Visitors/UsesExtractorVisitor.h
    src/SP/AST/Visitors/EntityExtractorVisitor.cpp
    src/SP/AST/Visitors/FollowsExtractorVisitor.cpp
    src/SP/AST/Visitors/UsesExtractorVisitor.cpp
    src/QPS/Tokenizer.cpp
    src/QPS/Token.cpp
    src/QPS/Query.cpp
    src/QPS/PQLParser.cpp
    src/QPS/SuchThatClause.cpp
    src/QPS/Ref.cpp
    src/QPS/Result.cpp
    src/QPS/PQLEvaluator.cpp
    src/QPS/QueryEntity.cpp
    src/Commons/Entities/EntityType.h
    src/PKB/Managers/UsesRelationshipManager.h
    src/PKB/Managers/UsesRelationshipManager.cpp
    src/Commons/Entities/StatementType.h
    src/PKB/Managers/PkbReaderManager.h
    src/PKB/Managers/PkbReaderManager.cpp
    src/PKB/Managers/FollowsRelationshipManager.h
    src/PKB/Managers/FollowsRelationshipManager.cpp
    
    src/SP/SPTokenizer.cpp
    src/SP/SPTokenizer.h
    src/SP/SPToken.cpp
    src/SP/SPToken.h
    src/SP/SPTokenType.h)

# this makes the headers accessible for other projects which uses spa lib
target_include_directories(spa PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)


