cmake_minimum_required(VERSION 3.12)
project(MeanShift)

set(CMAKE_CXX_STANDARD 14)

add_library(pointlib Point.h Point.cpp)

add_library(clusterlib Cluster.h Cluster.cpp)
target_link_libraries(clusterlib pointlib)

add_library(clustersbuilderlib ClustersBuilder.h ClustersBuilder.cpp)
target_link_libraries(clustersbuilderlib clusterlib)

add_executable(meanshift main.cpp meanShift.h meanShift.cpp Point.h Point.cpp Cluster.h
        Cluster.cpp ClustersBuilder.cpp ClustersBuilder.h)

add_library(meanshiftlib meanShift.h meanShift.cpp Point.h Point.cpp Cluster.h Cluster.cpp
        ClustersBuilder.cpp ClustersBuilder.h)
#target_link_libraries(meanshift meanshiftlib)

add_subdirectory(test)