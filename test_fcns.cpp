//
// Created by pierson on 4/2/18.
//

#include "test_fcns.h"
#include <iostream>
using namespace std;

bool test_ctors(){
    //also testing priority

    //test enqueue and dequeue
    queue<char, int> que(65);
    for(size_t i = 'A'; i <= 'Z'; ++i){
        que.enqueue(i,'Z' - i);
    }

    if(que.size() != 26){
        cout << "size failed" << endl;
        return false;
    }
    int i = 'A';
    while(!que.empty())
    {
        if(que.dequeue() != i){
            cout << "enqueue/dequeue failed" << endl;
            return false;
        }
        ++i;
    }

    //test << and >>
    for(size_t j = 'A'; j <= 'Z'; ++j){
        que<<j;
    }

    if(que.size() != 26){
        cout << "size failed" << endl;
        return false;
    }
    i = 'A';
    while(!que.empty())
    {
        char bitch;
        que>> bitch;
        if(bitch != i){
            cout << "<< / >> failed" << endl;
            return false;
        }
        ++i;
    }

    //testing priority
    for(size_t j = 'A'; j <= 'Z'; ++j){
        que.enqueue(j,'Z' - j);
    }
    que.enqueue('0', 99);
    //should go right to beginning of queue

    if(que.size() != 27){
        cout << "size failed" << endl;
        return false;
    }
    if(que.dequeue() != '0'){
        cout << "priority failed" << endl;
        return false;
    }

    return true;
}
bool test_destruction(){
    queue<char, int> que(65);
    for(size_t i = 'A'; i <= 'Z'; ++i){
        que.enqueue(i,'Z' - i);
    }
    que.clear();
    if(que.size()){
        return false;
    }
    return true;
}
bool test_peek(){
    queue<char, int> que(65);
    for(size_t i = 'A'; i <= 'Z'; ++i){
        que.enqueue(i,'Z' - i);
    }
    if(que.peek() != 'A'){
        return false;
    }
    return true;
}