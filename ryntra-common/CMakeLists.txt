add_library(RyntraCommon STATIC
        include/defs/ryntra_exceptions.h)

target_sources(RyntraCommon
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src/utils/ApplicationArgsManager/ApplicationArgsManager.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/utils/ConsoleTextColorManager/ConsoleTextColorManager.cpp
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include/defs/ryntra_defs.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/utils/ApplicationArgsManager/ApplicationArgsManager.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/include/utils/ConsoleTextColorManager/ConsoleTextColorManager.hpp
)

target_include_directories(RyntraCommon
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

set_target_properties(RyntraCommon PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)