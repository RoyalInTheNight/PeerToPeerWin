cmake_minimum_required(VERSION 3.23)
project(untitled)

set(CMAKE_CXX_STANDARD 17)

add_executable(untitled peer-to-peer-net.cpp NetUtils.cpp Utils.cpp)
