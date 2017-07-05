cmake_minimum_required(VERSION 3.3)
project(inlupp_1_3_neural_net)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wpedantic")

set(SOURCE_FILES main.cpp NeuralNet.cpp NeuralNet.h)
add_executable(inlupp_1_3_neural_net ${SOURCE_FILES})