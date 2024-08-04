#include <iostream>
using namespace std;

// Function to print the grid
void printGrid(int grid[9][9]) {
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++)
            cout << grid[row][col] << " ";
        cout << endl;
    }
}

// Function to find an empty location in the grid
bool findEmptyLocation(int grid[9][9], int &row, int &col) {
    for (row = 0; row < 9; row++)
        for (col = 0; col < 9; col++)
            if (grid[row][col] == 0)
                return true;
    return false;
}

// Function to check if a number is used in the specified row
bool usedInRow(int grid[9][9], int row, int num) {
    for (int col = 0; col < 9; col++)
        if (grid[row][col] == num)
            return true;
    return false;
}

// Function to check if a number is used in the specified column
bool usedInCol(int grid[9][9], int col, int num) {
    for (int row = 0; row < 9; row++)
        if (grid[row][col] == num)
            return true;
    return false;
}

// Function to check if a number is used in the specified 3x3 box
bool usedInBox(int grid[9][9], int boxStartRow, int boxStartCol, int num) {
    for (int row = 0; row < 3; row++)
        for (int col = 0; col < 3; col++)
            if (grid[row + boxStartRow][col + boxStartCol] == num)
                return true;
    return false;
}

// Function to check if it is safe to place a number in the specified location
bool isSafe(int grid[9][9], int row, int col, int num) {
    return !usedInRow(grid, row, num) &&
           !usedInCol(grid, col, num) &&
           !usedInBox(grid, row - row % 3, col - col % 3, num);
}

// Function to solve the Sudoku puzzle using backtracking
bool solveSudoku(int grid[9][9]) {
    int row, col;
    if (!findEmptyLocation(grid, row, col))
        return true; // Success!

    for (int num = 1; num <= 9; num++) {
        if (isSafe(grid, row, col, num)) {
            grid[row][col] = num;
            if (solveSudoku(grid))
                return true;
            grid[row][col] = 0; // Failure, undo & try again
        }
    }
    return false; // Triggers backtracking
}

int main() {
    // Example Sudoku puzzle (0 represents empty cells)
    int grid[9][9] = {
        {3, 0, 6, 5, 0, 8, 4, 0, 0},
        {5, 2, 0, 0, 0, 0, 0, 0, 0},
        {0, 8, 7, 0, 0, 0, 0, 3, 1},
        {0, 0, 3, 0, 1, 0, 0, 8, 0},
        {9, 0, 0, 8, 6, 3, 0, 0, 5},
        {0, 5, 0, 0, 9, 0, 6, 0, 0},
        {1, 3, 0, 0, 0, 0, 2, 5, 0},
        {0, 0, 0, 0, 0, 0, 0, 7, 4},
        {0, 0, 5, 2, 0, 6, 3, 0, 0}
    };

    if (solveSudoku(grid)) {
        cout << "Sudoku solved successfully!" << endl;
        printGrid(grid);
    } else {
        cout << "No solution exists" << endl;
    }

    return 0;
}

