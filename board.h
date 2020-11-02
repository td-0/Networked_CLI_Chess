#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <iostream>
#include <string>

#include "piece.h"

using namespace std;

class Board {
private:

     vector<vector<Piece>> board_state;

     char currPlayer;

public:

    Board();

    char getCurrPlayer();

    void setCurrPlayer(char);

    void printBoard();

    bool check(char);

    bool stalemate(char);

    bool checkmate(char);

    bool checkMoveValid(string);

    void movePiece(string);

};

#endif
