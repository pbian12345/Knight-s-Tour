#include <iostream>
#include "priorityQueue.h"

using namespace std;

int main()
{
    queue<char, int> que(65);
    cout<<"I'm enqueuing"<<endl;
    for(size_t i = 'A'; i <= 'Z'; ++i){
        cout << 'Z' - i << endl;
        que.enqueue(i,'Z' - i);
    }
    cout<<"I'm dequeuing"<<endl;
    cout << que.size() << endl;
    while(!que.empty())
    {
        char d = que.dequeue();
        cout<<d<<endl;
    }
    cout<<"I'm exiting"<<endl;
    return 0;

}
