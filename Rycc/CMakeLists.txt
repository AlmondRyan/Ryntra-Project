find_package(LLVM REQUIRED CONFIG)

# 明确指定需要的LLVM组件
llvm_map_components_to_libnames(subproject_llvm_libs
        core support irreader
)

add_executable(
        RyntraCompiler
        Lexer/Lexer.hpp
        Lexer/Token.hpp
        Lexer/Lexer.cpp
        Lexer/Token.cpp
        main.cpp
)

target_include_directories(RyntraCompiler PRIVATE ${LLVM_INCLUDE_DIRS})
target_compile_definitions(RyntraCompiler PRIVATE ${LLVM_DEFINITIONS})
target_link_libraries(RyntraCompiler PRIVATE ${subproject_llvm_libs})