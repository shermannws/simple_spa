file(GLOB srcs "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB headers "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp")
add_executable(unit_testing ${srcs}

	"src/Commons/TestEntities.cpp"
	"src/PKB/Relationships/TestUsesRelationship.cpp"
	"src/PKB/RelationshipStorage/TestRelationshipStorage.cpp"
	"src/PKB/Relationships/TestFollowsRelationship.cpp"
	"src/PKB/EntityStorage/TestEntityStorage.cpp"
	"src/PKB/AssignmentStore/TestAssignmentPatternStorage.cpp"
	"src/PKB/TestPkb.cpp"
	"src/main.cpp"
	"src/TestAST.cpp"
	"src/SP/SPTokenizer/TestSPTokenizer.cpp"
	"src/SP/SPTokenizer/TestSPToken.cpp"
	"src/SP/SyntacticValidator/TestSyntacticValidator.cpp"
	"src/QPS/TestPQLParser.cpp"
	"src/QPS/TestQuery.cpp"
	"src/QPS/TestTokenizer.cpp"
	"src/QPS/TestToken.cpp"
	src/QPS/TestPQLEvaluator.cpp
	src/QPS/TestPQLEvaluator.cpp
	src/SP/AST/Nodes/TestASTNodes.cpp
	src/PKB/TestPkbReader.cpp
	src/PKB/Managers/TestUseRelationshipManager.cpp
	src/PKB/Managers/TestFollowsRelationshipManager.cpp
	src/SP/AST/TestSPParser.cpp
	src/PKB/TestPkbReader.cpp
	src/PKB/TestPkbReader.cpp
	src/QPS/TestToken.cpp
	src/PKB/TestPkbWriter.cpp
		src/IntegrationTesting/TestPkbQps.cpp)

target_link_libraries(unit_testing spa)

