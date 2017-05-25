cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++14 -Wall -Wextra -g")
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

# ncurses
find_package(PkgConfig)
pkg_check_modules(CURSES QUIET ncursesw)
include_directories(${CURSES_INCLUDE_DIRS})
link_directories(${CURSES_LIBRARY_DIRS})

# Boost
find_package(Boost
  COMPONENTS system filesystem log
  REQUIRED)
include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIR})

include_directories(
  .
  ${CMAKE_SOURCE_DIR}/include
  )

message("PROJECT_SOURCE_DIR: ${PROJECT_SOURCE_DIR}")

set(SRC_FILES
  Cell.cc
  ConsoleMapView.cc
  ConsolePathView.cc
  ConsoleViewBackend.cc
  DijkstraPathFinder.cc
  AStarPathFinder.cc
  Map.cc
  Path.cc
  Renderer.cc
  )

add_definitions(-DBOOST_LOG_DYN_LINK)
add_executable(${APP_NAME} main.cc)

add_library(${LIB_NAME} SHARED ${SRC_FILES})

message("Using Boost libs:   ${Boost_LIBRARIES}")
message("Using Curses libs:  ${CURSES_LIBRARIES}")

target_link_libraries(${LIB_NAME}
  pthread
  ${Boost_LIBRARIES}
  ${CURSES_LIBRARIES}
  )
target_link_libraries(${APP_NAME}
  ${LIB_NAME}
  )
