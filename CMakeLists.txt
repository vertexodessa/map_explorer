cmake_minimum_required(VERSION 3.0)

set(SRC_DIR src)
set(TESTS_DIR unittests)

project(MapSolver)

set(APP_NAME "${PROJECT_NAME}Bin")
set(LIB_NAME "${PROJECT_NAME}Lib")

add_subdirectory(${SRC_DIR})
add_subdirectory(${TESTS_DIR})

