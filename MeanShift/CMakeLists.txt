cmake_minimum_required(VERSION 3.10)
project(MeanShift)

set(CMAKE_CXX_STANDARD 14)

add_library(pointlib Point.cpp)

add_library(clusterlib Cluster.cpp)
target_link_libraries(clusterlib pointlib)

add_library(clustersbuilderlib ClustersBuilder.cpp)
target_link_libraries(clustersbuilderlib pointlib clusterlib)

add_library(meanshiftlib meanShift.cpp)
target_link_libraries(meanshiftlib clustersbuilderlib pointlib clusterlib)

add_executable(meanshift main.cpp)
target_link_libraries(meanshift meanshiftlib)

add_executable(batchtest batchTest.cpp)
target_link_libraries(batchtest meanshiftlib)

add_subdirectory(test)