//
// Created by pierson on 3/28/18.
//

#ifndef TEST_KNIGHT_TOUR_H
#define TEST_KNIGHT_TOUR_H

#include "queue.h"
#include <vector>
class Tour {
public:
    Tour(int x = 4, int y = 4);
    ~Tour();
    Tour(const Tour &other);
    Tour&operator=(const Tour &other);

    std::vector<int*> possibles();
    int* search(std::vector<int*> poses);

    void q_enqueue(int* input);
    int* q_dequeue();

    void q_print();
private:
    int** _board;
    myqueue::myQueue<int*> _path;
    int _x, _y;
    int* _position;

    void copy(const Tour &other);
    void nukem();
    void update_pos();
    bool on_board(int x, int y);
};


#endif //TEST_KNIGHT_TOUR_H
