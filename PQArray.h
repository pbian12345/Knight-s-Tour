//
// Created by Luz on 4/8/2018.
//

#ifndef PRIORITYPQArray_ARRAYBASED_PQARRAY_H
#define PRIORITYPQArray_ARRAYBASED_PQARRAY_H
#include <iostream>
#include <cstdlib>

enum QUEUE_ERRORS{PQ_BADSIZE, PQ_EMPTY, PQ_FULL, PQ_BADPRIORITY};

using namespace std;

struct PQ_node
{
    void *data, *priority;


    PQ_node(){
        data = nullptr;
        priority = nullptr;
    }
    PQ_node(void *d, void *p){
        data = d;
        priority = p;
    }

};


template<typename Data, typename Priority = int>
class PQArray {

public:
    PQArray(int capacity = 65);
    ~PQArray();
    size_t capacity();
    bool empty() const;
    bool full();
    Data peek();
    PQArray<Data,Priority>(PQArray<Data,Priority> &other);
    PQArray<Data,Priority>& operator=(PQArray<Data,Priority> &other);
    void clear();
    void copy(PQArray<Data,Priority> &other);
    void enqueue(Data d, Priority p);
    PQArray<Data,Priority>& operator>>(Data &d);
    PQArray<Data,Priority>& operator<<(const Data &d);
    Data dequeue();



private:
    PQ_node prqueue;
    void addToEnd(PQ_node *who);
    void addToFront(PQ_node *who);
    int mySize, head, tail, head_priority, tail_priority, myCapacity;
    int currentindex;
    void nukem();
    bool isGreater(PQ_node *p1,Priority p2);
    bool isLessOrEqual(PQ_node *p1, Priority p2);
    PQ_node* array[65];


};

template<typename Data, typename Priority>
PQArray<Data,Priority>::PQArray(int capacity)
{

    if (capacity > 2)
    {
        // If capacity entered is greater than 2, allocate space for user-entered array
        head = tail = -1;
        mySize = 0;
        head_priority = tail_priority = 0;
        myCapacity = capacity;
        currentindex = -1;
    }
    else {
        // Throw error if user inputted a size smaller than two
        throw PQ_BADSIZE;
    }

}

// Erases array
template<typename Data, typename Priority>
PQArray<Data,Priority>::~PQArray(){
    nukem();
}

// Return true if array is empty
template<typename Data, typename Priority>
bool PQArray<Data,Priority>::empty() const{
    return !mySize;
}

// Returns true if array is full
template<typename Data, typename Priority>
bool PQArray<Data,Priority>::full(){
    return mySize == myCapacity;
}

// Returns capacity of array
template<typename Data, typename Priority>
size_t PQArray<Data,Priority>::capacity(){
    return myCapacity;
}

template<typename Data, typename Priority>
void PQArray<Data,Priority>::copy(PQArray<Data,Priority> &other){
    if(other.empty())
        return;
    mySize = other.mySize;
    myCapacity = other.myCapacity;
    PQ_node *node;
    node = other.array[head];
    tail_priority = *(Priority*)node->priority;
    head_priority =  *(Priority*)node->priority;
    head = other.head;
    tail = other.head;

    for (int i = 0; i < other.mySize; i++){
        this->array[i] = other.array[i];
    }

}

template<typename Data, typename Priority>
PQArray<Data,Priority>& PQArray<Data,Priority>::operator=(PQArray<Data,Priority> &other){
    if(this != &other)
    {
        nukem();
        copy(other);
    }
    return  *this;

}

template<typename Data, typename Priority>
void PQArray<Data,Priority>::enqueue(Data d, Priority p) {

    PQ_node *newNode = new PQ_node;
    currentindex += 1;
    newNode->data = new Data(d);
    newNode->priority = new Priority(p);

    if (empty()) {
        addToEnd(newNode);
    }
    else if (isLessOrEqual(newNode,head_priority)) {
        addToEnd(newNode);
    }
    else if (isGreater(newNode, tail_priority)) {
        addToFront(newNode);
    }
    else {
        throw PQ_BADPRIORITY;
    }
}


template<typename Data, typename Priority >
void PQArray<Data,Priority>::addToEnd(PQ_node *who){
    // Increase tail index by one

    if (empty()){
        head += 1;
        tail += 1;
        tail_priority = *(Priority*)who->priority;
        head_priority =  *(Priority*)who->priority;
        array[tail] = array[head] = who;
        ++mySize;
    }
    else if (!full()){
        tail += 1;
        tail_priority = *(Priority*)who->priority;
        array[tail] = who;
        ++mySize;
    }
    else {
        throw PQ_FULL;
    }
}

template<typename Data, typename Priority >
bool PQArray<Data,Priority>::isGreater(PQ_node *p1, Priority p2)
{
    return *(Priority*)p1->priority > p2;
}
template<typename Data, typename Priority >
bool PQArray<Data,Priority>::isLessOrEqual(PQ_node *p1, Priority p2)
{

    return *(Priority*)p1->priority <= p2;
}
template<typename Data, typename Priority>
void PQArray<Data,Priority>::addToFront(PQ_node *n)
{
    // Increase size and therefore index of array
    if (!full()){
        head = mySize+1;
        // Assign priority to head
        head_priority = *(Priority*)n->priority;
        // Assign data to new head
        array[head] = n;
        ++mySize;
    }
    else {
        throw PQ_BADSIZE;
    }

}

template<typename Data, typename Priority>
PQArray<Data,Priority>& PQArray<Data,Priority>::operator>>(Data &d){
    d = dequeue();
    return *this;

}

template<typename Data, typename Priority>
PQArray<Data,Priority>& PQArray<Data,Priority>::operator<<(const Data &d){
    enqueue(d, 0);
    return *this;
}


template<typename Data, typename Priority>
Data PQArray<Data,Priority>::dequeue(){

    Data data;
    PQ_node* bye;

    try
    {
        // 1. Set temporary pointer to point to head node
        // 2. Move head pointer so that it points to the second node
        // 3. Delete the temporary pointer

        // 1. First asterisk typecasts it
        // 2. Second asterisk dereferences it

        bye = array[head];

        array[head] = array[head+1];
        if (mySize != 1) {
            array[head] = NULL;
        }
        head +=1;

        data = *(Data*)bye->data;
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
            case PQ_EMPTY : std::cout<<"Queue is empty!"<<std::endl;
                break;
            case PQ_FULL: std::cout<<"Queue is full!" << std::endl;
                break;
            case PQ_BADSIZE: std::cout<<"Bad size!" << std::endl;
                break;
            case PQ_BADPRIORITY: std::cout<<"Bad priority!" << std::endl;
                break;
        }
    }
    catch(...)
    {
        std::cout<<"Unknown error occurred. Program terminating"<<std::endl;
        exit(1);
    }
    --mySize;
    return data;

}

template<typename Data, typename Priority>
Data PQArray<Data,Priority>::peek()
{
    return array[head];
}

template<typename Data, typename Priority>
PQArray<Data,Priority>::PQArray(PQArray<Data,Priority> &other){
    copy(other);
}

template<typename Data, typename Priority>
void PQArray<Data,Priority>::clear(){
    nukem();
}
template<typename Data, typename Priority>
void PQArray<Data,Priority>::nukem(){

    for (int i = 0; i < mySize; i++){
        delete[] array[i];
        array[i] = nullptr;
    }
    head = tail = -1;
    mySize = myCapacity = 0;
}

#endif //PRIORITYPQArray_ARRAYBASED_PQARRAY_H
