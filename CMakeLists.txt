cmake_minimum_required(VERSION 3.16)
project(QUANTUM-CHESS)

set(CMAKE_CXX_STANDARD 14)

add_compile_options(-Wall -Wextra -pedantic -Werror)

# Wildcard
FILE(GLOB_RECURSE client_files "client/*.cpp")
FILE(GLOB_RECURSE server_files "server/*.cpp")
FILE(GLOB_RECURSE common_files "common/*.cpp")

FILE(GLOB_RECURSE common_header_files "common/*.h")
FILE(GLOB_RECURSE server_header_files "server/*.h" ${common_header_files})
FILE(GLOB_RECURSE client_header_files "client/*.h" ${common_header_files})
# message(STATUS "Sources loaded: ${server_files}")

# Directories
include_directories(.)
include_directories(./common)
include_directories(./client)
include_directories(./server)
include_directories(./tests)
include_directories(./tests/doctest)

# Executables
add_executable(TESTS
        tests/Tests.cpp tests/doctest/doctest.h ${common_files})

add_executable(CLIENT
        ${client_files} ${common_files})

add_executable(SERVER
        ${server_files} ${common_files})

# Libraries
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(CLIENT Threads::Threads)
target_link_libraries(SERVER Threads::Threads)

#Paths client
set (all_the_paths "")
foreach (_headerFile ${client_header_files})
    get_filename_component(_dir ${_headerFile} PATH)
    list (APPEND all_the_paths ${_dir})
endforeach()
list (REMOVE_DUPLICATES all_the_paths)
target_include_directories(CLIENT PRIVATE ${all_the_paths})

#Paths server
set (all_the_paths "")
foreach (_headerFile ${server_header_files})
    get_filename_component(_dir ${_headerFile} PATH)
    list (APPEND all_the_paths ${_dir})
endforeach()
list (REMOVE_DUPLICATES all_the_paths)
target_include_directories(SERVER PRIVATE ${all_the_paths})

#FOR WINDOWS
if (WIN32)
    target_link_libraries(CLIENT wsock32 ws2_32)
    target_link_libraries(SERVER wsock32 ws2_32)
    target_link_libraries(TESTS wsock32 ws2_32)
endif (WIN32)