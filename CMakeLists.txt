cmake_minimum_required(VERSION 3.9)
project(test_knight)

set(CMAKE_CXX_STANDARD 11)

add_executable(test_knight main.cpp tour.cpp tour.h myStack.h linked_list.h priorityqueue.h)