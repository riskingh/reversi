#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

const int BOARD_SIZE = 8;

// WHITE ^ 1 = BLACK
const int WHITE = 2;
const int BLACK = 3;
const int EMPTY = 0;

// d ^ 1 = opposite direction
const int DIRECTIONS = 8;
const int di[] = {  0,  0,  1, -1,  1, -1,  1, -1   };
const int dj[] = {  1, -1,  1, -1,  0,  0, -1,  1   };

const int INF = (int)1e6;


int **initBoard() {
	int **board = (int **)malloc(sizeof(int *) * BOARD_SIZE);
	for (int i = 0; i < BOARD_SIZE; ++i)
		board[i] = (int *)malloc(sizeof(int) * BOARD_SIZE);

	for (int i = 0; i < BOARD_SIZE; ++i)
		for (int j = 0; j < BOARD_SIZE; ++j)
			board[i][j] = EMPTY;

	board[3][3] = board[4][4] = WHITE;
	board[3][4] = board[4][3] = BLACK;

	return board;
}

void printBoard(int **board) {
	for (int i = 0; i < BOARD_SIZE; ++i) {
		for (int j = 0; j < BOARD_SIZE; ++j) {
			if (board[i][j] == EMPTY)
				cout << ". ";
			else
				cout << (board[i][j] == WHITE ? "W " : "B ");
		}
		cout << "\n";
	}
}

bool onBoard(int i, int j) {
	return (0 <= i && i < BOARD_SIZE) && (0 <= j && j < BOARD_SIZE);
}

void addDisc(int **board, int i, int j, int color) {
	int ni, nj;
	for (int d = 0; d < 8; ++d) {
		board[i][j] = color ^ 1;
		for (ni = i, nj = j; 
			onBoard(ni, nj) && board[ni][nj] == (color ^ 1);
			ni += di[d], nj += dj[d])
			;
		if (onBoard(ni, nj) && board[ni][nj] == color) {
			for (ni = i, nj = j;
				board[ni][nj] == (color ^ 1);
				ni += di[d], nj += dj[d])
				board[ni][nj] = color;
		}
	}
	board[i][j] = color;
}

bool possibleMove(int **board, int i, int j, int color) {
	if (board[i][j] != EMPTY)
		return false;
	int ni, nj;
	bool possible = false;
	for (int d = 0; d < 8; ++d) {
		board[i][j] = color ^ 1;
		for (ni = i, nj = j; 
			onBoard(ni, nj) && board[ni][nj] == (color ^ 1);
			ni += di[d], nj += dj[d])
			;
		possible |= (onBoard(ni, nj) && board[ni][nj] == color && max(abs(ni - i), abs(nj - j)) > 1);
		if (possible)
			break;
	}
	board[i][j] = EMPTY;
	return possible;
}

int **copyBoard(int **board) {
	int **newBoard = initBoard();
	for (int i = 0; i < BOARD_SIZE; ++i)
		for (int j = 0; j < BOARD_SIZE; ++j)
			newBoard[i][j] = board[i][j];
	return newBoard;
}

void copyBoard(int **fromBoard, int **toBoard) {
	for (int i = 0; i < BOARD_SIZE; ++i)
		for (int j = 0; j < BOARD_SIZE; ++j)
			toBoard[i][j] = fromBoard[i][j];
}