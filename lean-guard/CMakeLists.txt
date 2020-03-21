# What version of cmake.
cmake_minimum_required (VERSION 3.5)


# Project name.
set (PROJECT_NAME lean-guard)
PROJECT (PROJECT_NAME)


# Targets.
set (TARGET_LEAN_GUARD lean-guard)
set (TARGET_UNITTESTS unittests)


# Compiler and linker flags.
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g")
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
file (GLOB LEAN_GUARD_SRCS ${CMAKE_SOURCE_DIR}/src/*.cpp)


# Build lean-guard target.
set (PROJECT_LEAN_GUARD_SRCS ${LEAN_GUARD_SRCS} CACHE INTERNAL "list of source files for lean-guard")
message (STATUS "Guard Source Files: ${PROJECT_LEAN_GUARD_SRCS}")
add_executable (${TARGET_LEAN_GUARD} ${PROJECT_LEAN_GUARD_SRCS})
target_link_libraries (${TARGET_LEAN_GUARD} -lstdc++fs)





