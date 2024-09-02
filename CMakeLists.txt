cmake_minimum_required(VERSION 3.28)
project(Mathematics)

set(CMAKE_CXX_STANDARD 26)

add_library(Mathematics STATIC)
target_compile_options(Mathematics PUBLIC -fdeclspec)
target_sources(Mathematics PUBLIC FILE_SET CXX_MODULES FILES src/Mathematics.cxx)
