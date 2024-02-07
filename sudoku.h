#ifndef SUDOKU_H // Include guard to prevent multiple inclusions
#define SUDOKU_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <cstdlib>
#include <ctime>
using namespace std;

const int N = 9;
void printGrid(const vector<vector<int>> &grid);
bool isSafe(vector<vector<int>> &grid, int row, int col, int num);
bool solveSudoku(vector<vector<int>> &grid);
void generateRandomBoard(vector<vector<int>> &grid, int numEmptyCells);

#endif