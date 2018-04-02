#include <iostream>
#include "tour.h"
using namespace std;

void user_input(string &input);


int main() {

    // Calls constructor of test1 class. Sets origin point as (4,4).
    // Initializes board.
    Tour test1(1, 0);
    myqueue::myQueue<int*> path_temp;

    for(int i = 0; i < 63; ++i){
        // First it calls the possibles function and generates all given possibilities from that point
        // Stores possibilities into a vector of int pointers
        // Returns vector to the search function
        test1.possibles_stack();
        test1.stack_push(test1.searchStack());
//        test1.q_enqueue(test1.search(test1.possibles()));
    }

    test1.printBoard();

//        test1.stack_push();
//    for(int i = 0; i < 63; ++i){
//        cout << "iteration #" << i + 1 << endl;
//        test1.q_print();
//    }
    return 0;
}
