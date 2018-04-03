cmake_minimum_required(VERSION 3.9)
project(CS8_priority_queue)

set(CMAKE_CXX_STANDARD 11)

add_executable(CS8_priority_queue main.cpp priorityqueue.h queuebase.cpp queuebase.h test_fcns.cpp test_fcns.h)