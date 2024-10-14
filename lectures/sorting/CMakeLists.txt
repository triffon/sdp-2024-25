cmake_minimum_required(VERSION 3.5.0)
project(sorting VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(sorting main.cpp)
include_directories(../common)
