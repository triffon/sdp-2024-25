cmake_minimum_required(VERSION 3.5.0)
project(calculator VERSION 0.1.0 LANGUAGES C CXX)

add_executable(calculator main.cpp rpn_calculator.cpp binary_tree_calculator.cpp calculator.cpp)
include_directories(../common ../stack ../trees)

