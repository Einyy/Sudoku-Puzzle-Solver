#include <iostream>
#include "sudoku.h"
#include <vector>
#include <algorithm>
#include <random>
#include <ctime>
using namespace std;

int main()
{

    srand(time(nullptr));
    
    int difficultyLevel;
    int numEmptyCells;
    cout << "Select difficulty level (1: Easy, 2: Medium, 3: Hard): ";
    cin >> difficultyLevel;
    
    if (difficultyLevel < 1 || difficultyLevel > 3)
    {
        cout << "Invalid difficulty level. Defaulting to medium." << endl;
        numEmptyCells = 40; // Default to medium difficulty
    }
    
    switch (difficultyLevel)
    {
    case 1:
        numEmptyCells = 30; // Adjust these values based on your preference
        break;
    case 2:
        numEmptyCells = 40;
        break;
    case 3:
        numEmptyCells = 50;
        break;
    default:
        numEmptyCells = 40; // Default to medium difficulty
        break;
    }

    vector<vector<int>> grid(N, vector<int>(N, 0));
    generateRandomBoard(grid, numEmptyCells);
    printGrid(grid);

    return 0;
} // int main()