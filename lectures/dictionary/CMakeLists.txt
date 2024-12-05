cmake_minimum_required(VERSION 3.5.0)
project(dictionary VERSION 0.1.0 LANGUAGES C CXX)

include_directories(../common ../list ../trees)

add_executable(dictionary main.cpp)

