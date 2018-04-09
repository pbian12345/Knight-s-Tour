#include <iostream>
#include "PQArray.h"

using namespace std;

int main() {
    PQArray<char, int> ji(65);

    cout<<"I'm enqueuing"<<endl;
    for(size_t i = 'A'; i <= 'Z'; ++i){
        cout << 'Z' - i << endl;
        ji.enqueue(i,'Z' - i);
    }
    ji.clear();
    cout << "I'm enqueuing again!" << endl;
    for(size_t i = 'A'; i <= 'Z'; ++i){
        ji.enqueue(i,'Z' - i);
    }

    while(!ji.empty())
    {
        char d = ji.dequeue();
        cout<<d<<endl;
    }
    cout<<"I'm exiting"<<endl;
    return 0;
}