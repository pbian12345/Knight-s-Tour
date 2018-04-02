#include "linkedlistbaseclass.h"

linkedListBaseClass::linkedListBaseClass(linkedListType type)
{
    mySize = 0;
    head = nullptr;
    myCapacity = 10;
    myType = type;
}


linkedListBaseClass::~linkedListBaseClass()
{

}

bool linkedListBaseClass::full()
{
    return mySize == myCapacity;
}

bool linkedListBaseClass::empty()
{
    return !mySize;
}

size_t linkedListBaseClass::size()
{
    return mySize;
}

size_t linkedListBaseClass::capacity()
{
    return myCapacity;
}

//virtual void clear() = 0;



void nukem(){


}


void linkedListBaseClass::insert(node *n)
{

    if(full())
        throw LL_FULL;
    switch(myType)
    {
        case LL_STACK :
            if (empty()){
                head = tail = n;
                tail->next = nullptr;
            }
            else {
                n->next = head;
                head = n;
                tail->next = nullptr;
            }
            break;

        case LL_MAP   : break;
            //For you....
    }
}

node* linkedListBaseClass::remove(node *n)
{
    if(empty())
        throw LL_EMPTY;
    node* who;
    switch(myType)
    {
        case LL_STACK :
            if (head != nullptr){
                who = head;
                head = head->next;
                return who;
            }
            break;

        case LL_MAP   : break;
            //For you....
    }
}
