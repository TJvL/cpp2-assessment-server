cmake_minimum_required(VERSION 3.1)

set(CMAKE_CXX_STANDARD 20)

project(Cpp2Server)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

add_executable(Cpp2Server src/Server.cpp)

target_link_libraries(Cpp2Server PRIVATE Threads::Threads)
