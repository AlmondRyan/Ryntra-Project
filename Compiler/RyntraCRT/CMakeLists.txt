cmake_minimum_required(VERSION 3.31)
project(RyntraCRT C)

add_library(RyntraCRT STATIC src/ToString.c
        include/ToString.h)

target_include_directories(RyntraCRT PUBLIC include/)
target_compile_features(RyntraCRT PUBLIC c_std_11)