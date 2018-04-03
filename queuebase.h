//
// Created by pierson on 4/2/18.
//

#ifndef CS8_PRIORITY_QUEUE_QUEUEBASE_H
#define CS8_PRIORITY_QUEUE_QUEUEBASE_H


#include <cstdlib>

// Declares what type of queue it is
enum QUEUE_TYPE {Q_NORMAL,Q_PRIORITY, Q_DEQUE, Q_PRIORITY_DEQUE };
// Declares the queue errors
enum QUEUE_ERRORS {Q_EMPTY, Q_FULL, Q_BAD_SIZE};
// IDK
enum WHICH_END {Q_FRONT, Q_REAR};

// Node: Contains data, priority, and pointers in order to link it to other nodes
struct node
{
    // Void pointers to point to data and priority
    void *data, *priority;

    // Node pointers to point to the next and prev nodes
    node *next, *prev;

    // Default constructor
    node()
    {
        // Linked list starts off as empty
        next = prev = nullptr;
        data = priority = nullptr;
    }
    // Overloaded constructor with void pointers to data and priority
    node(void *d, void *p)
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
    node *head, *tail;
    QUEUE_TYPE queueType;
    WHICH_END whichEnd;

    virtual bool isGreaterOrEqual(node *x, node *y) = 0;
    virtual bool isLess(node *x, node *y) = 0;
    virtual bool isGreater(node *x, node *y) = 0;
    virtual bool isLessOrEqual(node *x, node *y) = 0;
    void enqueue(node *who);
    node* dequeue();
    node* peek();

private:
    void addToEnd(node *who);
    void addToFront(node *who);
};


#endif //CS8_PRIORITY_QUEUE_QUEUEBASE_H
