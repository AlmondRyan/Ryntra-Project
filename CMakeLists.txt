cmake_minimum_required(VERSION 3.20)
project(RyntraProject)

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
    message(FATAL_ERROR "[Error]: Build in the root of Ryntra Project Source Tree is not allowed. "
    "CMake would overwrite the make scripts with Ryntra Project. "
    "The best to do is create a `build` folder, then change to `build` folder in command prompt. "
    "And pass the source directory by `cmake build` in the last argument. "
    "The process that you did earlier will generate a `CMakeCache.txt` and the directory `CMakeFiles`. "
    "Please delete them before execute `cmake build`.")
endif()

add_subdirectory(rld)
add_subdirectory(rasm)