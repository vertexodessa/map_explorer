
project(unittests)

include( CTest )

# Boost
find_package(Boost 
  COMPONENTS system filesystem log
  REQUIRED)
include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIR})
add_definitions(-DBOOST_LOG_DYN_LINK)


set(GTEST_MAP_FILE \"${CMAKE_SOURCE_DIR}/unittests/crafted_map.map\")
add_definitions(-DGTEST_MAP_FILE=${GTEST_MAP_FILE})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++14 -Wall -Wextra -g")
set(LIBRARY_NAME ${CMAKE_BINARY_DIR}/src/lib${LIB_NAME}.so)
set(GTEST_BINARY_NAME GTestMain)


add_test(AllTests ${GTEST_BINARY_NAME})

find_package(GTest REQUIRED)
include_directories(
  ${GTEST_INCLUDE_DIRS}
  ${CMAKE_SOURCE_DIR}/include/
  )

add_executable(${GTEST_BINARY_NAME}
  test_main.cc
  test_map.cc
  test_iterator.cc
  test_dijkstra_path_finder.cc
  )

target_link_libraries(${GTEST_BINARY_NAME}
  ${GTEST_BOTH_LIBRARIES}
  -pthread
  ${LIBRARY_NAME}
  ${Boost_LIBRARIES}
  )

add_custom_command(TARGET ${GTEST_BINARY_NAME}
  POST_BUILD COMMAND ./${GTEST_BINARY_NAME}
  )

add_dependencies(${GTEST_BINARY_NAME}
  ${LIB_NAME}
  )
