#include <iostream>
using namespace std;

bool isWon(char, char[][3]);
bool isDraw(char[][3]);
void displayBoard(char[][3]);
void makeAMove(char[][3], char);

int main() {
    //
    //	PLEASE DO NOT CHANGE function main
    //
    char board[3][3] = { { ' ', ' ', ' ' },{ ' ', ' ', ' ' },{ ' ', ' ', ' ' } };
    displayBoard(board);

    while (true) {
        // The first player makes a move
        makeAMove(board, 'X');
        displayBoard(board);
        if (isWon('X', board)) {
            cout << "X player won" << endl;
            exit(0);
        }
        else if (isDraw(board)) {
            cout << "No winner" << endl;
            exit(0);
        }

        // The second player makes a move
        makeAMove(board, 'O');
        displayBoard(board);

        if (isWon('O', board)) {
            cout << "O player won" << endl;
            exit(0);
        }
        else if (isDraw(board)) {
            cout << "No winner" << endl;
            exit(0);
        }
    }

    return 0;
}

void displayBoard(char board[][3]) {
    cout << "\n-------------\n"
         << "| " << board[0][0] << " | " << board[0][1] << " | " << board[0][2] << " |\n"
         << "-------------\n"
         << "| " << board[1][0] << " | " << board[1][1] << " | " << board[1][2] << " |\n"
         << "-------------\n"
         << "| " << board[2][0] << " | " << board[2][1] << " | " << board[2][2] << " |\n"
         << "-------------\n";
}

bool isWon(char winner, char board[][3]) {
    if(board[0][0] == winner && board[1][1] == winner && board[2][2] == winner)
        return true;
    if(board[0][2] == winner && board[1][1] == winner && board[2][0] == winner)
        return true;
    for(int i = 0; i < 3; i++) {
        if(board[0][i] == winner && board[1][i] == winner && board[2][i] == winner)
            return true;
        if(board[i][0] == winner && board[i][1] == winner && board[i][2] == winner)
            return true;
    }
    return false;
}

bool isDraw(char board[][3]) {
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            if(board[i][j] == ' ')
                return false;
    if(!isWon('0', board) && !isWon('X', board))
        return true;
    else
        return false;
}

void makeAMove(char board[][3], char move) {
    int row, col;

    cout << "Enter a row (0, 1, 2) for player " << move << "   : ";
    cin >> row;

    cout << "Enter a column (0, 1, 2) for player " << move << ": ";
    cin >> col;

    board[row-1][col-1] = move;
}

