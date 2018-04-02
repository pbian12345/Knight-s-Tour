#ifndef LINKEDLISTBASECLASS_H
#define LINKEDLISTBASECLASS_H

#include <cstdlib>

enum linkedListBaseClassErrors {LL_FULL, LL_EMPTY, LL_BAD_SIZE};
enum linkedListType {LL_STACK, LL_MAP};

struct node
{
    void *key, *data;
    node *next;

    node(){
        key = data = next = nullptr;
    }
    ~node(){
        key = data = next = nullptr;
    }
    node(void *k, void *d){
        key = k;
        data = d;
        next = nullptr;
    }
};

class linkedListBaseClass
{

public:
    explicit linkedListBaseClass(linkedListType type = LL_STACK);

    // Must derive a class in order to use the pure virtual destructor
    virtual ~linkedListBaseClass() = 0;

    bool full();
    bool empty();
    size_t size();
    size_t capacity();
    // Must derive a class in order to use the pure virtual clear function
    virtual void clear() = 0;

protected:
    node *head, *tail;
    size_t mySize, myCapacity;
    linkedListType myType;

    // Must derive a class in order to use the pure virtual nukem
    virtual void nukem() = 0;
    void copy(const linkedListBaseClass &other);
    void insert(node *n);
    node* remove(node *n = nullptr);

    // virtual bool isLessThan(node *x, node *y);

private:
};

#endif // LINKEDLISTBASECLASS_H
