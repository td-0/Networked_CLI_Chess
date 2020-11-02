#include "board.h"

using namespace std;


Board::Board() {

    // Set up standard chessboard

    for ( int row_iter = 0; row_iter < 8; row_iter++ )
        board_state.push_back({});

    board_state[0].push_back(Piece('r', 'b'));
    board_state[0].push_back(Piece('k', 'b'));
    board_state[0].push_back(Piece('b', 'b'));
    board_state[0].push_back(Piece('q', 'b'));
    board_state[0].push_back(Piece('K', 'b'));
    board_state[0].push_back(Piece('b', 'b'));
    board_state[0].push_back(Piece('k', 'b'));
    board_state[0].push_back(Piece('r', 'b'));

    for ( int b_iter = 0; b_iter < 8; b_iter++ )
        board_state[1].push_back(Piece('p', 'b'));

    for ( int mid_iter = 2; mid_iter < 6; mid_iter++ ) {
        for ( int col_iter = 0; col_iter < 8; col_iter++ )
            board_state[mid_iter].push_back(Piece());
    }

    for ( int w_iter = 0; w_iter < 8; w_iter++ )
        board_state[6].push_back(Piece('p', 'w'));

    board_state[7].push_back(Piece('r', 'w'));
    board_state[7].push_back(Piece('k', 'w'));
    board_state[7].push_back(Piece('b', 'w'));
    board_state[7].push_back(Piece('q', 'w'));
    board_state[7].push_back(Piece('K', 'w'));
    board_state[7].push_back(Piece('b', 'w'));
    board_state[7].push_back(Piece('k', 'w'));
    board_state[7].push_back(Piece('r', 'w'));

    currPlayer = 'w';

}


char Board::getCurrPlayer() {
    return currPlayer;
}


void Board::setCurrPlayer(char player) {
    currPlayer = player;
}


void Board::printBoard() {

    cout << "      a  b  c  d  e  f  g  h" << endl << endl << endl;
    for ( unsigned int iter1 = 0; iter1 < board_state.size(); iter1++ ) {
        cout << " " << 8 - iter1 << "    ";
        for ( unsigned int iter2 = 0; iter2 < board_state[iter1].size();
        iter2++ ) {
            if ( board_state[iter1][iter2].getColor() == 'w' ) {
                if ( board_state[iter1][iter2].getType() == 'K' )
                    cout << board_state[iter1][iter2].getType();
                else
                    cout << char(board_state[iter1][iter2].getType() - 32);
                cout << "  ";
            }
            else
                cout << board_state[iter1][iter2].getType() << "  ";
        }
        cout << "  " << 8 - iter1 << endl << endl;
    }
    cout << endl << "      a  b  c  d  e  f  g  h" << endl;

}


bool Board::check(char kingColor) {

    // Determine if king of specified color is in check

    Piece king;
    string kingPos;

    char enemyColor;
    if(kingColor == 'w')
        enemyColor = 'b';
    else
        enemyColor = 'w';

    // Find Specified King on Board
    for (unsigned int iter1 = 0; iter1 < board_state.size(); iter1++) {
        for (unsigned int iter2 = 0; iter2 < board_state.at(iter1).size(); iter2++) {

            Piece curr = board_state.at(iter1).at(iter2);

            if (curr.getColor() == kingColor && curr.getType() == 'K') {
                king = curr;
                kingPos = to_string(iter1) + to_string(iter2);
                break;
                break;
            }

        }
    }

    // Check if King is being attacked by any enemy piece
    for (unsigned int iter1 = 0; iter1 < board_state.size(); iter1++) {
        for (unsigned int iter2 = 0; iter2 < board_state.at(iter1).size(); iter2++) {

            Piece curr = board_state.at(iter1).at(iter2);

            if (curr.getColor() == enemyColor) {
                vector<string> enemyMoves = curr.getMoves(iter1, iter2, board_state);

                for (unsigned int moveIter = 0; moveIter < enemyMoves.size(); moveIter++) {

                    if (enemyMoves.at(moveIter) == kingPos)
                        return true;

                }

            }

        }
    }
    return false;

}



bool Board::stalemate(char kingColor) {
    // Determine if the game has reached a stalemate

    if (check(kingColor))
        return false;

    for (unsigned int iter1 = 0; iter1 < board_state.size(); iter1++) {
        for (unsigned int iter2 = 0; iter2 < board_state.at(iter1).size(); iter2++) {

            Piece curr = board_state.at(iter1).at(iter2);

            if (curr.getColor() == kingColor && curr.getType() == 'K') {

                if (curr.getMoves(iter1, iter2, board_state).empty())
                    return true;
                else
                    return false;
            }

        }
    }
    return true;
}


bool Board::checkmate(char kingColor) {

    // Determine if king of specified color is in checkmate

    if (!check(kingColor))
        return false;

    // Determine if any friendly piece can break check
    for (unsigned int iter1 = 0; iter1 < board_state.size(); iter1++) {
        for (unsigned int iter2 = 0; iter2 < board_state.at(iter1).size(); iter2++) {

            Piece curr = board_state.at(iter1).at(iter2);

            if (curr.getColor() == kingColor) {

                vector<string> possibleMoves = curr.getMoves(iter1, iter2, board_state);

                for (unsigned int iter = 0; iter < possibleMoves.size(); iter++) {

                    string possibleMove = possibleMoves.at(iter);

                    // Convert moves from getMoves() into the format
                    // in which they are entered by player so as to
                    // reuse checkMoveValid() function

                    char from_col = iter2 + 97;
                    char from_row = 8 + iter1 + '0';
                    char to_col = possibleMove.at(1) + '1';
                    char to_row = '8' - possibleMove.at(0) + '0';

                    string move;
                    move.append(1, from_col);
                    move.append(1, from_row);
                    move.append(1, to_col);
                    move.append(1, to_row);

                    if (checkMoveValid(move))
                        return false;
                }

            }

        }
    }
    return true;
}


bool Board::checkMoveValid(string move) {

    // Parse Move
    int from_col = move.at(0) - 97;
    int from_row = 8 - (move.at(1) - '0');
    int to_col = move.at(2) - 97;
    int to_row = 8 - (move.at(3) - '0');

    Piece selected = board_state.at(from_row).at(from_col);

    if (currPlayer != selected.getColor()) {
        return false;
    }

    // Check for Illegal Move of Capturing the King
    if (board_state.at(to_row).at(to_col).getType() == 'K')
        return false;

    vector<string> moveSet = selected.getMoves(from_row, from_col, board_state);

    string playerMove;
    playerMove += to_string(to_row);
    playerMove += to_string(to_col);

    for (auto& iter : moveSet) {
        // Check if move is in Piece's move set

        if (iter == playerMove) {

            // Ensure that Player is Breaking Check if necessary
            if (check(currPlayer)) {

                // Simulate Move on Duplicate Board State
                vector<vector<Piece>> afterMove(board_state);

                Piece tempSelected = afterMove.at(from_row).at(from_col);

                Piece tempDestination = afterMove.at(to_row).at(to_col);

                // Cannot castle out of check
                if (selected.getType() == 'K' && to_col == from_col + 2) {
                    // Castle King Side
                    return false;
                }

                else if (selected.getType() == 'K' && to_col == from_col - 2) {
                    // Castle Queen Side
                    return false;
                }

                if (tempSelected.getType() == 'p' && ((from_row == 3 && to_row == 2) ||
                (from_row == 4 && to_row == 5)) && (to_col == from_col - 1 ||
                to_col == from_col + 1) && tempDestination.getType() == 'x') {
                    // En Passant

                    afterMove.at(to_row).at(to_col) = tempSelected;
                    afterMove.at(from_row).at(from_col) = Piece('x', 'e');

                    afterMove.at(from_row).at(to_col) = Piece('x', 'e');

                }

                else if (tempDestination.getType() != 'x') {
                    afterMove.at(to_row).at(to_col) = tempSelected;
                    afterMove.at(from_row).at(from_col) = Piece('x', 'e');
                }

                else {
                    afterMove.at(to_row).at(to_col) = tempSelected;
                    afterMove.at(from_row).at(from_col) = tempDestination;
                }

                // Determine if still in check after move
                Piece king;
                string kingPos;

                char enemyColor;
                if(currPlayer == 'w')
                    enemyColor = 'b';
                else
                    enemyColor = 'w';

                // Find King
                for (unsigned int iter1 = 0; iter1 < afterMove.size(); iter1++) {
                    for (unsigned int iter2 = 0; iter2 < afterMove.at(iter1).size(); iter2++) {

                        Piece curr = afterMove.at(iter1).at(iter2);

                        if (curr.getColor() == currPlayer && curr.getType() == 'K') {
                            king = curr;
                            kingPos = to_string(iter1) + to_string(iter2);
                            break;
                            break;
                        }

                    }
                }

                // Check if King is being attacked by any enemy piece
                for (unsigned int iter1 = 0; iter1 < afterMove.size(); iter1++) {
                    for (unsigned int iter2 = 0; iter2 < afterMove.at(iter1).size(); iter2++) {

                        Piece curr = afterMove.at(iter1).at(iter2);

                        if (curr.getColor() == enemyColor) {
                            vector<string> enemyMoves = curr.getMoves(iter1, iter2, afterMove);
                            for (unsigned int moveIter = 0; moveIter < enemyMoves.size(); moveIter++) {
                                if (enemyMoves.at(moveIter) == kingPos)
                                    return false;
                            }
                        }

                    }
                }
            }
            return true;
        }

    }
    return false;

}


void Board::movePiece(string move) {

    // Parse Move
    int from_col = move.at(0) - 97;
    int from_row = 8 - (move.at(1) - '0');
    int to_col = move.at(2) - 97;
    int to_row = 8 - (move.at(3) - '0');

    Piece selected = board_state.at(from_row).at(from_col);

    Piece destination = board_state.at(to_row).at(to_col);


    if (selected.getType() == 'K' && to_col == from_col + 2) {
        // Castle King Side
        board_state.at(to_row).at(to_col) = selected;
        board_state.at(from_row).at(from_col) = destination;

        Piece rook = board_state.at(from_row).at(from_col + 3);
        Piece rookTo = board_state.at(from_row).at(from_col + 1);
        board_state.at(from_row).at(from_col + 1) = rook;
        board_state.at(from_row).at(from_col + 3) = rookTo;
    }

    else if (selected.getType() == 'K' && to_col == from_col - 2) {
        // Castle Queen Side
        board_state.at(to_row).at(to_col) = selected;
        board_state.at(from_row).at(from_col) = destination;

        Piece rook = board_state.at(from_row).at(from_col - 4);
        Piece rookTo = board_state.at(from_row).at(from_col - 1);
        board_state.at(from_row).at(from_col - 1) = rook;
        board_state.at(from_row).at(from_col - 4) = rookTo;
    }

    else if (selected.getType() == 'p' && ((from_row == 3 && to_row == 2) ||
    (from_row == 4 && to_row == 5)) && (to_col == from_col - 1 ||
    to_col == from_col + 1) && destination.getType() == 'x') {
        // En Passant

        board_state.at(to_row).at(to_col) = selected;
        board_state.at(from_row).at(from_col) = Piece('x', 'e');

        board_state.at(from_row).at(to_col) = Piece('x', 'e');

    }

    else if (destination.getType() != 'x') {
        // Taking enemy piece

        board_state.at(to_row).at(to_col) = selected;
        board_state.at(from_row).at(from_col) = Piece('x', 'e');
    }

    else {
        // Moving to empty space

        board_state.at(to_row).at(to_col) = selected;
        board_state.at(from_row).at(from_col) = destination;
    }


    // Trade Pawn if it reaches enemy side
    if (selected.getType() == 'p') {
        if ((selected.getColor() == 'w' && to_row == 0) ||
        (selected.getColor() == 'b' && to_row == 7)) {
            char tradeType;
            cout << endl << "Trade Pawn for Queen (q), Bishop (b), Knight (k), "
            << "or Rook (r):" << endl << endl;
            cin >> tradeType;
            cout << endl;

            while (tradeType != 'q' && tradeType != 'b' && tradeType != 'k' &&
            tradeType != 'r') {
                cout << endl << "Not a valid trade piece. Please enter another" << endl << endl;
                cin >> tradeType;
                cout << endl;
            }

            board_state.at(to_row).at(to_col).setType(tradeType);

        }
    }

    // Increase selected piece's move count
    int moveCount = board_state.at(to_row).at(to_col).getMoveCount();
    board_state.at(to_row).at(to_col).setMoveCount(moveCount + 1);

}
