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
 "src/PKB/EntityStorage/AssignmentStatementStore.h"
 "src/PKB/EntityStorage/AssignmentStatementStore.cpp"
        src/QPS/Tokenizer.cpp
        src/QPS/Token.cpp
        src/QPS/Entity.cpp
        src/QPS/Query.cpp
        src/QPS/PQLParser.cpp)
# this makes the headers accessible for other projects which uses spa lib
target_include_directories(spa PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)


