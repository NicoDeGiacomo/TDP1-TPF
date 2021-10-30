cmake_minimum_required(VERSION 3.16)
project(QUANTUM-CHESS)

set(CMAKE_CXX_STANDARD 14)

# Wildcard
FILE(GLOB_RECURSE main_files "client/*.cpp" "server/*.cpp" "common/*.cpp")
message(STATUS "Sources loaded: ${main_files}")

# Directories
include_directories(.)
include_directories(./common)
include_directories(./client)
include_directories(./server)
include_directories(./tests)
include_directories(./tests/doctest)

# Executables
add_executable(TESTS
        tests/Tests.cpp tests/doctest/doctest.h ${main_files})

add_executable(CLIENT
        ${main_files})

add_executable(SERVER
        ${main_files})

# Libraries
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(CLIENT Threads::Threads)
target_link_libraries(SERVER Threads::Threads)