cmake_minimum_required(VERSION 3.16)
project(QUANTUM-CHESS)

set(CMAKE_CXX_STANDARD 14)

add_compile_options(-Wall -Wextra -pedantic -Werror)

# Agrego la libreria SDL2pp habilitando manejo de imagenes y de letras
SET(SDL2PP_WITH_IMAGE ON) # if you need SDL_image support
SET(SDL2PP_WITH_MIXER ON) # if you need SDL_mixer support
SET(SDL2PP_WITH_TTF ON) # if you need SDL_ttf support
ADD_SUBDIRECTORY(libs/libSDL2pp)

# Agrego la carpeta con los headers autogenerados a los includes
message("Agregando '${PROJECT_SOURCE_DIR}/libs' como directorio de includes")
include_directories(${PROJECT_SOURCE_DIR}/libs)
include_directories(${SDL2PP_INCLUDE_DIRS})

# Wildcard
FILE(GLOB_RECURSE client_files "client/*.cpp")
FILE(GLOB_RECURSE server_files "server/*.cpp")
FILE(GLOB_RECURSE common_files "common/*.cpp")
FILE(GLOB_RECURSE tests_files "tests/*.cpp")

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
    ${tests_files} ${common_files})

add_executable(CLIENT
    ${client_files} ${common_files})

add_executable(SERVER
    ${server_files} ${common_files})

# Libraries
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(CLIENT Threads::Threads ${SDL2PP_LIBRARIES})
target_link_libraries(SERVER Threads::Threads ${SDL2PP_LIBRARIES})

# Paths client
set(all_the_paths "")
foreach (_headerFile ${client_header_files})
    get_filename_component(_dir ${_headerFile} PATH)
    list(APPEND all_the_paths ${_dir})
endforeach ()
list(REMOVE_DUPLICATES all_the_paths)
target_include_directories(CLIENT PRIVATE ${all_the_paths})

# Paths server
set(all_the_paths "")
foreach (_headerFile ${server_header_files})
    get_filename_component(_dir ${_headerFile} PATH)
    list(APPEND all_the_paths ${_dir})
endforeach ()
list(REMOVE_DUPLICATES all_the_paths)
target_include_directories(SERVER PRIVATE ${all_the_paths})

# Paths tests
set(all_the_paths "")
foreach (_headerFile ${common_header_files})
    get_filename_component(_dir ${_headerFile} PATH)
    list(APPEND all_the_paths ${_dir})
endforeach ()
list(REMOVE_DUPLICATES all_the_paths)
target_include_directories(TESTS PRIVATE ${all_the_paths})

# For Windows
if (WIN32)
    target_link_libraries(CLIENT wsock32 ws2_32)
    target_link_libraries(SERVER wsock32 ws2_32)
    target_link_libraries(TESTS wsock32 ws2_32)
endif (WIN32)
