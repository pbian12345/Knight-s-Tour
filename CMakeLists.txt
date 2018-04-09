cmake_minimum_required(VERSION 3.9)
project(priorityQueue_ArrayBased)

set(CMAKE_CXX_STANDARD 11)

add_executable(priorityQueue_ArrayBased main.cpp PQArray.cpp PQArray.h queuebase.cpp queuebase.h)