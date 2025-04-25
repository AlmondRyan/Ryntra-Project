cmake_minimum_required(VERSION 3.20)
project(RyntraProject)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(RYNTRA_SUPPORT_PROJECTS "ryntra-common" "rylink" "ryntra-compiler" "ryntra-optimizer" "rive" "rikamo" "rynd")
set(RYNTRA_ENABLE_BUILD_PROJECTS "" CACHE STRING "List of projects you want to build, separated by semicolon (e.g. rylink;rive). Use 'all' to build all the projects.")

set(LLVM_DIR "E:/llvm-toolchain-install/lib/cmake/llvm" CACHE PATH "LLVM installation directory")
message(STATUS "Looking for LLVM in: ${LLVM_DIR}")

find_package(LLVM REQUIRED CONFIG)
message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "LLVM Include dirs: ${LLVM_INCLUDE_DIRS}")

set(RYNTRA_LLVM_COMPONENTS
    core
    support
    irreader
    passes
    analysis
    transformutils
    scalaropts
)

llvm_map_components_to_libnames(RYNTRA_LLVM_LIBS ${RYNTRA_LLVM_COMPONENTS})
message(STATUS "Using LLVM libraries: ${RYNTRA_LLVM_LIBS}")

add_subdirectory(ryntra-common)
add_subdirectory(ryntra-compiler)

if (RYNTRA_ENABLE_BUILD_PROJECTS STREQUAL "all")
    foreach(project IN LISTS RYNTRA_SUPPORT_PROJECTS)
        if(NOT project STREQUAL "ryntra-compiler")
            add_subdirectory(${project})
        endif()
    endforeach()
else()
    if(NOT "${RYNTRA_ENABLE_BUILD_PROJECTS}" STREQUAL "")
        foreach(project IN LISTS RYNTRA_ENABLE_BUILD_PROJECTS)
            if(NOT project STREQUAL "ryntra-compiler" AND EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${project}")
                message(STATUS "Enable Building: ${project}")
                add_subdirectory(${project})
            endif()
        endforeach()
    endif()
endif()