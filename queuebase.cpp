//
// Created by pierson on 3/27/18.
//
#include "queuebase.h"
#include <iostream>

queueBase::queueBase()
{
    mySize = 0;
    myCapacity = 5;
//    head = tail = nullptr;
    queueType = Q_PRIORITY;
    whichEnd = Q_FRONT;
}

queueBase::~queueBase()
{
    // Virtual functions should generally not be used in constructors and destructors
}

QUEUE_TYPE queueBase::getQueueType(){
    return queueType;
}


size_t queueBase::size()
{
    return mySize;
}

size_t queueBase::capacity()
{
    return myCapacity;
}

bool queueBase::empty() const
{
    return !mySize;
}

bool queueBase::full()
{
    return mySize == myCapacity;
}

//virtual void clear() = 0;

//virtual bool compare(node *x, node *y) = 0;

void queueBase::enqueue(q_node *who)
{
    q_node *ptr = tail;
    switch(queueType)
    {
        case Q_PRIORITY :
            if(empty())
                addToEnd(who);
            else if(isLessOrEqual(who, tail))
                addToEnd(who);
            else
            if(isGreater(who, head))
                addToFront(who);
            else
            {
                for(;ptr && isGreater(who, ptr->next); ptr = ptr->next);
                who->prev = ptr;
                who->next = ptr->next;
                ptr->next->prev = who;
                ptr->next = who;
            }

            break;

        case Q_NORMAL   : addToEnd(who);
            break;
        case Q_DEQUE :
            if(empty())
                addToEnd(who);
            else if(whichEnd == Q_REAR)
                addToFront(who);
            else addToEnd(who);
            break;
        case Q_PRIORITY_DEQUE :
            if(empty())
                addToEnd(who);
            else if(isLessOrEqual(who, tail))
                addToEnd(who);
            else
            if(isGreater(who, head))
                addToFront(who);
            else
            {
                for(;ptr && isGreater(who, ptr->next); ptr = ptr->next);
                who->prev = ptr;
                who->next = ptr->next;
                ptr->next->prev = who;
                ptr->next = who;
            };
    };
    ++mySize;
}

void queueBase::addToFront(q_node* who) {
    head->next = who;
    who->prev = head;
    head = head->next;
}

void queueBase::addToEnd(q_node *who)
{
    if(empty()){
        head = tail = who;
    }
    else
    {
        tail->next = new q_node(who->data,who->priority);
        tail = tail->next;
    }
}



q_node* queueBase::dequeue()
{
    q_node *item = head;
    switch(queueType)
    {
        case Q_PRIORITY : head = head->next;
            if (mySize != 1){
            }
            break;
        case Q_NORMAL   :
            head = head->prev;
            head->next = NULL;
            break;

        case Q_DEQUE   :
        case Q_PRIORITY_DEQUE : break;
    };
    --mySize;
    return item;
}

q_node* queueBase::peek()
{
    return head;
}