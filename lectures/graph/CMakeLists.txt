cmake_minimum_required(VERSION 3.5.0)
project(graph VERSION 0.1.0 LANGUAGES C CXX)

include_directories(../common ../dictionary ../list)

add_executable(graph main.cpp)

