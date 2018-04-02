//
// Created by pierson on 3/28/18.
//

#ifndef TEST_KNIGHT_TOUR_H
#define TEST_KNIGHT_TOUR_H

#include "queue.h"
#include "linkedlist.h"
#include <vector>
#include <string>

class Tour {
public:
    Tour(int x = 4, int y = 4);
    ~Tour();
    Tour(const Tour &other);
    Tour&operator=(const Tour &other);

    std::vector<int*> possibles();
    void possibles_stack();
    int* search(std::vector<int*> poses);
    int* searchStack();
    int *search();

    void q_enqueue(int* input);
    bool check_for_solutions();
    bool check_if_solved();

    void stack_push(int* pos);

    myqueue::myQueue<int*> stack_pop();
    int* q_dequeue();

    int getXPosition();
    int getYPosition();

    void printBoard();

    void q_print();
private:
    // 2D array of type int
    int** _board;
    bool solved;
    int number_of_solutions;
    myqueue::myQueue<int*> _path;
    linkStack<int*> stack_path;
    int _x, _y;
    int* _position;
    int* start_position;

    void copy(const Tour &other);
    void nukem();
    void update_pos();
    bool on_board(int x, int y);
};


#endif //TEST_KNIGHT_TOUR_H
