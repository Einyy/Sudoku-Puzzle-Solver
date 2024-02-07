#include "sudoku.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <cstdlib>
#include <ctime>
using namespace std;

void printGrid(const vector<vector<int>> &grid)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }
} // printGrind()

bool isSafe(std::vector<std::vector<int>> &grid, int row, int col, int num)
{
    // Check if the number already exists in the row or column
    for (int x = 0; x < N; x++)
    {
        if (grid[row][x] == num || grid[x][col] == num)
        {
            return false;
        }
    }
    // Check if the number already exists in the 3x3 subgrid
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (grid[i + startRow][j + startCol] == num)
            {

                return false;
            }
        }
    }
    return true;
} // isSafe()

bool solveSudoku(std::vector<std::vector<int>> &grid)
{
    int row, col;
    bool isEmpty = false;
    for (row = 0; row < N; row++)
    {
        for (col = 0; col < N; col++)
        {
            if (grid[row][col] == 0)
            {
                isEmpty = true;
                break;
            }
        }

        if (isEmpty)
        {
            break;
        }
    }

    if (!isEmpty)
    {
        return true;
    }

    vector<int> possibleValues = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    shuffle(possibleValues.begin(), possibleValues.end(), mt19937(random_device()()));
    for (int num : possibleValues)
    {
        if (isSafe(grid, row, col, num))
        {
            grid[row][col] = num;
            if (solveSudoku(grid))
            {
                return true;
            }
            grid[row][col] = 0;
        }
    }
    return false;
} // solveSudoku()

void generateRandomBoard(vector<vector<int>> &grid, int numEmptyCells)
{
    solveSudoku(grid);

    // Get the number of cells in the Sudoku grid
    int totalCells = N * N;

    // Ensure that numEmptyCells is within the valid range
    numEmptyCells = max(0, min(numEmptyCells, totalCells));

    // Shuffle the indices of the cells
    vector<int> indices(totalCells);
    for (int i = 0; i < totalCells; ++i)
    {
        indices[i] = i;
    }
    shuffle(indices.begin(), indices.end(), mt19937(random_device()()));

    // Remove numbers randomly to create the puzzle
    for (int i = 0; i < numEmptyCells; ++i)
    {
        int index = indices[i];
        int row = index / N;
        int col = index % N;
        grid[row][col] = 0;
    }
} // generateRandomBoard()