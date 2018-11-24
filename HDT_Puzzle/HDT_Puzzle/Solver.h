#pragma once
#include "CommonDef.h"
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solver {
private:

	//남 남서 서 북서 북 북동 동 남동
	int puzzle_row, puzzle_col;
	int** puzzle;
	int max;
	INT_PAIR start;
	INT_PAIR end;
	vector<pair<int, pair<int, int> > > hint;
	bool isEnd;
	int zero_count;
	float** wei_puzzle1;
	float** wei_puzzle2;
	float** weight_puzzle;

public:

	Solver(int row, int col);
	void setSolPuzzle(int** gen_puzzle);
	void setWeightPuzzle(int** gen_puzzle,float** wei_puzzle1);
	void setWeightPuzzle(float** wei_puzzle1,float** wei_puzzle2);
	void solveWeightpuzzle(const int& x, const int& y, int& step, int& hint_idx, bool& isHint);
	//void ShowWeightPuzzle(); TO DO
	void ShowPuzzle();
	void ShowWeightPuzzle();
	void ShowHint();
	void Solve(const int& x, const int& y, int step, int hint_idx, bool isHint);
	int getMax();
	INT_PAIR getStart();
	INT_PAIR getEnd();
	void Initiate();
};