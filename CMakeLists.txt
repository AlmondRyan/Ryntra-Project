cmake_minimum_required(VERSION 3.31)
project(RyntraProject LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_TOOLCHAIN_FILE "C:/vcpkg/vcpkg/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "vcpkg toolchain")
set(antlr4-runtime_DIR "C:/vcpkg/vcpkg/vcpkg/installed/x64-windows/share/antlr4-runtime")
set(LLVM_DIR "C:/LLVM/lib/cmake/llvm")
set(ANTLR_SOURCES
        ANTLR/antlr-generated/antlr/RyntraBaseListener.cpp
        ANTLR/antlr-generated/antlr/RyntraBaseVisitor.cpp
        ANTLR/antlr-generated/antlr/RyntraLexer.cpp
        ANTLR/antlr-generated/antlr/RyntraListener.cpp
        ANTLR/antlr-generated/antlr/RyntraParser.cpp
        ANTLR/antlr-generated/antlr/RyntraVisitor.cpp
        Compiler/IRGenerator/IRGenerator.cpp
)

find_package(antlr4-runtime REQUIRED)
find_package(LLVM CONFIG REQUIRED)

add_subdirectory(Compiler/RyntraCRT)
message(STATUS "Found LLVM Library: ${LLVM_PACKAGE_VERSION}")

include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

if (MSVC)
    add_compile_options("/utf-8")
endif ()

add_executable(RyntraProject
        main.cpp
        ${ANTLR_SOURCES}
        Compiler/AST/ASTBuilder.cpp
        Compiler/Semantic/SemanticAnalyzer.cpp
        Utility/ErrorHandler/ErrorHandler.cpp
        Compiler/AST/ASTNodes.cpp
)

llvm_map_components_to_libnames(LLVM_LIBS
        core
        support
        irreader
)

target_link_libraries(RyntraProject PRIVATE antlr4_shared ${LLVM_LIBS})
target_include_directories(RyntraProject PRIVATE Compiler ANTLR/antlr-generated Utility)