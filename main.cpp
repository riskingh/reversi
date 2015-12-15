#include <iostream>
#include <fstream>
#include <string>

#include "strategy.h"

using namespace std;

//ofstream logFile;
/*
char cellToChar(int **board, int i, int j) {
    if (board[i][j] == EMPTY)
        return ' ';
    else if (board[i][j] == BLACK)
        return 'B';
    else
        return 'W';
}

void logBoard(int **board) {
    int i, j;
    for (i = 0; i < BOARD_SIZE; ++i) {
        for (j = 0; j < BOARD_SIZE; ++j)
            logFile << cellToChar(board, i, j) << " ";
        logFile << "\n";
    }
}
*/
void opponentMove(int **board, int myColor) {
	char cI, cJ;
	cin >> cI >> cJ;
	int i = (int)(cJ - '1'), j = (int)(cI - 'a');
	addDisc(board, i, j, myColor ^ 1);

	//logFile << "op: " << i << " " << j << " " << (myColor ^ 1) << "\n";
	//logBoard(board);
	//logFile.flush();
}

bool myMove(int **board, int myColor) {
	pair<int, int> move = getMove(board, myColor);
	addDisc(board, move.first, move.second, myColor);

	//logFile << "my: " << move.first << " " << move.second << " " << myColor << "\n";
	//logBoard(board);
	//logFile.flush();

	cout << "move " << (char)(move.second + 'a') << " " << move.first + 1 << "\n";
	cout.flush();
	return true;
}

const int testBoard[][8] = {
	{3, 2, 2, 2, 2, 2, 2, 3},
	{2, 2, 2, 2, 2, 2, 2, 2},
	{2, 2, 2, 2, 2, 2, 2, 2},
	{2, 2, 2, 2, 2, 2, 2, 2},
	{2, 2, 2, 2, 2, 2, 2, 2},
	{2, 2, 2, 2, 2, 2, 2, 2},
	{2, 2, 2, 2, 2, 2, 2, 2},
	{0, 2, 2, 2, 2, 2, 2, 2}
};

int main() {
	//logFile = ofstream("log.txt");

	int **board = initBoard();

	string temp, color;
	cin >> temp >> color;

    //logFile << color << "\n";
    //logFile.flush();

	int myColor = (color == "white" ? WHITE : BLACK);

	while ((cin >> temp) > 0) {
		if (temp == "turn")
			myMove(board, myColor);
		else
			opponentMove(board, myColor);
	}

	/*
	int **board = initBoard();
	for (int i = 0; i < BOARD_SIZE; ++i)
		for (int j = 0; j < BOARD_SIZE; ++j)
			board[i][j] = testBoard[i][j];

	myMove(board, 3);
	*/
	return 0;
}