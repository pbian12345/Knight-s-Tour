//
// Created by pierson on 3/27/18.
//

#ifndef CS8_LAB_PRIORITY_QUEUE_PRIORITYQUEUE_H
#define CS8_LAB_PRIORITY_QUEUE_PRIORITYQUEUE_H

#include "queuebase.h"
//#include <QDebug>
#include <iostream>
#include <cstdlib>

// Queue class that inherits from a base class
template<typename Data, typename Priority = int>
class queue : public queueBase
{
public:
    queue( size_t c = 64, QUEUE_TYPE q = Q_PRIORITY);
    ~queue();
    queue(const queue<Data,Priority> &other);
    queue<Data,Priority>& operator=(const queue<Data,Priority> &other);
    void enqueue(const Data &d, const Priority &p = mySize);
    queue<Data,Priority>& operator>>(Data &d);
    queue<Data,Priority>& operator<<(const Data &d);
    Data dequeue();
    Data peek();
    void clear();



private:
    void copy(const queue<Data,Priority> &other);
    void nukem();
    bool isGreaterOrEqual(node *x, node *y) override; // Overriding a virtual function from the base class
    bool isLess(node *x, node *y) override;
    bool isGreater(node *x, node *y) override;
    bool isLessOrEqual(node *x, node *y) override;

};


template<typename Data, typename Priority>
queue<Data,Priority>::queue(size_t c, QUEUE_TYPE q)
{
    myCapacity = c;
    queueType = q;
}

template<typename Data, typename Priority >
queue<Data,Priority>::~queue()
{
    nukem();
    mySize = myCapacity = 0;
}

template<typename Data, typename Priority >
queue<Data,Priority>::queue(const queue<Data,Priority> &other)
{
    copy(other);
}

template<typename Data, typename Priority >
queue<Data,Priority>& queue<Data,Priority>::operator=(const queue<Data,Priority> &other)
{
    if(this != &other)
    {
        nukem();
        copy(other);
    }
    return  *this;
}


template<typename Data, typename Priority >
void queue<Data,Priority>::enqueue(const Data &d, const Priority &p)
{

    node *newNode = new node;
    newNode->data = new Data(d);
    newNode->priority = new Priority(p);
    queueBase::enqueue(newNode);
}

template<typename Data, typename Priority >
Data queue<Data,Priority>::dequeue()
{
    Data data;
    node* bye;

    try
    {
        // 1. Set temporary pointer to point to head node
        // 2. Move head pointer so that it points to the second node
        // 3. Delete the temporary pointer

        // 1. First asterisk typecasts it
        // 2. Second asterisk dereferences it

        bye = head;
        data = *(Data*)queueBase::dequeue()->data;
        delete (Data*)bye->data;
        bye->data = NULL;
        delete (Priority*)bye->priority;
        bye->priority = NULL;
        delete bye;
    }
    catch(QUEUE_ERRORS e)
    {
        switch(e)
        {
            case Q_EMPTY : std::cout<<"Queue is empty!"<<std::endl;
                break;
            case Q_FULL: std::cout<<"Queue is full!" << std::endl;
                break;
            case Q_BAD_SIZE: std::cout<<"Bad size!" << std::endl;
                break;
        }
    }
    catch(...)
    {
        std::cout<<"Unknown error occurred. Program terminating"<<std::endl;
        exit(1);
    }
    return data;
}
//Fix
template<typename Data, typename Priority >
Data queue<Data,Priority>::peek()
{
    Data data;
    node* bye;
    try
    {
        data = *(Data*)queueBase::peek()->data, bye = head;
    }
    catch(QUEUE_ERRORS e)
    {
        switch(e)
        {
            case Q_EMPTY : std::cout<<"Dequeuing failed!"<<std::endl;
                break;

            case Q_FULL:
            case Q_BAD_SIZE: break;
        }
    }
    catch(...)
    {
        std::cout<<"Unknown error occurred. Program terminating"<<std::endl;
        exit(1);
    }
    return data;
}

// Fix
template<typename Data, typename Priority >
void queue<Data,Priority>::copy(const queue<Data,Priority> &other)
{
    if(other.empty())
        return;
    mySize = other.mySize;
    myCapacity = other.myCapacity;
    head = new node(new Data(*(Data*)other.head->data),
                    new Priority(*(Priority*)other.head->priority));
    tail = new node(new Data(*(Data*)other.tail->data),
                    new Priority(*(Priority*)other.tail->priority));
    node *ptr2 = head;
    for(node *ptr = other.head->prev;
        ptr != tail;
        ptr = ptr->prev,
                ptr2 = ptr2->prev)
    {
        ptr2->prev = new node(new Data(*(Data*)ptr->data),
                              new Priority(*(Priority*)ptr->priority));
        ptr2->prev->next = ptr2;
    }
    tail->next = ptr2;
    ptr2->prev = tail;
}

template<typename Data, typename Priority >
void queue<Data,Priority>::clear()
{
    nukem();
}

template<typename Data, typename Priority >
void queue<Data,Priority>::nukem()
{
    node *ptr = head;

    while (ptr != 0){
        node *bye = ptr;
        ptr = ptr->next;
        delete bye;
        bye = NULL;

    }
    mySize = myCapacity = 0;
    head = tail = nullptr;
}

template<typename Data, typename Priority >
bool queue<Data,Priority>::isGreaterOrEqual(node *x, node *y)
{
    return *(Priority*)x->priority >= *(Priority*)y->priority;
}

template<typename Data, typename Priority >
bool queue<Data,Priority>::isLess(node *x, node *y)
{
    return *(Priority*)x->priority < *(Priority*)y->priority;
}

template<typename Data, typename Priority >
bool queue<Data,Priority>::isGreater(node *x, node *y)
{
    return *(Priority*)x->priority > *(Priority*)y->priority;
}

template<typename Data, typename Priority >
bool queue<Data,Priority>::isLessOrEqual(node *x, node *y)
{
    return *((Priority*)x->priority) <= *((Priority*)y->priority);
}

template<typename Data, typename Priority >
queue<Data,Priority>& queue<Data,Priority>::operator>>(Data &d)
{
    d = dequeue();
    return *this;
}

template<typename Data, typename Priority >
queue<Data,Priority>& queue<Data,Priority>::operator<<(const Data &d)
{
    enqueue(d, 0);
    return *this;
}

#endif //CS8_LAB_PRIORITY_QUEUE_PRIORITYQUEUE_H
