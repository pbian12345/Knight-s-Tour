//
// Created by pierson on 3/21/18.
//

#ifndef CS8_LAB_STACK_LINKED_LIST_H
#define CS8_LAB_STACK_LINKED_LIST_H

#include <iostream>
using namespace std;
template <typename ITEM_TYPE>
struct node {
    ITEM_TYPE _item;
    node* _next;
    node(){
        _item = ITEM_TYPE();
        _next = NULL;
    }
    node(ITEM_TYPE item){
        _item = item;
        _next = NULL;
    }
//    template <class T>
//    friend ostream& operator <<(ostream& outs, const node<T> &print_me){
//        outs << print_me._item;
//        return outs;
//    }
};



template <typename T>
class List {
private:
    node<T>* _head;
    void copy(node<T>* copyThis);
public:
    List();
    List(node<T>* input);

    ~List();
    List(const List<T> &copyThis);
    List& operator =(const List& RHS);

    node<T>* insertHead(T i);
    node<T>* insertAfter(T i, node<T>* iMarker);
    node<T>* insertBefore(T i, node<T>* iMarker);
    T Delete(node<T>* iMarker);
    void clearList();
    node<T>* Search(const T &key);
    node<T>* Prev(node<T>* iMarker);
    T& operator[](int index);
    node<T>* Begin() const;
    node<T>* End() const;

    //insertion operator for list
    template <class U>
    friend ostream& operator <<(ostream& outs, const List<U>& rhs);
};

template <typename T>
List<T>::List() {
    //default ctor
    _head = NULL;
}
template <typename T>
List<T>::List(node<T> *input){
    //ctor takes linked list input
    copy(input);
}
template <typename T>
List<T>::~List() {
    //destructor of worlds!!
    clearList();
}
template <typename T>
List<T>::List(const List<T> &copyThis) {
    //copy ctor
    copy(copyThis._head);
}
template <typename T>
List<T>& List<T>::operator=(const List &RHS) {
    //assignment operator overload
    if (this != &RHS){
        clearList();
        copy(RHS._head);
    }
    return *this;
}

template <typename T>
node<T>* List<T>::insertHead(T i) {
    //inserts i at beginning of list
    node<T>* temp = new node<T>(i);
    temp->_next = _head;
    _head = temp;
    return _head;
}
template <typename T>
node<T>* List<T>::insertAfter(T i, node<T> *iMarker) {
    //inserts i after given node pointer
    if (!_head){
        return _head;
    }
    else if (!iMarker){
        return _head;
    }
    node<T>* insert_ptr = new node<T>(i);
    insert_ptr->_next = iMarker->_next;
    iMarker->_next = insert_ptr;
    return insert_ptr;
}
template <typename T>
node<T>* List<T>::insertBefore(T i, node<T> *iMarker) {
    //inserts i before given node pointer
    if (!_head){
        return _head;
    }
    else if (!iMarker){
        return _head;
    }
    node<T>* insert_ptr = new node<T>(iMarker);
    insert_ptr->_next = iMarker;
    Prev(iMarker)->_next = insert_ptr;
    return insert_ptr;
}

template <typename T>
T List<T>::Delete(node<T> *iMarker) {
    //deletes a single node in list
    if (_head == iMarker){
        _head = _head->_next;
        T contents = iMarker->_item;
        delete iMarker;
        return contents;
    }
    else if (!_head){
        return iMarker->_item;
    }
    else{
        node<T>* before_thing = Prev(iMarker);
        before_thing->_next = iMarker->_next;
        T contents = iMarker->_item;
        delete iMarker;
        return contents;
    }
}

template <typename T>
void List<T>::clearList() {
    //deletes entire list
    while (_head != NULL){
        Delete(_head);
    }
}

template <typename T>
node<T>* List<T>::Search(const T &key) {
    //searches for key and returns node pointer
    while (_head != NULL){
        if (_head->_item == key){
            return _head;
        }
        else{
            _head = _head->_next;
        }
    }
    return NULL;
}
template <typename T>
node<T>* List<T>::Prev(node<T> *iMarker) {
    //returns previous node pointer to given node pointer
    if (_head == iMarker){
        return NULL;
    }
    else{
        while (_head->_next != iMarker){ //segmentation error here
            _head = _head->_next;
        }
        return _head;
    }
}

template <typename T>
T& List<T>::operator[](int index) {
    //overloads brackets operator so can snag item of any node in list
    for (int i = 0; i <= index; i++){
        if (index == 0){
            return _head->_item;
        }
        _head = _head->_next;
    }
    return _head->_item;
}
template <typename T>
node<T>* List<T>::Begin() const {
    //returns head of linked list
    return _head;
}
template <typename T>
node<T>* List<T>::End() const {
    if (!_head){
        return NULL;
    }
    else{
        node<T>* temp = _head;
        while (temp->_next != NULL){
            temp = temp->_next;
        }
        return temp;
    }
}

template <typename T>
void List<T>::copy(node<T>* copyThis) {
    node<T>* cpy_walker = copyThis;
    node<T>* walker = _head;
    insertHead(copyThis->_item);
    while (cpy_walker != NULL){
        insertAfter(cpy_walker->_next->_item, walker);
        cpy_walker = cpy_walker->_next;
        walker = walker->_next;
    }
}


//template <typename U>
//ostream& operator <<(ostream& outs, const List<U>& rhs){
//    //overloads output operator
//    node<U>* walker = rhs._head;
//    while (walker != NULL){
//        outs << *walker << " ";
//        walker = walker->_next;
//    }
//    return outs;
//}
#endif //CS8_LAB_STACK_LINKED_LIST_H
