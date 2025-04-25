set(RYNTRA_COMPILER_VERSION "0.1.0")

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(RyntraCompiler
    Lexer/Lexer.hpp
    Lexer/Token.hpp
    Lexer/Lexer.cpp
    Lexer/Token.cpp
    main.cpp
)

target_include_directories(RyntraCompiler
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${LLVM_INCLUDE_DIRS}
        ${CMAKE_SOURCE_DIR}/include
)

target_compile_definitions(RyntraCompiler
    PRIVATE
        ${LLVM_DEFINITIONS}
        RYNTRA_COMPILER_VERSION="${RYNTRA_COMPILER_VERSION}"
)

target_link_libraries(RyntraCompiler
    PRIVATE
        ${RYNTRA_LLVM_LIBS}
)

set_target_properties(RyntraCompiler PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)