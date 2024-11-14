cmake_minimum_required(VERSION 3.5.0)
project(horse VERSION 0.1.0 LANGUAGES C CXX)

add_executable(horse main.cpp)
include_directories(../common ../stack)