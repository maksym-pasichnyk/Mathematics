cmake_minimum_required(VERSION 3.27)
project(Mathematics)

set(CMAKE_CXX_STANDARD 26)

add_library(Mathematics INTERFACE src/Mathematics.hpp)
target_compile_options(Mathematics INTERFACE -fdeclspec)
target_include_directories(Mathematics INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/src")
