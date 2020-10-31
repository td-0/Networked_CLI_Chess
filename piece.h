#ifndef PIECE_H
#define PIECE_H

#include <string>
#include <vector>

using namespace std;

class Piece {
private:

    char type;
    char color;
    int moveCount;

    bool inPathOfEnemy(int, int, vector<vector<Piece>>);

    vector<string> getDiagonal(int, int, vector<vector<Piece>>);
    vector<string> getSameLine(int, int, vector<vector<Piece>>);
    vector<string> getLShaped(int, int, vector<vector<Piece>>);
    vector<string> getKingMoves(int, int, vector<vector<Piece>>);
    vector<string> getPawnMoves(int, int, vector<vector<Piece>>);

public:

    Piece();

    Piece( char t, char c );

    char getType();

    void setType(char);

    int getMoveCount();

    void setMoveCount(int);

    char getColor();

    vector<string> getMoves(int, int, vector<vector<Piece>>);

};

#endif
