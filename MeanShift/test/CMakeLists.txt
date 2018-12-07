set(GTEST_SOURCE_DIR ./lib/googletest)

add_subdirectory(${GTEST_SOURCE_DIR})

include_directories(${GTEST_SOURCE_DIR} ${GTEST_SOURCE_DIR}/include)

add_executable(PointTest PointTest.cpp)
target_link_libraries(PointTest gtest gtest_main pointlib)

add_executable(ClusterTest ClusterTest.cpp)
target_link_libraries(ClusterTest gtest gtest_main clusterlib)

add_executable(ClustersBuilderTest ClustersBuilderTest.cpp)
target_link_libraries(ClustersBuilderTest gtest gtest_main clustersbuilderlib)

add_executable(csvUtilsTest csvUtilsTest.cpp)
target_link_libraries(csvUtilsTest gtest gtest_main csvutilslib)

add_executable(meanShiftTest meanShiftTest.cpp)
target_link_libraries(meanShiftTest gtest gtest_main meanshiftlib)

add_executable(runAllTests runAllTests.cpp PointTest.cpp ClusterTest.cpp ClustersBuilderTest.cpp
        csvUtilsTest.cpp meanShiftTest.cpp)
target_link_libraries(runAllTests gtest gtest_main pointlib clusterlib clustersbuilderlib
        csvutilslib meanshiftlib)