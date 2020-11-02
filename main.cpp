// TODO: Add network functionality

#include <iostream>
#include <string>

#include "board.h"

using namespace std;

string promptMove( char currPlayer ) {

    string moveFrom, moveTo;

    // Prompt Player for Move
    if ( currPlayer == 'w' )
        cout << "White's ";
    else
        cout << "Black's ";
    cout << "Move: ";
    cin >> moveFrom >> moveTo;

    while (moveFrom.length() != 2 || moveTo.length() != 2) {
        cout << endl << "Not a Valid Move. Please try again: ";
        cin >> moveFrom >> moveTo;
    }

    // Display Error for Attempted Off-Board Move
    char from_col_id = moveFrom.at(0);
    char from_row_id = moveFrom.at(1);
    char to_col_id = moveTo.at(0);
    char to_row_id = moveTo.at(1);

    while ( from_col_id < 'a' || from_col_id > 'h' ||
    to_col_id < 'a' || to_col_id > 'h' ||
    from_row_id < '1' || from_row_id > '8' ||
    to_row_id < '1' || to_row_id > '8' ) {
        cout << endl << "Move Not On Board. Please Enter Another Move: ";
        cin >> moveFrom >> moveTo;
    }

    string move = moveFrom + moveTo;
    return move;

}

int main() {

    // Starting Menu

    char menuSelection;

    cout << endl << "Welcome to Command Line Chess!" << endl;

    while (menuSelection != 'p') {

        if (menuSelection == 'h') {
            cout << endl << "This is a two player chess game." << endl << endl;
            cout << "When prompted, enter you move in the following format:" << endl;
            cout << "Origin_Square Destination_Square" << endl;
            cout << "Example: To move the leftmost pawn forward two spaces: a1 a3" << endl;
            cout << endl << "The game ends when a checkmate or stalemate is reached" << endl;
            cout << endl << "Castling may be done only by moving the king" << endl;
        }

        if (menuSelection == 'q')
            exit(0);

        cout << endl << "Press (p) to Play, (h) for help, or (q) to quit the game" << endl << endl;
        cin >> menuSelection;
    }


    // Create Initial Board and Set First Move as White
    Board play_board;


    // Game Loop
    for(;;) {
        cout << endl;
        play_board.printBoard();
        cout << endl;


        // Check for Stalemate
        if (play_board.stalemate(play_board.getCurrPlayer())) {
            cout << "Stalemate." << endl << endl;
            exit(0);
        }

        // Check for check and checkmate
        if (play_board.getCurrPlayer() == 'w') {

            if (play_board.checkmate('w')) {
                cout << "Checkmate! Black Wins." << endl << endl;
                exit(0);
            }

            if (play_board.check('w')) {
                cout << "White's King is in Check." << endl << endl;
            }

        }


        if (play_board.getCurrPlayer() == 'b') {

            if (play_board.checkmate('b')) {
                cout << "Checkmate! White Wins" << endl << endl;
                exit(0);
            }

            if (play_board.check('b')) {
                cout << "Black's King is in Check." << endl << endl;
            }

        }

        // Prompt player move
        string move = promptMove(play_board.getCurrPlayer());

        // See if player move is valid
        while ((move.length() != 4) || !play_board.checkMoveValid(move)) {
            cout << endl <<"Invalid Move: Please Enter Another" << endl << endl;
            move = promptMove(play_board.getCurrPlayer());
        }

        // Play out move
        play_board.movePiece(move);


        // Change current player for next turn
        if (play_board.getCurrPlayer() == 'w')
            play_board.setCurrPlayer('b');
        else
            play_board.setCurrPlayer('w');
    }


}
