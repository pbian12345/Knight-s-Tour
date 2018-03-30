#include <iostream>
#include "tour.h"
using namespace std;

int main() {
    Tour test1(4, 4);

    for(int i = 0; i < 63; ++i){
        test1.q_enqueue(test1.search(test1.possibles()));
    }
    for(int i = 0; i < 63; ++i){
        cout << "iteration #" << i + 1 << endl;
        test1.q_print();
    }
    return 0;
}