cmake_minimum_required(VERSION 3.12)
project(MeanShift)

set(CMAKE_CXX_STANDARD 14)

add_executable(meanshift main.cpp meanShift.h)

add_library(meanshiftlib meanShift.h)
set_target_properties(meanshiftlib PROPERTIES LINKER_LANGUAGE CXX)

add_subdirectory(test)