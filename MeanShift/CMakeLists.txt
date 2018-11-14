cmake_minimum_required(VERSION 3.12)
project(MeanShift)

set(CMAKE_CXX_STANDARD 14)

add_executable(meanshift main.cpp meanShift.h meanShift.cpp)

add_library(meanshiftlib meanShift.h meanShift.cpp)
set_target_properties(meanshiftlib PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(meanshift meanshiftlib)

add_subdirectory(test)