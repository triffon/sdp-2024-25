cmake_minimum_required(VERSION 3.5.0)
project(trees VERSION 0.1.0 LANGUAGES C CXX)

include_directories(../common ../list)
add_executable(trees main.cpp)

