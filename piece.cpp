#include "piece.h"

using namespace std;

Piece::Piece() {
    type = 'x';
    color = 'e';
    moveCount = 0;
}

Piece::Piece( char t, char c ) {
    type = t;
    color = c;
    moveCount = 0;
}


// Private
bool Piece::inPathOfEnemy(int row, int col, vector<vector<Piece>> board) {
    string squareToCheck = to_string(row) + to_string(col);

    char enemyColor;
    if(color == 'w')
        enemyColor = 'b';
    else
        enemyColor = 'w';

    for (unsigned int iter1 = 0; iter1 < board.size(); iter1++) {
        for (unsigned int iter2 = 0; iter2 < board.at(iter1).size(); iter2++) {
            Piece curr = board.at(iter1).at(iter2);
            if (curr.getColor() == enemyColor && curr.getType() != 'K') {
                vector<string> enemyMoves = curr.getMoves(iter1, iter2, board);
                for (unsigned int moveIter = 0; moveIter < enemyMoves.size(); moveIter++) {
                    if (enemyMoves.at(moveIter) == squareToCheck) {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}


vector<string> Piece::getDiagonal(int row, int col, vector<vector<Piece>> board) {
    vector<string> moves;
    string move;

    char enemyColor;
    if(color == 'w')
        enemyColor = 'b';
    else
        enemyColor = 'w';

    int col_id = 1;
    int iter = row - 1;
    bool obstacle1 = false;
    bool obstacle2 = false;
    while(iter >= 0) {

        if (col + col_id < 8) {
            // Cuts off possible spaces at friendly piece
            if (board.at(iter).at(col + col_id).getColor() == color)
                obstacle1 = true;

            if (obstacle1 == false) {
                move.clear();
                move += to_string(iter);
                move += to_string(col + col_id);
                moves.push_back(move);
            }

            // Cuts off possible spaces after enemy piece
            if (board.at(iter).at(col + col_id).getColor() == enemyColor)
                obstacle1 = true;
        }

        if (col - col_id >= 0) {
            // Cuts off possible spaces at friendly piece
            if (board.at(iter).at(col - col_id).getColor() == color)
                obstacle2 = true;

            if (obstacle2 == false) {
                move.clear();
                move += to_string(iter);
                move += to_string(col - col_id);
                moves.push_back(move);
            }

            // Cuts off possible spaces after enemy piece
            if (board.at(iter).at(col - col_id).getColor() == enemyColor)
                obstacle2 = true;
        }

        iter--;
        col_id++;
    }

    col_id = 1;
    iter = row + 1;
    obstacle1 = false;
    obstacle2 = false;
    while(iter < 8) {

        if (col + col_id < 8) {
            // Cuts off possible spaces at friendly piece
            if (board.at(iter).at(col + col_id).getColor() == color)
                obstacle1 = true;

            if (obstacle1 == false) {
                move.clear();
                move += to_string(iter);
                move += to_string(col + col_id);
                moves.push_back(move);
            }

            // Cuts off possible spaces after enemy piece
            if (board.at(iter).at(col + col_id).getColor() == enemyColor)
                obstacle1 = true;
        }

        if (col - col_id >= 0) {
            // Cuts off possible spaces at friendly piece
            if (board.at(iter).at(col - col_id).getColor() == color)
                obstacle2 = true;

            if (obstacle2 == false) {
                move.clear();
                move += to_string(iter);
                move += to_string(col - col_id);
                moves.push_back(move);
            }

            // Cuts off possible spaces after enemy piece
            if (board.at(iter).at(col - col_id).getColor() == enemyColor)
                obstacle2 = true;
        }

        iter++;
        col_id++;
    }

    return moves;
}


vector<string> Piece::getSameLine(int row, int col, vector<vector<Piece>> board) {
    vector<string> moves;
    string move;

    char enemyColor;
    if(color == 'w')
        enemyColor = 'b';
    else
        enemyColor = 'w';

    for (int iter = row + 1; iter < 8; iter++) {

        // Cuts off possible spaces at friendly piece
        if (board.at(iter).at(col).getColor() == color)
            break;

        move.clear();
        move += to_string(iter);
        move += to_string(col);
        moves.push_back(move);

        // Cuts off possible spaces after enemy piece
        if (board.at(iter).at(col).getColor() == enemyColor)
            break;
    }

    for (int iter = row - 1; iter >= 0; iter--) {

        // Cuts off possible spaces at friendly piece
        if (board.at(iter).at(col).getColor() == color)
            break;

        move.clear();
        move += to_string(iter);
        move += to_string(col);
        moves.push_back(move);

        // Cuts off possible spaces after enemy piece
        if (board.at(iter).at(col).getColor() == enemyColor)
            break;
    }

    for (int iter = col + 1; iter < 8; iter++) {

        // Cuts off possible spaces at friendly piece
        if (board.at(row).at(iter).getColor() == color)
            break;

        move.clear();
        move += to_string(row);
        move += to_string(iter);
        moves.push_back(move);

        // Cuts off possible spaces after enemy piece
        if (board.at(row).at(iter).getColor() == enemyColor)
            break;
    }

    for (int iter = col - 1; iter >= 0; iter--) {

        // Cuts off possible spaces at friendly piece
        if (board.at(row).at(iter).getColor() == color)
            break;

        move.clear();
        move += to_string(row);
        move += to_string(iter);
        moves.push_back(move);

        // Cuts off possible spaces after enemy piece
        if (board.at(row).at(iter).getColor() == enemyColor)
            break;
    }

    return moves;
}


vector<string> Piece::getLShaped(int row, int col, vector<vector<Piece>> board) {
    vector<string> moves;
    string move;

    if (row < 6) {
        if(col > 0 && board.at(row + 2).at(col - 1).getColor() != color) {
                move += to_string(row + 2);
                move += to_string(col - 1);
                moves.push_back(move);
                move.clear();
        }

        if(col < 7 && board.at(row + 2).at(col + 1).getColor() != color) {
                move += to_string(row + 2);
                move += to_string(col + 1);
                moves.push_back(move);
                move.clear();
        }
    }

    if (row > 1) {
        if(col > 0 && board.at(row - 2).at(col - 1).getColor() != color) {
                move += to_string(row - 2);
                move += to_string(col - 1);
                moves.push_back(move);
                move.clear();
        }

        if(col < 7 && board.at(row - 2).at(col + 1).getColor() != color) {
                move += to_string(row - 2);
                move += to_string(col + 1);
                moves.push_back(move);
                move.clear();
        }
    }

    if (col < 6) {
        if(row > 0 && board.at(row - 1).at(col + 2).getColor() != color) {
                move += to_string(row - 1);
                move += to_string(col + 2);
                moves.push_back(move);
                move.clear();
        }

        if(row < 7 && board.at(row + 1).at(col + 2).getColor() != color) {
                move += to_string(row + 1);
                move += to_string(col + 2);
                moves.push_back(move);
                move.clear();
        }
    }

    if (col > 1) {
        if(row > 0 && board.at(row - 1).at(col - 2).getColor() != color) {
                move += to_string(row - 1);
                move += to_string(col - 2);
                moves.push_back(move);
                move.clear();
        }

        if(row < 7 && board.at(row + 1).at(col - 2).getColor() != color) {
                move += to_string(row + 1);
                move += to_string(col - 2);
                moves.push_back(move);
                move.clear();
        }
    }

    return moves;

}


// Check if piece in way
vector<string> Piece::getKingMoves(int row, int col, vector<vector<Piece>> board) {
    vector<string> moves;
    string move;

    for(int iter1 = -1; iter1 < 2; iter1++) {
        if (row + iter1 >= 0 && row + iter1 < 8) {
            for(int iter2 = -1; iter2 < 2; iter2++) {
                if (col + iter2 >= 0 && col + iter2 < 8) {
                    if (iter1 != 0 or iter2 != 0) {
                            if (!inPathOfEnemy(row + iter1, col + iter2, board)) {
                                move += to_string(row + iter1);
                                move += to_string(col + iter2);
                                moves.push_back(move);
                                move.clear();
                            }
                    }
                }
            }
        }
    }

    // Castling - King Side
    if (moveCount == 0 && board.at(row).at(col + 3).getType() == 'r' &&
    board.at(row).at(col + 3).getColor() == color &&
    board.at(row).at(col + 3).getMoveCount() == 0) {

        // No pieces between king and rook
        if (board.at(row).at(col + 2).getType() == 'x' &&
        board.at(row).at(col + 1).getType() == 'x') {

            // Not in check or passing through check
            if (!inPathOfEnemy(row, col, board) && !inPathOfEnemy(row, col + 1, board)
            && !inPathOfEnemy(row, col + 2, board)) {
        
                move += to_string(row);
                move += to_string(col + 2);
                moves.push_back(move);
                move.clear();

            }
        }
    }

    // Castling - Queen Side
    if (moveCount == 0 && board.at(row).at(col - 4).getType() == 'r' &&
    board.at(row).at(col - 4).getColor() == color &&
    board.at(row).at(col - 4).getMoveCount() == 0) {

        // No pieces between king and rook
        if (board.at(row).at(col - 3).getType() == 'x' &&
        board.at(row).at(col - 2).getType() == 'x' &&
        board.at(row).at(col - 1).getType() == 'x') {

            // Not in check or passing through check
            if (!inPathOfEnemy(row, col, board) && !inPathOfEnemy(row, col - 1, board)
            && !inPathOfEnemy(row, col - 2, board)) {

                move += to_string(row);
                move += to_string(col - 2);
                moves.push_back(move);
                move.clear();

            }
        }
    }

    return moves;
}


vector<string> Piece::getPawnMoves(int row, int col, vector<vector<Piece>> board) {
    vector<string> moves;
    string move;
    char enemyColor;
    if(color == 'w')
        enemyColor = 'b';
    else
        enemyColor = 'w';

    if (color == 'w' && row > 0 && board.at(row - 1).at(col).getColor() != color
    && board.at(row - 1).at(col).getColor() != enemyColor) {
        move += to_string(row - 1);
        move += to_string(col);
        moves.push_back(move);
        move.clear();

        if (row == 6 && board.at(row - 2).at(col).getColor() != color
        && board.at(row - 2).at(col).getColor() != enemyColor) {
            move += to_string(row - 2);
            move += to_string(col);
            moves.push_back(move);
            move.clear();
        }
    }

    if (color == 'b' && row > 0 && board.at(row + 1).at(col).getColor() != color
    && board.at(row + 1).at(col).getColor() != enemyColor) {
        move += to_string(row + 1);
        move += to_string(col);
        moves.push_back(move);
        move.clear();

        if (row == 1 && board.at(row + 2).at(col).getColor() != color &&
        board.at(row + 2).at(col).getColor() != enemyColor) {
            move += to_string(row + 2);
            move += to_string(col);
            moves.push_back(move);
            move.clear();
        }
    }

    // Diagonal move if another piece is there
    if (color == 'w') {
        if (col > 0 && board.at(row - 1).at(col - 1).getColor() == enemyColor) {
            move += to_string(row - 1);
            move += to_string(col - 1);
            moves.push_back(move);
            move.clear();
        }

        if (col < 7 && board.at(row - 1).at(col + 1).getColor() == enemyColor) {
            move += to_string(row - 1);
            move += to_string(col + 1);
            moves.push_back(move);
            move.clear();
        }
    }

    if (color == 'b') {
        if (col > 0 && board.at(row + 1).at(col - 1).getColor() == enemyColor) {
            move += to_string(row + 1);
            move += to_string(col - 1);
            moves.push_back(move);
            move.clear();
        }

        if (col < 7 && board.at(row + 1).at(col + 1).getColor() == enemyColor) {
            move += to_string(row + 1);
            move += to_string(col + 1);
            moves.push_back(move);
            move.clear();
        }
    }

    // Add en passant

    return moves;
}


// Public
char Piece::getType() {
    return type;
}

void Piece::setType(char newType) {
    type = newType;
}

int Piece::getMoveCount() {
    return moveCount;
}

void Piece::setMoveCount(int count) {
    moveCount = count;
}

char Piece::getColor() {
    return color;
}

vector<string> Piece::getMoves(int row, int col, vector<vector<Piece>> board) {
    vector<string> moves;

    switch(type) {
        case 'K': {
            moves = getKingMoves(row, col, board);
            }
            break;
        case 'q': {
            vector<string> same = getSameLine(row, col, board);
            vector<string> diagonal = getDiagonal(row, col, board);
            moves = same;
            moves.insert(moves.end(), diagonal.begin(), diagonal.end());
            }
            break;
        case 'r': {
            moves = getSameLine(row, col, board);
            }
            break;
        case 'k': {
            moves = getLShaped(row, col, board);
            }
            break;
        case 'b': {
            moves = getDiagonal(row, col, board);
            }
            break;
        default: {
            moves = getPawnMoves(row, col, board);
            }
            break;
    }
    return moves;
}
