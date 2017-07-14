cmake_minimum_required(VERSION 2.6)

project(gca)

set(VTK_DIR /Users/dillon/Downloads/VTK-build/)

find_package(CGAL REQUIRED COMPONENTS Core)
include( ${CGAL_USE_FILE} )

find_package(VTK REQUIRED)
include(${VTK_USE_FILE})

SET(EXTRA_CXX_COMPILE_FLAGS "-std=c++11 -I./src -I./test -I/opt/local/include -O2 -Werror -Wall -pedantic")

SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${EXTRA_CXX_COMPILE_FLAGS}")

INCLUDE_DIRECTORIES(./include/dbhc)

SET(DBHC_HEADERS include/dbhc/algorithm.h
		 include/dbhc/check.h)

SET(TEST_FILES test/algorithm_tests.cpp)

add_executable(all-tests ${TEST_FILES} ${MANUFACTURE_TEST_FILES})

install(FILES ${DBHC_HEADERS} DESTINATION include/dbhc)
