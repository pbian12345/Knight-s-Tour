#ifndef linkStack_H
#define linkStack_H
#include<cstdlib>
#include<iostream>
#include"linkedlistbaseclass.h"

using namespace std;

template<typename T>
class linkStack : public linkedListBaseClass
{
public:
//            linkStack();
    explicit linkStack(size_t cap = 64);
    ~linkStack() override;
    linkStack(const linkStack<T> &other);
    linkStack<T>& operator=(const linkStack<T> &other);
    linkStack<T>& operator<<(T &d);
    linkStack<T>& operator>>(T &d);

    T peek();
    T pop();
    void push(const T &data);
    void clear();
private:
    void copy(const linkStack<T> &other);
    void nukem() override;
};


//template<typename T>
//linkStack<T>::linkStack(){
//    mySize = 0;
//    head = nullptr;
//}

template<typename T>
linkStack<T>::linkStack(size_t cap)
{
    if(cap<2)
        throw LL_BAD_SIZE;
    myCapacity = cap;
    mySize = 0;
    head = tail = nullptr;
    myType = LL_STACK;

}

template<typename T>
linkStack<T>::~linkStack()
{
    nukem();
    mySize = myCapacity = 0;
    head = tail = nullptr;
}

template<typename T>
linkStack<T>::linkStack(const linkStack<T> &other)
{
    copy(other);
}

template<typename T>
linkStack<T>& linkStack<T>::operator=(const linkStack<T> &other)
{
    if(this != &other)
    {
        nukem();
        copy(other);
    }
    return *this;
}


template<typename T>
T linkStack<T>::peek()
{

    if(empty())
        throw LL_EMPTY;

    // First asterisk: Typecasts void pointer to pointer of appropriate type T
    // Second asterisk (outermost asterisk): Dereferences appropriately typecasted pointer in order to access data
    return *((T*)head->data);
}

template<typename T>
T linkStack<T>::pop()
{
    try
    {
        T data = *(T *)head->data;
        node *ptr = remove();
        delete ptr;
        --mySize;
        return data;
    }
    catch(linkedListBaseClassErrors e)
    {
        switch(e)
        {
            case LL_FULL :throw LL_FULL;
                break;
            case LL_EMPTY: throw LL_EMPTY;
                break;
            case LL_BAD_SIZE : break;
        }
    }
    catch (...){
        cout << "ERROR!" << endl;
    }
}

template<typename T>
void linkStack<T>::push(const T &data)
{

//    const bool debug = true;
//    if(debug){
//        cout << "push called" << endl;
//    }
    node *newNode;
    try
    {
        newNode = new node(NULL, new T(data));
        // Construct new node with key as null, value as typecasted data
        // Attempt to insert node
        insert(newNode);
        ++mySize;
    }
    catch(linkedListBaseClassErrors e)
    {
        switch(e)
        {
            case LL_FULL : delete newNode;
                throw LL_FULL;
            case LL_EMPTY: break;
            case LL_BAD_SIZE : break;
        }
    }
    catch (...){
        cout << "Other error detected!" << endl;
    }
//    cout << "PUSH HAS FINISHED!" << endl;
}

template<typename T>
void linkStack<T>::clear()
{
    size_t cap = myCapacity;
    nukem();
    head=nullptr;
    mySize=0;
}

template<typename T>
linkStack<T>& linkStack<T>::operator<<(T &d)
{
    d = pop();
    return *this;
}

template<typename T>
linkStack<T>& linkStack<T>::operator>>(T &d)
{
    push(d);
    return *this;
}


template<typename T>
void linkStack<T>::copy(const linkStack<T> &other)
{
    mySize = other.mySize;
    myType = other.myType;
    myCapacity = other.myCapacity;
    if(!other.head)
        return;
    head = new node(NULL, new T(*(T*)other.head->data));
    node *ptr = other.head->next, *ptr2 = head;
    for( ; ptr; ptr = ptr->next)
    {
        ptr2->next = new node(NULL, new T(*(T*)ptr->data));
        ptr2 = ptr2->next;
    }

}

template<typename T>
void linkStack<T>::nukem()
{
    try
    {
        while(!empty())
            T temp = pop();
    }
    catch(...)
    {
        cout << "ERROR occurred!" << endl;
    }
    mySize = myCapacity = 0;
}


#endif // linkStack_H
