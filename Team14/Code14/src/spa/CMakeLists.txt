file(GLOB srcs "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB headers "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp")
add_library(spa ${srcs} ${headers} "src/Commons/Statement.h" "src/Commons/Statement.cpp"  "src/Commons/Procedure.h" "src/Commons/Procedure.cpp" "src/Commons/Constant.h" "src/Commons/Constant.cpp" "src/Commons/Variable.h" "src/Commons/Variable.cpp")
# this makes the headers accessible for other projects which uses spa lib
target_include_directories(spa PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)


