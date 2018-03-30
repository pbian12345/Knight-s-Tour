//
// Created by pierson on 3/22/18.
//
//typedef int T;
#include "test_fcns.h"
myStack<T> ctor(T array[]){
    myStack<T> test_stack(5);
    for(int i = 0; i < 5; ++i){
        test_stack.push(array[i]);
    }
    return test_stack;
}
bool test_ctor(){
    T input[5] = {1, 2, 3, 4, 5};
    myStack<T> test_stack1(ctor(input));
    for(int i = 4; i >= 0; --i){
        if(test_stack1.pop() != input[i]){
            return false;
        }
    }
    return true;
}
bool test_size(){
    //check empty and full fcns
    T input[5] = {1, 2, 3, 4, 5};
    myStack<T> test_stack1(ctor(input));

    if(test_stack1.empty()){
        cout << "empty failed" << endl;
        return false;
    }
    if(!test_stack1.full()){
        cout << "full failed" << endl;
        return false;
    }
    return true;
}
bool test_pop(){
    T input[5] = {1, 2, 3, 4, 5};
    myStack<T> test_stack1(ctor(input));
    if(test_stack1.pop() != 5){
        return false;
    }
    return true;
}
bool test_clear(){
    //test clear fcn
    const bool debug = false;
    if (debug){
        cout << "clear test called" << endl;
    }

    T input[5] = {1, 2, 3, 4, 5};
    myStack<T> test_stack1(ctor(input));

    if(debug){
        cout << "stack built" << endl;
    }

    test_stack1.clear();

    if(debug){
        cout << "stack cleared" << endl;
    }

    if(test_stack1.full()){
        cout << "stack returns false full" << endl;
        return false;
    }
    return true;
}
bool test_peek(){
    T input[5] = {1, 2, 3, 4, 5};
    myStack<T> test_stack1(ctor(input));
    if(test_stack1.peek() != 5){
        return false;
    }
    return true;
}