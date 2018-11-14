set(GTEST_SOURCE_DIR ./lib/googletest)

add_subdirectory(${GTEST_SOURCE_DIR})

include_directories(${GTEST_SOURCE_DIR} ${GTEST_SOURCE_DIR}/include)

add_executable(meanShiftTest meanShiftTest.cpp)
target_link_libraries(meanShiftTest gtest gtest_main meanshiftlib)