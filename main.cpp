#include <iostream>
#include "tour.h"
using namespace std;

void user_input(string &input);


int main() {

    // Calls constructor of test1 class. Sets origin point as (4, 4).
    // Initializes board.
    Tour test1(4, 4);
    test1.printBoard();

    bool is_done = false;
    while (!is_done){
//        test1.possibles();
        if(!test1.get_have_bted()){
            test1.possibles();
        }
        // Chain rule function call, isnull is a set of a possibilities on
        is_done = test1.run_check(test1.search());
    }
    cout << "Successful closed tour!" << endl;
    test1.printBoard();
    cout << endl << "======================Printing path========================" << endl;
    test1.normal_print();


//    test1.printBoard();
//    cout << "Success? " << test1.is_solved();

    return 0;
}

//Widget needs array of coordinates