################ INITIAL ################
cmake_minimum_required(VERSION 3.16)
project(QUANTUM-CHESS)
set(CMAKE_CXX_STANDARD 14)
add_compile_options(-Wall -Wextra -pedantic -Werror)


################ WILDCARDS ################
file(GLOB_RECURSE client_files "client/*.cpp")
file(GLOB_RECURSE server_files "server/*.cpp")
file(GLOB_RECURSE common_files "common/*.cpp")
file(GLOB_RECURSE tests_files "tests/*.cpp")

file(GLOB_RECURSE common_header_files "common/*.h")
file(GLOB_RECURSE server_header_files "server/*.h" ${common_header_files})
file(GLOB_RECURSE client_header_files "client/*.h" ${common_header_files})


################ DIRECTORIES ################
include_directories(${PROJECT_SOURCE_DIR}/common)
include_directories(${PROJECT_SOURCE_DIR}/client)
include_directories(${PROJECT_SOURCE_DIR}/server)
include_directories(${PROJECT_SOURCE_DIR}/tests)
include_directories(${PROJECT_SOURCE_DIR}/tests/doctest)
include_directories(${PROJECT_SOURCE_DIR}/libs)
include_directories(${PROJECT_SOURCE_DIR}/libs/libSDL2pp)
include_directories(${PROJECT_SOURCE_DIR}/libs/libSDL2pp/SDL2pp)


################ EXECUTABLES ################
add_executable(TESTS
    ${tests_files} ${common_files})

add_executable(CLIENT
    ${client_files} ${common_files})

add_executable(SERVER
    ${server_files} ${common_files})


################ LIBRARIES ################
# Threads
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(CLIENT Threads::Threads)
target_link_libraries(SERVER Threads::Threads)

# SDL2pp
SET(SDL2PP_WITH_IMAGE ON)
SET(SDL2PP_WITH_MIXER ON)
SET(SDL2PP_WITH_TTF ON)
add_subdirectory(libs/libSDL2pp)
include_directories(${SDL2PP_INCLUDE_DIRS})
target_link_libraries(CLIENT ${SDL2PP_LIBRARIES})


################ PATHS ################
# Client
set(all_the_paths "")
foreach (_headerFile ${client_header_files})
    get_filename_component(_dir ${_headerFile} PATH)
    list(APPEND all_the_paths ${_dir})
endforeach ()
list(REMOVE_DUPLICATES all_the_paths)
target_include_directories(CLIENT PRIVATE ${all_the_paths})

# Server
set(all_the_paths "")
foreach (_headerFile ${server_header_files})
    get_filename_component(_dir ${_headerFile} PATH)
    list(APPEND all_the_paths ${_dir})
endforeach ()
list(REMOVE_DUPLICATES all_the_paths)
target_include_directories(SERVER PRIVATE ${all_the_paths})

# Tests
set(all_the_paths "")
foreach (_headerFile ${common_header_files})
    get_filename_component(_dir ${_headerFile} PATH)
    list(APPEND all_the_paths ${_dir})
endforeach ()
list(REMOVE_DUPLICATES all_the_paths)
target_include_directories(TESTS PRIVATE ${all_the_paths})


################ WINDOWS ################ DEPRECATED :(
#if (WIN32)
#    target_link_libraries(CLIENT wsock32 ws2_32)
#    target_link_libraries(SERVER wsock32 ws2_32)
#    target_link_libraries(TESTS wsock32 ws2_32)
#endif (WIN32)
