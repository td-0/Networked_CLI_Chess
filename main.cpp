#include <iostream>
#include <string>

#include "board.h"
#include "network.h"

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

        cout << endl << "Move Not On Board. Please Enter Another Move: " << endl;
        cin >> moveFrom >> moveTo;

        from_col_id = moveFrom.at(0);
        from_row_id = moveFrom.at(1);
        to_col_id = moveTo.at(0);
        to_row_id = moveTo.at(1);

    }

    string move = moveFrom + moveTo;
    return move;

}

string promptMoveRemote( char currPlayer, Network remote) {

    // Prompt move in a networked game

    string moveFrom, moveTo;

    // Prompt Player for Move
    if ( currPlayer == 'w' ) {

        // Tell Client to Wait
        remote.sendOut("Waiting for Other Player...\n\n");

        // Prompt Host for Move
        cout << "Your Move:\n";
        cin >> moveFrom >> moveTo;

        while (moveFrom.length() != 2 || moveTo.length() != 2) {
            cout << endl << "Not a Valid Move. Please try again: " << endl << endl;
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

            cout << endl << "Move Not On Board. Please Enter Another Move: " << endl;
            cin >> moveFrom >> moveTo;

            from_col_id = moveFrom.at(0);
            from_row_id = moveFrom.at(1);
            to_col_id = moveTo.at(0);
            to_row_id = moveTo.at(1);

        }

    }

    else {

        // Tell Host to Wait
        cout << "Waiting for Other Player..." << endl << endl;

        // Prompt Client for Move
        remote.sendOut("Your Move:\n");

        moveFrom = remote.receiveIn();
        while (moveFrom.length() != 2)
            moveFrom = remote.receiveIn();

        moveTo = remote.receiveIn();
        while (moveTo.length() != 2)
            moveTo = remote.receiveIn();


        while (moveFrom.length() != 2 || moveTo.length() != 2) {
            remote.sendOut("\nNot a Valid Move. Please try again:\n\n");

            moveFrom = remote.receiveIn();
            while (moveFrom.length() != 2)
                moveFrom = remote.receiveIn();

            moveTo = remote.receiveIn();
            while (moveTo.length() != 2)
                moveTo = remote.receiveIn();

            }

        remote.sendOut("\n");

        // Display Error for Attempted Off-Board Move
        char from_col_id = moveFrom.at(0);
        char from_row_id = moveFrom.at(1);
        char to_col_id = moveTo.at(0);
        char to_row_id = moveTo.at(1);

        while ( from_col_id < 'a' || from_col_id > 'h' ||
        to_col_id < 'a' || to_col_id > 'h' ||
        from_row_id < '1' || from_row_id > '8' ||
        to_row_id < '1' || to_row_id > '8' ) {

            remote.sendOut("\nMove Not On Board. Please Enter Another Move:\n");

            moveFrom = remote.receiveIn();

            while (moveFrom.length() != 2)
                moveFrom = remote.receiveIn();

            moveTo = remote.receiveIn();
            while (moveTo.length() != 2)
                moveTo = remote.receiveIn();

            remote.sendOut("\n");

            from_col_id = moveFrom.at(0);
            from_row_id = moveFrom.at(1);
            to_col_id = moveTo.at(0);
            to_row_id = moveTo.at(1);

        }

    }

    string move = moveFrom + moveTo;
    return move;

}


void runOnlineHost() {

    // If player hosts a game

    Network remote;

    remote.createServer();

    Board play_board;


    for (;;) {

        cout << endl;
        play_board.printBoard();
        cout << endl;

        // Send board to client
        vector<string> vec = play_board.boardToVector();
        for ( auto& iter : vec ) {
            remote.sendOut(iter);
        }
        remote.sendOut("\n");


        // Check for Stalemate
        if (play_board.stalemate(play_board.getCurrPlayer())) {
            cout << "Stalemate." << endl << endl;
            remote.sendOut("Stalemate.\n\n");
            exit(0);
        }

        // Check for check and checkmate
        if (play_board.getCurrPlayer() == 'w') {

            if (play_board.checkmate('w')) {
                cout << "Checkmate! You Lose." << endl << endl;
                remote.sendOut("Checkmate! You Win!\n\n");
                exit(0);
            }

            if (play_board.check('w')) {
                cout << "Your King is in Check." << endl << endl;
                remote.sendOut("You Check White's King.\n\n");
            }

        }


        if (play_board.getCurrPlayer() == 'b') {

            if (play_board.checkmate('b')) {
                cout << "Checkmate! You Win!" << endl << endl;
                remote.sendOut("Checkmate! You Lose.\n\n");
                exit(0);
            }

            if (play_board.check('b')) {
                cout << "You Check Black's King." << endl << endl;
                remote.sendOut("Your King is in Check.\n\n");
            }

        }


        // Prompt player move
        string move = promptMoveRemote(play_board.getCurrPlayer(), remote);

        // See if player move is valid
        while ((move.length() != 4) || !play_board.checkMoveValid(move)) {

            if (play_board.getCurrPlayer() == 'w') {
                cout << endl << "Invalid Move: Please Enter Another" << endl << endl;
                move = promptMoveRemote(play_board.getCurrPlayer(), remote);
            }

            else {
                remote.sendOut("\nInvalid Move: Please Enter Another\n\n");
                move = promptMoveRemote(play_board.getCurrPlayer(), remote);
            }

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


void runOnlineClient() {

    // If player joins a game

    string ip_address;

    cout << endl << "Please Enter Another Player's IP Address:" << endl << endl;
    cin >> ip_address;

    // Create network client
    Network remote = Network(ip_address);

    remote.createClient();

    Board play_board;


    for (;;) {

        // Receieve information from host
        string prompt = remote.receiveIn();

        cout << prompt;

        if (prompt.find("Your Move:") != string::npos || prompt.find("Not a Valid Move. Please try again:") != string::npos
        || prompt.find("Move Not On Board. Please Enter Another Move:") != string::npos) {

            // Send information if it's player's move
            string moveFrom, moveTo;
            cin >> moveFrom >> moveTo;
            remote.sendOut(moveFrom);
            remote.sendOut(moveTo);

        }

    }

}


int main() {

    // Starting Menu

    char menuSelection;

    cout << endl << "Welcome to Command Line Chess!" << endl;

    while (menuSelection != 'p' && menuSelection != 'o') {

        if (menuSelection == 'h') {
            cout << endl << "This is a two player chess game." << endl << endl;
            cout << "When prompted, enter you move in the following format:" << endl;
            cout << "Origin_Square Destination_Square" << endl;
            cout << "Example: To move the leftmost pawn forward two spaces: a1 a3" << endl;
            cout << endl << "The game ends when a checkmate or stalemate is reached" << endl;
            cout << endl << "Castling may be done only by moving the king" << endl;
            cout << endl << "Online play is supported." << endl;
            cout << "To play online, one player must host and another must join" << endl;
            cout << "by entering the host's IP Address" << endl;
        }

        if (menuSelection == 'q')
            exit(0);

        cout << endl << "Press (p) to Play a Local Game, (o) to Play an Online Game,";
        cout<< " (h) for Help, or (q) to Quit the Game." << endl << endl;

        cin >> menuSelection;
    }


    if (menuSelection == 'o') {

        char networkChoice = 'n';


        while (networkChoice != 'h' && networkChoice != 'j') {
            cout << endl << "Press (h) to Host a Game or (j) to Join a Game: " << endl << endl;
            cin >> networkChoice;
        }

        // Player is Hosting Game
        if (networkChoice == 'h') {
            runOnlineHost();
        }

        // Player is Joining Game
        if (networkChoice == 'j') {
            runOnlineClient();
        }

    }


    if (menuSelection == 'p') {

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

}
