file(GLOB srcs "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB headers "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp")
add_library(spa ${srcs} ${headers}
        src/SP/SPTokenizer.cpp
        src/SP/SPTokenizer.h
        src/SP/SPToken.cpp
        src/SP/SPToken.h
        src/SP/SPTokenType.h
        src/SP/AST/Nodes/ASTNode.h
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
        src/SP/AST/Visitors/DesignExtractorVisitor.h
        src/SP/AST/Visitors/EntityExtractorVisitor.h
        src/SP/AST/Visitors/FollowsExtractorVisitor.h
        src/SP/AST/Visitors/UsesExtractorVisitor.h
        src/SP/AST/Visitors/EntityExtractorVisitor.cpp
        src/SP/AST/Visitors/FollowsExtractorVisitor.cpp
        src/SP/AST/Visitors/UsesExtractorVisitor.cpp
        src/SP/SPParser.h
        src/SP/SPParser.cpp
)
# this makes the headers accessible for other projects which uses spa lib
target_include_directories(spa PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)


