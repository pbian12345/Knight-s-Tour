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

    int getXPosition();
    int getYPosition();

    void printBoard();
    bool check_for_solutions();
    bool check_if_solved();

    void q_print();
private:
    // 2D array of type int
    int** _board;
    bool _solved;
    int _number_of_solutions;
    myStack<int*> _path;
//    queue<int*> _path;

//backtracking storage
    int*** _back_track;//capacity of 63
    int _spaces_moved;//be careful w/ this variable: it keeps track of current location in _back_track[]

    int _x, _y;
    int* _position;
    int* _start_position;

    void copy(const Tour &other);
    void nukem();
    void update_pos();
    bool on_board(int x, int y);
};


#endif //TEST_KNIGHT_TOUR_H
