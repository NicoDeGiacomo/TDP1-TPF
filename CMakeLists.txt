cmake_minimum_required(VERSION 3.16)
project(QUANTUM-CHESS)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(./common)
include_directories(./client)
include_directories(./server)
include_directories(./tests)
include_directories(./tests/doctest)

add_executable(TESTS
        tests/Tests.cpp common/ChessBoard.cpp common/ChessBoard.h)

add_executable(CLIENT
        common/ChessBoard.cpp common/ChessBoard.h common/Socket.cpp common/Socket.h client/client_main.cpp)

add_executable(SERVER
        common/ChessBoard.cpp common/ChessBoard.h common/Socket.cpp common/Socket.h server/server_main.cpp)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(CLIENT Threads::Threads)
target_link_libraries(SERVER Threads::Threads)