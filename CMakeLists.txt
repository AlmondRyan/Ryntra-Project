cmake_minimum_required(VERSION 3.20)
project(RyntraProject)

set(CMAKE_CXX_STANDARD 20)

message(STATUS "[Ryntra Project]: WARNING: This project uses LLVM Project that I \"Almond Ryan\" built on my computer."
        "So if you want to build Ryntra Project on your computer, you must make sure you have an built"
        "version of LLVM project on your computer, and change LLVM_DIR variable that pointed to your LLVM Build."
)

set(LLVM_DIR "E:/llvm-toolchain-install/lib/cmake/llvm")
message(STATUS "Looking for LLVM in: ${LLVM_DIR}")

find_package(LLVM REQUIRED CONFIG)
message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "LLVM Include dirs: ${LLVM_INCLUDE_DIRS}")

# 明确指定需要的LLVM组件
llvm_map_components_to_libnames(llvm_libs
        core support irreader passes analysis transformutils scalaropts
)
message(STATUS "Using LLVM libraries: ${llvm_libs}")

#add_executable(RyntraProject tst.cpp)

#target_include_directories(RyntraProject PRIVATE ${LLVM_INCLUDE_DIRS})
#target_compile_definitions(RyntraProject PRIVATE ${LLVM_DEFINITIONS})

add_subdirectory(Rycc/)

#target_link_libraries(RyntraProject PRIVATE ${llvm_libs})