//
// Created by pierson on 3/9/18.
//

#ifndef CS8_LAB_STACK_MYSTACK_H
#define CS8_LAB_STACK_MYSTACK_H

#include <cstddef>
#include "linked_list.h"

enum STACK_ERRORS {STACK_EMPTY, STACK_FULL};

template<typename T>
class myStack
{
public:
    explicit myStack(size_t cap = 65);
    ~myStack();
    myStack(const myStack &x);
    myStack& operator=(const myStack &x);
    bool empty();
    bool full();
    void clear();
    T peek();
    T dequeue();
    void enqueue(const T &data);

private:
    size_t _mySize, _myCapacity;
    List<T> _stack;
    //stack is list of nodes each containing an item of type T

    void nukem();
    void copy(const myStack &x);
};

template<typename T>
myStack<T>::myStack(size_t cap) {
    _mySize = 0;
    _myCapacity = cap;
}
template<typename T>
myStack<T>::~myStack() {
    nukem();
}
template<typename T>
myStack<T>::myStack(const myStack &x) {
    copy(x);
}
template<typename T>
myStack<T>& myStack<T>::operator=(const myStack &x) {
    if(this != &x){
        nukem();
        copy(x);
    }
    return *this;
}
template<typename T>
bool myStack<T>::empty() {
    //assuming size is regularly updated
    return _mySize == 0;
}
template<typename T>
bool myStack<T>::full() {
    //assuming size is regularly updated
    return _mySize == _myCapacity;
}
template<typename T>
void myStack<T>::clear() {
    //public clear_all fcn
    nukem();
}
template<typename T>
T myStack<T>::peek() {
    return (_stack.Begin())->_item;
}
template<typename T>
T myStack<T>::dequeue() {
    T target = (_stack.Begin())->_item;
    _stack.Delete(_stack.Begin());
    _mySize -= 1;
    return target;
}
template<typename T>
void myStack<T>::enqueue(const T &data) {
    _stack.insertHead(data);
    _mySize += 1;
}

template<typename T>
void myStack<T>::nukem() {
    //clear_all fcn
    _stack.clearList();
    _mySize = 0;
}
template<typename T>
void myStack<T>::copy(const myStack &x) {
    //List class already has overloaded assignment operator
    _stack = x._stack;
    _mySize = x._mySize;
    _myCapacity = x._myCapacity;
}

#endif //CS8_LAB_STACK_MYSTACK_H
