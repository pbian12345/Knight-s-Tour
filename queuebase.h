//
// Created by pierson on 3/27/18.
//

#ifndef CS8_LAB_PRIORITY_QUEUE_QUEUEBASE_H
#define CS8_LAB_PRIORITY_QUEUE_QUEUEBASE_H

#include <cstdlib>

// Declares what type of queue it is
enum QUEUE_TYPE {Q_NORMAL,Q_PRIORITY, Q_DEQUE, Q_PRIORITY_DEQUE };
// Declares the queue errors
enum QUEUE_ERRORS {Q_EMPTY, Q_FULL, Q_BAD_SIZE};
// IDK
enum WHICH_END {Q_FRONT, Q_REAR};

// Node: Contains data, priority, and pointers in order to link it to other nodes
struct q_node
{
    // Void pointers to point to data and priority
    void *data, *priority;

    // Node pointers to point to the next and prev nodes
    q_node *next, *prev;

    // Default constructor
    q_node()
    {
        // Linked list starts off as empty
        next = prev = nullptr;
        data = priority = nullptr;
    }
    // Overloaded constructor with void pointers to data and priority
    q_node(void *d, void *p)
    {
        // Assigns void pointer d to data
        data = d;
        // Assigns void pointer p to priority
        priority = p;
    }
};

// Purpose: Creates a basic skeleton from which to form other queues
class queueBase
{
public:
    queueBase();
    ~queueBase();

    size_t size();
    size_t capacity();
    bool empty() const;
    bool full();
    QUEUE_TYPE getQueueType();
    void setQueueType(QUEUE_TYPE type);
    virtual void clear() = 0;
    void from(WHICH_END end);

protected:
    size_t mySize, myCapacity;
    q_node *head, *tail;
    QUEUE_TYPE queueType;
    WHICH_END whichEnd;

    virtual bool isGreaterOrEqual(q_node *x, q_node *y) = 0;
    virtual bool isLess(q_node *x, q_node *y) = 0;
    virtual bool isGreater(q_node *x, q_node *y) = 0;
    virtual bool isLessOrEqual(q_node *x, q_node *y) = 0;
    void enqueue(q_node *who);
    q_node* dequeue();
    q_node* peek();

private:
    void addToEnd(q_node *who);
    void addToFront(q_node *who);
};
#endif //CS8_LAB_PRIORITY_QUEUE_QUEUEBASE_H
