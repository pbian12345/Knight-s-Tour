//
// Created by pierson on 3/28/18.
//

#include "tour.h"
#include <cmath>
#include <iostream>

Tour::Tour(int x, int y) {
    //these rows will be repeated
        //they're the contents of an 8x8 board in terms of possible moves

    int row1[] = {2,3,4,4,4,4,3,2};
    int row2[] = {3,4,6,6,6,6,4,3};
    int row3[] = {4,6,8,8,8,8,6,4};
    _board = new int* [8];
    for(int i = 0; i < 8; ++i){
        _board[i] = new int [8];
        switch (i){
            case 0:{
                for(int j = 0; j < 8; ++j){
                    _board[i][j] = row1[j];
                }
                break;
            }
            case 1:{
                for(int j = 0; j < 8; ++j){
                    _board[i][j] = row2[j];
                }
                break;
            }
            case 2:{
                for(int j = 0; j < 8; ++j){
                    _board[i][j] = row3[j];
                }
                break;
            }
            case 3:{
                for(int j = 0; j < 8; ++j){
                    _board[i][j] = row3[j];
                }
                break;
            }
            case 4:{
                for(int j = 0; j < 8; ++j){
                    _board[i][j] = row3[j];
                }
                break;
            }
            case 5:{
                for(int j = 0; j < 8; ++j){
                    _board[i][j] = row3[j];
                }
                break;
            }
            case 6:{
                for(int j = 0; j < 8; ++j){
                    _board[i][j] = row2[j];
                }
                break;
            }
            case 7:{
                for(int j = 0; j < 8; ++j){
                    _board[i][j] = row1[j];
                }
                break;
            }
            default:
                break;
        }
    }
    _x = x;
    _y = y;
    _position = &_board[x][y];
    *_position = 0;
    int* temp = _position;
    std::cout << "initial position: " << _x << " , " << _y << std::endl;
    _path.enqueue(temp);
}
Tour::~Tour() {
    nukem();
}
Tour::Tour(const Tour &other) {
    copy(other);
}
Tour& Tour::operator=(const Tour &other) {
    if(this != &other){
        nukem();
        copy(other);
    }
}
std::vector<int*> Tour::possibles() {
        //pointer to each result put into vector to be returned
        //when making pointer, THAT is when the coordinates get connected to board

    //don't forget to check to make sure there are no null pointers
    //(pointers to positions that are not on board)
    std::vector<int*> pos_coord;
    int* temp = NULL;
    if(on_board(_x - 1, _y - 2)){
        temp = &_board[_x - 1][_y - 2];
        --(*temp);
        pos_coord.push_back(temp);
    }
    else if(on_board(_x - 2, _y - 1)){
        temp = &_board[_x - 2][_y - 1];
        --(*temp);
        pos_coord.push_back(temp);
    }
    else if(on_board(_x - 2, _y + 1)){
        temp = &_board[_x - 2][_y + 1];
        --(*temp);
        pos_coord.push_back(temp);
    }
    else if(on_board(_x - 1, _y + 2)){
        temp = &_board[_x - 1][_y + 2];
        --(*temp);
        pos_coord.push_back(temp);
    }
    else if(on_board(_x + 1, _y + 2)){
        temp = &_board[_x + 1][_y + 2];
        --(*temp);
        pos_coord.push_back(temp);
    }
    else if(on_board(_x + 2, _y + 1)){
        temp = &_board[_x + 2][_y + 1];
        --(*temp);
        pos_coord.push_back(temp);
    }
    else if(on_board(_x + 2, _y - 1)){
        temp = &_board[_x + 2][_y - 1];
        --(*temp);
        pos_coord.push_back(temp);
    }
    else if(on_board(_x + 1, _y - 2)){
        temp = &_board[_x + 1][_y - 2];
        --(*temp);
        pos_coord.push_back(temp);
    }
    return pos_coord;
}
int* Tour::search(std::vector<int*> poses) {
    //decide which possible move will be used (pushed into queue)


    //now check for smallest as in Warnsdorff's rule
        //as tie-breaker, counter-clockwise
    int count = 8;
    std::vector<int*>::iterator it = poses.begin();
    while(it != poses.end()){
        if(**it <= count){
            count = **it;
            _position = *it;
        }
        ++it;
    }
    update_pos();
    *_position = 0;
    int* temp = _position;
    return temp;
}

void Tour::q_enqueue(int *input) {
    _path.enqueue(input);
}
int* Tour::q_dequeue() {
    return _path.dequeue();
}
void Tour::copy(const Tour &other) {
    for(int i = 0; i < 8; ++i){
        for(int j = 0; j < 8; ++j){
            _board[i][j] = other._board[i][j];
        }
    }
    _path = other._path;
    _x = other._x;
    _y = other._y;
    _position = other._position;
}

void Tour::nukem() {
    delete[] _board;
    delete _position;
    _path.clear();
}
void Tour::update_pos() {
    for(int i = 0; i < 8; ++i){
        for(int j = 0; j < 8; ++j){
            if(_position == &_board[i][j]){
                _x = i;
                _y = j;
            }
        }
    }
}
bool Tour::on_board(int x, int y) {
    if(x < 0 || y < 0){
        return false;
    }
    else if(x > 8 || y > 8){
        return false;
    }
        //also check to see if value is 0
            //meaning you can't go there
    else if(_board[x][y] == 0){
        return false;
    }
    return true;
}
void Tour::q_print() {
    int x, y;
    int* temp = q_dequeue();
    for(int a = 0; a < 8; ++a){
        for(int b = 0; b < 8; ++b){
            if(temp == &_board[a][b]){
                x = a;
                y = b;
            }
        }
    }
    switch (x){
        case 0:{
            std::cout << "QR" << 9 - (y + 1) << std::endl;
            break;
        }
        case 1:{
            std::cout << "QN" << 9 - (y + 1) << std::endl;
            break;
        }
        case 2:{
            std::cout << "QB" << 9 - (y + 1) << std::endl;
            break;
        }
        case 3:{
            std::cout << "Q" << 9 - (y + 1) << std::endl;
            break;
        }
        case 4:{
            std::cout << "K" << 9 - (y + 1) << std::endl;
            break;
        }
        case 5:{
            std::cout << "KB" << 9 - (y + 1) << std::endl;
            break;
        }
        case 6:{
            std::cout << "KN" << 9 - (y + 1) << std::endl;
            break;
        }
        case 7:{
            std::cout << "KR" << 9 - (y + 1) << std::endl;
            break;
        }
        default:
            break;
    }
}