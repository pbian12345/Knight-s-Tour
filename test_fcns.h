//
// Created by pierson on 3/22/18.
//

#ifndef CS8_LAB_STACK_TEST_FCNS_H
#define CS8_LAB_STACK_TEST_FCNS_H

#include "myStack.h"
typedef int T;

myStack<T> ctor(T array[]);
bool test_ctor();
bool test_size();
bool test_clear();
bool test_peek();
bool test_pop();

#endif //CS8_LAB_STACK_TEST_FCNS_H