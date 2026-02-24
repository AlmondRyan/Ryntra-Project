cmake_minimum_required(VERSION 3.15)
project(RyntraProject)

find_package(Python3 REQUIRED COMPONENTS Interpreter)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_TOOLCHAIN_FILE "C:/vcpkg/vcpkg/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "vcpkg toolchain")
set(antlr4-runtime_DIR "C:/vcpkg/vcpkg/vcpkg/installed/x64-windows/share/antlr4-runtime")

set(GEN_SCRIPT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Scripts/GenAllNodesVisitor")
set(GEN_SCRIPT "${GEN_SCRIPT_DIR}/GenAllNodesVisitor.py")
set(GENERATED_HEADER "${CMAKE_CURRENT_SOURCE_DIR}/Compiler/GeneratedHeader/AllNodesVisitor.h")
file(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/Compiler/GeneratedHeader")

add_custom_command(
        OUTPUT ${GENERATED_HEADER}
        COMMAND ${Python3_EXECUTABLE} ${GEN_SCRIPT} ${GENERATED_HEADER}
        WORKING_DIRECTORY ${GEN_SCRIPT_DIR}
        DEPENDS ${GEN_SCRIPT}
        COMMENT "Generating AllNodesVisitor.h from GenAllNodesVisitor.py"
        VERBATIM
)

add_custom_target(GenerateAllNodesVisitor ALL DEPENDS ${GENERATED_HEADER})

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
        ${GENERATED_HEADER}
)

set(UTILITY_SOURCE
        Utility/ErrorHandler/ErrorHandler.cpp
)

set(SEMANTIC_SOURCE
        Compiler/Semantic/SymbolTable.cpp
        Compiler/Semantic/SemanticAnalyzer.cpp
)

set(IR_SOURCE
        Compiler/IR/BasicBlock.cpp
        Compiler/IR/BasicBlock.h
        Compiler/IR/Constant.cpp
        Compiler/IR/Constant.h
        Compiler/IR/Function.cpp
        Compiler/IR/Function.h
        Compiler/IR/HLIRBuilder.cpp
        Compiler/IR/HLIRBuilder.h
        Compiler/IR/Instruction.h
        Compiler/IR/Instruction.cpp
        Compiler/IR/IRBuilder.cpp
        Compiler/IR/IRBuilder.h
        Compiler/IR/Module.cpp
        Compiler/IR/Module.h
        Compiler/IR/Type.cpp
        Compiler/IR/Type.h
        Compiler/IR/Value.h
        Compiler/IR/Value.cpp
)

find_package(antlr4-runtime REQUIRED)

add_executable(RyntraProject
        main.cpp
        ${ANTLR_SOURCE}
        ${AST_SOURCE}
        ${UTILITY_SOURCE}
        ${SEMANTIC_SOURCE}
        ${IR_SOURCE}
)

add_dependencies(RyntraProject GenerateAllNodesVisitor)

target_link_libraries(RyntraProject PRIVATE antlr4_shared)
target_include_directories(RyntraProject PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/ANTLR/antlr-generated
        ${CMAKE_CURRENT_SOURCE_DIR}/Compiler/
        ${CMAKE_CURRENT_SOURCE_DIR}/Utility
        ${CMAKE_CURRENT_SOURCE_DIR}/Compiler/
        ${CMAKE_CURRENT_SOURCE_DIR}/
        ${CMAKE_CURRENT_BINARY_DIR} #< Avoid pollute the source tree
)