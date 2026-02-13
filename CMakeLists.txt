cmake_minimum_required(VERSION 3.15)
project(RyntraProject)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_TOOLCHAIN_FILE "C:/vcpkg/vcpkg/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "vcpkg toolchain")
set(antlr4-runtime_DIR "C:/vcpkg/vcpkg/vcpkg/installed/x64-windows/share/antlr4-runtime")
set(ANTLR_SOURCE
    ANTLR/antlr-generated/antlr/RyntraBaseListener.cpp
    ANTLR/antlr-generated/antlr/RyntraBaseVisitor.cpp
    ANTLR/antlr-generated/antlr/RyntraLexer.cpp
    ANTLR/antlr-generated/antlr/RyntraParser.cpp
    ANTLR/antlr-generated/antlr/RyntraListener.cpp
    ANTLR/antlr-generated/antlr/RyntraVisitor.cpp
)

set(AST_SOURCE
    Compiler/AST/ASTNodes.cpp
    Compiler/AST/ASTBuilder.cpp
)

set(UTILITY_SOURCE
    Utility/ErrorHandler/ErrorHandler.cpp
)

find_package(antlr4-runtime REQUIRED)

add_executable(RyntraProject main.cpp ${ANTLR_SOURCE} ${AST_SOURCE} ${UTILITY_SOURCE})
target_link_libraries(RyntraProject PRIVATE antlr4_shared)
target_include_directories(RyntraProject PRIVATE ANTLR/antlr-generated Compiler/AST Utility)