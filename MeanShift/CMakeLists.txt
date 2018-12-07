cmake_minimum_required(VERSION 3.10)
project(MeanShift)

set(CMAKE_CXX_STANDARD 14)

add_library(pointlib Point.cpp)

add_library(clusterlib Cluster.cpp)
target_link_libraries(clusterlib pointlib)

add_library(clustersbuilderlib ClustersBuilder.cpp)
target_link_libraries(clustersbuilderlib pointlib clusterlib)

add_library(csvutilslib csvUtils.cpp)
target_link_libraries(csvutilslib pointlib clusterlib)

add_library(meanshiftlib meanShift.cpp)
target_link_libraries(meanshiftlib clustersbuilderlib pointlib clusterlib)

add_executable(meanshift main.cpp)
target_link_libraries(meanshift meanshiftlib csvutilslib)

add_subdirectory(test)