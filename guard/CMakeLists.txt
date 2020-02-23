# What version of cmake.
cmake_minimum_required (VERSION 3.5)


# Project name.
set (PROJECT_NAME guard)
PROJECT (PROJECT_NAME)


# Targets.
set (TARGET_GUARD guard)
set (TARGET_UNITTESTS unittests)


# Compiler and linker flags.
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -DALL_LOGGING")
set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS}")


# Output folder where project will be created.
set (CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build/bin)
set (EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set (LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})


# Include directories.
include_directories (
   "${CMAKE_SOURCE_DIR}/src"
)


# Source code directories.
file (GLOB GUARD_SRCS ${CMAKE_SOURCE_DIR}/src/*.cpp)


# Build guard target.
set (PROJECT_GUARD_SRCS ${GUARD_SRCS} CACHE INTERNAL "list of source files for guard")
message (STATUS "Guard Source Files: ${PROJECT_GUARD_SRCS}")
add_executable (${TARGET_GUARD} ${PROJECT_GUARD_SRCS})
target_link_libraries (${TARGET_GUARD})


# Build CxxTest unit test support.
find_package (CxxTest)
if (CXXTEST_FOUND)

   # Pull in the cxxtext test framework files.
   include_directories ($(CXXTEST_INCLUDE_DIR))
   enable_testing ()

   # Get a list of unit test files.
   set (UNITTEST_DIR ${CMAKE_SOURCE_DIR}/test/unittest)
   file (GLOB UNITTEST_SRCS ${UNITTEST_DIR}/*.h)
   message (STATUS "Unittest files: ${UNITTEST_SRCS}")

   # Remove the main.cpp guard file for unit testing purposes.
   list (REMOVE_ITEM GUARD_SRCS ${CMAKE_SOURCE_DIR}/src/main.cpp)

   # Build the test runner.
   CXXTEST_ADD_TEST (${TARGET_UNITTESTS} runner.cpp ${UNITTEST_SRCS} ${GUARD_SRCS})
   target_link_libraries (${TARGET_UNITTESTS}) 

endif ()




