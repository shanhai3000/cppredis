cmake_minimum_required(VERSION 3.15)
project(cppredis)

set(CMAKE_CXX_STANDARD 11)

add_executable(cppredis src/server.cpp include/server.h include/version.h)