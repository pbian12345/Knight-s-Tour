//
// Created by pierson on 3/28/18.
//

#include "tour.h"
#include <cmath>
#include <iostream>

// Overloaded constructor
// Takes in two coordinates
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
    // Keeps start position
    _start_position = &_board[x][y];
    *_position = -99;
    int* temp = _position;
    _path.enqueue(temp);

    //backtracking
    _spaces_moved = 0;
    _back_track = new int**[65];
    for(int i = 0; i < 65; ++i){
        _back_track[i] = new int*[8];
        for(int j = 0; j < 8; ++j){
            _back_track[i][j] = nullptr;
        }
    }
    _have_bted = false;
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
void Tour::possibles() {
        //pointer to each result put into _back_track array
        //when making pointer, THAT is when the coordinates get connected to board
    // updates _back_track array

    //check for nulls and if spot has been visited done in on_board()

    int* temp = NULL;

    // First CounterClockWise(CCW) movement
    if(on_board(_x - 1, _y - 2)){
        temp = &_board[_x - 1][_y - 2];
        --(*temp);
        _back_track[_spaces_moved][0] = temp;
    }
    // 2nd CCW movement
    if(on_board(_x - 2, _y - 1)){
        temp = &_board[_x - 2][_y - 1];
        --(*temp);
        _back_track[_spaces_moved][1] = temp;
    }
    // 3rd CCW movement
    if(on_board(_x - 2, _y + 1)){
        temp = &_board[_x - 2][_y + 1];
        --(*temp);
        _back_track[_spaces_moved][2] = temp;
    }
    // 4th CCW movement
    if(on_board(_x - 1, _y + 2)){
        temp = &_board[_x - 1][_y + 2];
         --(*temp);
        _back_track[_spaces_moved][3] = temp;
    }
    // 5th CCW movement
    if(on_board(_x + 1, _y + 2)){
        temp = &_board[_x + 1][_y + 2];
         --(*temp);
        _back_track[_spaces_moved][4] = temp;
    }
    // 6th CCW movement
    if(on_board(_x + 2, _y + 1)){
        temp = &_board[_x + 2][_y + 1];
         --(*temp);
        _back_track[_spaces_moved][5] = temp;
    }
    // 7th CCW movement
    if(on_board(_x + 2, _y - 1)){
        temp = &_board[_x + 2][_y - 1];
         --(*temp);
        _back_track[_spaces_moved][6] = temp;
    }
    // 8th CCW movement
    if(on_board(_x + 1, _y - 2)){
        temp = &_board[_x + 1][_y - 2];
         --(*temp);
        _back_track[_spaces_moved][7] = temp;
    }

    cout << "possibilities: " << endl;
    for(int i = 0; i < 8; ++i){
        cout << _back_track[_spaces_moved][i] << endl;
        if(_back_track[_spaces_moved][i]){
            cout << "contents: " << *(_back_track[_spaces_moved][i]) << endl;
        }
    }
}
void Tour::possibles_bt() {
    //iterate through most recent (based on _spaces_moved)
        //if location isn't NULL, increment (to offset the decrement in possibles())
        //then set it to NULL
        //by end, all elements in most recent should be reset to NULL
    for(int i = 0; i < 8; ++i){
        if(_back_track[_spaces_moved][i]){
            ++(*(_back_track[_spaces_moved][i]));
            _back_track[_spaces_moved][i] = NULL;
        }
    }
}

bool Tour::search() {
    //decide which possible move will be used (pushed into stack or queue or whatever)

    //now check for smallest as in Warnsdorff's rule
    //as tie-breaker, counter-clockwise
            //order implemented in possibles()
    //if not all possibilities are NULL, will enqueue
        //else if all are NULL, will backtrack

    int count = 8;
    bool is_null = true;
    // Searches through backtracking possibilities
        for(int i = 0; i < 8; ++i){
            //iterating through possibilities
            //if given position exists
            if(_back_track[_spaces_moved][i]){
                //dereff and run wardarf's algorithm
                if(*(_back_track[_spaces_moved][i]) <= count){
                    count = *(_back_track[_spaces_moved][i]);
                    _position = _back_track[_spaces_moved][i];
                    is_null = false;
                }
            }
        }
    return is_null;
}

bool Tour::run_check(bool is_null) {
    bool orig_is_null = is_null;
    // Search function
    switch (is_null){
        case 0:{
            //should make it so the last backtrack in a string of backtracks is returned to the stack
            if(_have_bted){
                *_position = -99;
                _restore_val.enqueue(*_position);
                _path.enqueue(_position);
            }
            _have_bted = false;
            // Updates position of x & y coordinates if they match a valid position on the board
            update_pos();
            //updates _restore_values
            _restore_val.enqueue(*_position);
            // Deferences pointer to space on board in order to set value = 0
            //cuz we've been there now
            *_position = -99;
            // Creates an integer pointer to the position on the board
            //returns that position ptr
            Enqueue(_position);
            if(is_solved()){
                printBoard();
                if(is_closed()){
                    //successful closed tour
                    return true;
                }
                else{
                    //cascade down to next switch case
                    is_null = true;
                }
            }
            else{
                break;
            }
        }
        case 1:{
            //when going back 1, system doesn't recognize that the previous one shouldn't be gone to again
                //so in infinite loop between last two spots************************************************

            _have_bted = true;
            cout << "initiating bt from " << _x << "," << _y << endl;
            cout << "spaces moved: " << _spaces_moved << endl;


            int* temp = _position;
            //if dequeue only once per, crash due to _spaces_moved decremented too many times (array[-1])
            //if dequeue 1 or 2 depending, crash due to _spaces_moved incremented too many times (array[65])
            if(!orig_is_null){
                _position = Dequeue();
                temp = _position;
                possibles_bt();
                *_position = _restore_val.dequeue();
            }
            _position = Dequeue();
            possibles_bt();
            *_position = _restore_val.dequeue();
            --_spaces_moved;
            update_pos();
            cout << "current position: " << "(" << getXPosition() << "," << getYPosition() << ")" << endl;

            for(int i = 0; i < 8; ++i){
                if(_back_track[_spaces_moved][i] == temp){
                    _back_track[_spaces_moved][i] = nullptr;
                }
                else if(_back_track[_spaces_moved][i] == _position){
                    _back_track[_spaces_moved][i] = nullptr;
                }
                cout << _back_track[_spaces_moved][i] << endl;
                if(_back_track[_spaces_moved][i]){
                    cout << "contents: " << *(_back_track[_spaces_moved][i]) << endl;
                }
            }
//            printBoard();

            break;
        }
        default:
            break;
    }
    return false;
}
bool Tour::is_solved(){
    // Loops through board and if there a value that does not equal zero, it is not _solved
    for(int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; j++){
            if (_board[i][j] != -99){
                return false;
            }
        }

    }
    // If all positions on board are zero, it is _solved
    return true;
}


bool Tour::is_closed(){
    possibles();
    for(int i = 0; i < 8; ++i){
        if(_back_track[_spaces_moved][i] == _start_position){
            return true;
        }
    }
    return false;
}

void Tour::Enqueue(int *input) {
    _path.enqueue(input);
    ++_spaces_moved;
    cout << "enqueued " << _x << "," << _y << endl;
}
int* Tour::Dequeue() {
    return _path.dequeue();
}

void Tour::copy(const Tour &other) {
    for(int i = 0; i < 8; ++i){
        for(int j = 0; j < 8; ++j){
            _board[i][j] = other._board[i][j];
        }
    }
    _path = other._path;
    _path = other._path;
    _x = other._x;
    _y = other._y;
    _position = other._position;
    _start_position = other._start_position;
}

void Tour::nukem() {
    delete[] _board;
    _path.clear();
}
// Updates new position on board
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
void Tour::print_location(int *) {
    for(int i = 0; i < 8; ++i){
        for(int j = 0; j < 8; ++j){
            if(_position == &_board[i][j]){
                cout << "(" << i << "," << j << ")" << endl;
            }
        }
    }
}
// Checks to see if coordinates are on board
bool Tour::on_board(int x, int y) {
    if(x < 0 || y < 0){
        return false;
    }
    else if(x >= 8 || y >= 8){
        return false;
    }
        //also check to see if value is 0
            //meaning you can't go there

        // May be dereferencing a null pointer?
    else if(_board[x][y] == -99){
        return false;
    }
    return true;
}
void Tour::printBoard(){
    // Print function in board format
    for(int i = 0; i < 8; ++i){
        std::cout << " " << std::endl;
        for(int j = 0; j < 8; ++j){
            std::cout <<_board[i][j];
        }
    }
    std::cout << std::endl << std::endl;

}
void Tour::q_print() {
    // Print function in standard chess notation

    int x, y;
    int* temp = NULL;

    while (!_path.empty()){
        //search _board for where temp points and save coordinates x, y
        temp = Dequeue();
        for(int a = 0; a < 8; ++a){
            for(int b = 0; b < 8; ++b){
                // If the int pointer is equal to the position of the board
                if(temp == &_board[a][b]){
                    // x & y is assigned to those specific coordinates from the 2D board array
                    x = a;
                    y = b;
                }

            }
        }
        //translate to chess standard notation and print
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
}
void Tour::normal_print() {
    int* temp = NULL;
    int count = 1;

    while (!_path.empty()){
        //search _board for where temp points and save coordinates x, y
        temp = Dequeue();
        for(int a = 0; a < 8; ++a){
            for(int b = 0; b < 8; ++b){
                // If the int pointer is equal to the position of the board
                if(temp == &_board[a][b]){
                    // x & y is assigned to those specific coordinates from the 2D board array
                    cout << count << ": (" << a << "," << b << ")" << endl;
                    ++count;
                }

            }
        }
    }
}