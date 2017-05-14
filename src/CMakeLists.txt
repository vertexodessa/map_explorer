cmake_minimum_required(VERSION 3.0)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++14 -Wall -g")
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

# Boost
find_package(Boost 
  COMPONENTS system filesystem log
  REQUIRED)
include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIR})

include_directories(
  .
  ../include
  )

message("PROJECT_SOURCE_DIR: ${PROJECT_SOURCE_DIR}")
# add_subdirectory(protocol)
# add_subdirectory(core)
# add_subdirectory(builder)
# add_subdirectory(common)
# add_subdirectory(executor)

# set(obj_libs $<TARGET_OBJECTS:obj_protocol_lib>
#              $<TARGET_OBJECTS:obj_core_lib>
#              $<TARGET_OBJECTS:obj_builder_lib>
#              $<TARGET_OBJECTS:obj_common_lib>
#              $<TARGET_OBJECTS:obj_executor_lib>)

#add_library(${PROJECT_NAME}_LIB ${obj_libs})
#add_library(${PROJECT_NAME}_LIB ${obj_libs})

set(SRC_FILES
  Cell.cc
  Compositor.cc
  ConsoleCellView.cc
  ConsoleMapView.cc
  ConsoleMapViewConfiguration.cc
  ConsolePathView.cc
  DijkstraPathFinder.cc
  Map.cc
  Path.cc
  )

add_definitions(-DBOOST_LOG_DYN_LINK)
add_executable(${PROJECT_NAME} main.cc ${SRC_FILES})

message("Using Boost libs:   ${Boost_LIBRARIES}")

target_link_libraries(${PROJECT_NAME}
  pthread
  ${Boost_LIBRARIES}
  )
