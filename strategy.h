#include "reversi.h"
#include <ctime>
#include <fstream>

const double TL = 2.5;

const int STEPS_MIN = 4;
const int STEPS_MAX = 9;
const int MOVES_COUNT_BORDER = 5;

const int mC = 100000;
const int mS = 20;

const int magicArray[][8] = {
    {  mC, mS, mS, mS, mS, mS, mS,  mC  },
    {  mS,  5,  2,  2,  2,  2,  5,  mS  },
    {  mS,  2,  1,  1,  1,  1,  2,  mS  },
    {  mS,  2,  1,  1,  1,  1,  2,  mS  },
    {  mS,  2,  1,  1,  1,  1,  2,  mS  },
    {  mS,  2,  1,  1,  1,  1,  2,  mS  },
    {  mS,  5,  2,  2,  2,  2,  5,  mS  },
    {  mC, mS, mS, mS, mS, mS, mS,  mC  }
};

clock_t start;

int magicFunction(int **board, int color) {

	int magic = 0, discValue;

	for (int i = 0; i < BOARD_SIZE; ++i) {
		for (int j = 0; j < BOARD_SIZE; ++j) {
            if (board[i][j] == EMPTY) {
            }
            else {
			    discValue = magicArray[i][j] * (board[i][j] == color ? 1 : -1);
                magic += discValue;
            }
		}
	}

	return magic;
}

// even step - my turn, odd step - opponent turn
int gen(int **board, int myColor, int step, int stepLimit, int prevBestScore = -INF) {
	if (step > stepLimit)
		return magicFunction(board, myColor);

	int bestScore = INF * (step % 2 ? 1 : -1), score;
	int **testBoard = initBoard();

	for (int i = 0; i < BOARD_SIZE; ++i) {
		for (int j = 0; j < BOARD_SIZE; ++j) {
			if (!possibleMove(board, i, j, myColor ^ (step % 2)))
				continue;
			copyBoard(board, testBoard);
			addDisc(testBoard, i, j, myColor ^ (step % 2));
			score = gen(testBoard, myColor, step + 1, stepLimit, bestScore);
            if (step % 2) {
			    bestScore = min(bestScore, score);
                if (bestScore < prevBestScore) {
                    delete testBoard;
                    return bestScore;
                }
            }
            else {
                bestScore = max(bestScore, score);
                if (bestScore > prevBestScore) {
                    delete testBoard;
                    return bestScore;
                }
            }
		}
        if ((double)(clock() - start) / (double)CLOCKS_PER_SEC > TL)
            break;
	}

    delete testBoard;

	// sometimes, there's nothing you can do
	//if (bestScore == -INF || bestScore == INF)
		//bestScore = magicFunction(board, myColor);

	return bestScore;
}

pair<int, int> getMove(int **board, int myColor) {
    start = clock();

	int bestScore = -INF, score;
	pair<int, int> bestMove(-1, -1);

	int **testBoard = initBoard();

    int possibleMovesCount = 0;
    for (int i = 0; i < BOARD_SIZE; ++i)
        for (int j = 0; j < BOARD_SIZE; ++j)
            possibleMovesCount += (int)possibleMove(board, i, j, myColor);

    int stepsCount = STEPS_MIN;
    if (possibleMovesCount < MOVES_COUNT_BORDER)
        stepsCount = STEPS_MAX;


	for (int i = 0; i < BOARD_SIZE; ++i) {
		for (int j = 0; j < BOARD_SIZE; ++j) {
			if (!possibleMove(board, i, j, myColor))
				continue;
			copyBoard(board, testBoard);
			addDisc(testBoard, i, j, myColor);
			score = gen(testBoard, myColor, 1, stepsCount);
			if (score > bestScore || bestMove.first == -1) {
				bestScore = score;
				bestMove.first = i;
				bestMove.second = j;
			}
		}
	}

    delete testBoard;

	return bestMove;
}