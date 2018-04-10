//
// Created by pierson on 3/28/18.
//

#ifndef TEST_KNIGHT_TOUR_H
#define TEST_KNIGHT_TOUR_H

#include "priorityqueue.h"
#include "myStack.h"
#include <vector>
#include <string>

class Tour {
public:
    Tour(int x = 4, int y = 4);
    ~Tour();
    Tour(const Tour &other);
    Tour&operator=(const Tour &other);

    void possibles();
    void possibles_bt();
    bool search();

    void Enqueue(int *input);
    int* Dequeue();

    int getXPosition() const {return _x;}
    int getYPosition() const {return _y;}
    bool get_have_bted() const {return _have_bted;}

    void printBoard();
    bool is_closed();
    bool is_solved();
    bool run_check(bool is_null);

    void q_print();
    void normal_print();
private:
    // 2D array of type int
    int** _board;
    myStack<int*> _path;
//    PQArray<int*> _path;

//backtracking storage

    // 63x8 2d array containing int*
    int*** _back_track;//capacity of 63
    myStack<int> _restore_val;
    int _spaces_moved;//be careful w/ this variable: it keeps track of current location in _back_track[]

    int _x, _y;
    int* _position;
    int* _start_position;
    bool _have_bted;

    void copy(const Tour &other);
    void nukem();
    void update_pos();
    void print_location(int*);
    bool on_board(int x, int y);
};


#endif //TEST_KNIGHT_TOUR_H
