#include <iostream>
#include <string>
using namespace std;


// ==========================================
// Custom Exception Class
// ==========================================

class SudokuException
{
private:
    string message;

public:

    SudokuException(string msg)
    {
        message = msg;
    }

    string getMessage()
    {
        return message;
    }
};


// ==========================================
// Sudoku Class
// ==========================================

class Sudoku
{
private:

    // 9 x 9 Sudoku grid
    int grid[9][9];

public:

    // ======================================
    // Constructor
    // ======================================

    Sudoku()
    {
        // Initialize all cells with 0
        for (int row = 0; row < 9; row++)
        {
            for (int column = 0; column < 9; column++)
            {
                grid[row][column] = 0;
            }
        }
    }


    // ======================================
    // Display Sudoku
    // ======================================

    void display()
    {
        cout << "\n";
        cout << "     1 2 3   4 5 6   7 8 9\n";
        cout << "   -------------------------\n";

        for (int row = 0; row < 9; row++)
        {
            cout << row + 1 << " | ";

            for (int column = 0; column < 9; column++)
            {
                if (grid[row][column] == 0)
                {
                    cout << ". ";
                }
                else
                {
                    cout << grid[row][column] << " ";
                }

                if ((column + 1) % 3 == 0)
                {
                    cout << "| ";
                }
            }

            cout << endl;

            if ((row + 1) % 3 == 0)
            {
                cout << "   -------------------------\n";
            }
        }
    }


    // ======================================
    // Check if number is safe in row
    // ======================================

    bool checkRow(int row, int number)
    {
        for (int column = 0; column < 9; column++)
        {
            if (grid[row][column] == number)
            {
                return false;
            }
        }

        return true;
    }


    // ======================================
    // Check if number is safe in column
    // ======================================

    bool checkColumn(int column, int number)
    {
        for (int row = 0; row < 9; row++)
        {
            if (grid[row][column] == number)
            {
                return false;
            }
        }

        return true;
    }


    // ======================================
    // Check 3 x 3 Subgrid
    // ======================================

    bool checkBox(int startRow,
                  int startColumn,
                  int number)
    {
        for (int row = 0; row < 3; row++)
        {
            for (int column = 0; column < 3; column++)
            {
                if (grid[startRow + row]
                          [startColumn + column] == number)
                {
                    return false;
                }
            }
        }

        return true;
    }


    // ======================================
    // Check all Sudoku Rules
    // ======================================

    bool isSafe(int row, int column, int number)
    {
        bool rowSafe = checkRow(row, number);

        bool columnSafe = checkColumn(column, number);

        int startRow = row - row % 3;
        int startColumn = column - column % 3;

        bool boxSafe =
            checkBox(startRow, startColumn, number);

        if (rowSafe && columnSafe && boxSafe)
        {
            return true;
        }

        return false;
    }


    // ======================================
    // Find Empty Cell
    // ======================================

    bool findEmptyCell(int &row, int &column)
    {
        for (row = 0; row < 9; row++)
        {
            for (column = 0; column < 9; column++)
            {
                if (grid[row][column] == 0)
                {
                    return true;
                }
            }
        }

        return false;
    }


    // ======================================
    // Backtracking Algorithm
    // ======================================

    bool solve()
    {
        int row;
        int column;

        // Find an empty cell
        if (!findEmptyCell(row, column))
        {
            // No empty cell means Sudoku is solved
            return true;
        }


        // Try numbers from 1 to 9
        for (int number = 1; number <= 9; number++)
        {
            // Check whether number is valid
            if (isSafe(row, column, number))
            {
                // Put number in empty cell
                grid[row][column] = number;

                // Recursively solve remaining cells
                if (solve())
                {
                    return true;
                }

                // If solution is not possible,
                // remove the number and try another
                grid[row][column] = 0;
            }
        }

        // No number worked
        return false;
    }


    // ======================================
    // Check Initial Sudoku
    // ======================================

    bool isInitialGridValid()
    {
        for (int row = 0; row < 9; row++)
        {
            for (int column = 0; column < 9; column++)
            {
                int number = grid[row][column];

                if (number != 0)
                {
                    // Temporarily remove the number
                    grid[row][column] = 0;

                    if (!isSafe(row, column, number))
                    {
                        // Put it back
                        grid[row][column] = number;

                        return false;
                    }

                    // Put it back
                    grid[row][column] = number;
                }
            }
        }

        return true;
    }


    // ======================================
    // Input Sudoku
    // ======================================

    void inputSudoku()
    {
        cout << "\n========================================\n";
        cout << "           ENTER SUDOKU PUZZLE\n";
        cout << "========================================\n";

        cout << "\nEnter numbers from 1 to 9.\n";
        cout << "Enter 0 for an empty cell.\n\n";


        for (int row = 0; row < 9; row++)
        {
            for (int column = 0; column < 9; column++)
            {
                string input;
                bool valid = false;

                while (!valid)
                {
                    try
                    {
                        cout << "Enter value for Row "
                             << row + 1
                             << ", Column "
                             << column + 1
                             << ": ";

                        cin >> input;


                        // Input must contain only one digit
                        if (input.length() != 1)
                        {
                            throw SudokuException(
                                "Enter only one digit from 0 to 9."
                            );
                        }


                        char ch = input[0];


                        // Check whether input is a digit
                        if (ch < '0' || ch > '9')
                        {
                            throw SudokuException(
                                "Invalid input. Enter a number from 0 to 9."
                            );
                        }


                        int number = ch - '0';


                        // 0 to 9 are allowed
                        grid[row][column] = number;

                        valid = true;
                    }
                    catch (SudokuException &e)
                    {
                        cout << "Error: "
                             << e.getMessage()
                             << endl;
                    }
                }
            }
        }


        // Check whether initial puzzle follows
        // Sudoku rules
        if (!isInitialGridValid())
        {
            throw SudokuException(
                "The entered Sudoku puzzle is invalid. "
                "A number is repeated in a row, column or 3x3 box."
            );
        }
    }
};


// ==========================================
// Main Function
// ==========================================

int main()
{
    int choice;

    bool running = true;


    while (running)
    {
        cout << "\n\n========================================\n";
        cout << "             SUDOKU SOLVER\n";
        cout << "========================================\n";
        cout << "1. Enter Sudoku Puzzle\n";
        cout << "2. Exit\n";
        cout << "========================================\n";


        string menuChoice;

        try
        {
            cout << "Enter your choice: ";
            cin >> menuChoice;


            if (menuChoice != "1" &&
                menuChoice != "2")
            {
                throw SudokuException(
                    "Invalid choice. Enter 1 or 2."
                );
            }


            choice = menuChoice[0] - '0';


            if (choice == 1)
            {
                Sudoku sudoku;


                try
                {
                    // Input puzzle
                    sudoku.inputSudoku();


                    cout << "\n========================================\n";
                    cout << "          ORIGINAL SUDOKU\n";
                    cout << "========================================\n";

                    sudoku.display();


                    cout << "\nSolving Sudoku...\n";


                    // Backtracking solver
                    if (sudoku.solve())
                    {
                        cout << "\n========================================\n";
                        cout << "          SUDOKU SOLVED!\n";
                        cout << "========================================\n";

                        sudoku.display();
                    }
                    else
                    {
                        cout << "\n========================================\n";
                        cout << "       NO SOLUTION EXISTS\n";
                        cout << "========================================\n";

                        cout << "The entered Sudoku puzzle cannot be solved.\n";
                    }
                }
                catch (SudokuException &e)
                {
                    cout << "\nError: "
                         << e.getMessage()
                         << endl;
                }
            }


            else if (choice == 2)
            {
                cout << "\nThank you for using Sudoku Solver!\n";

                running = false;
            }
        }
        catch (SudokuException &e)
        {
            cout << "\nError: "
                 << e.getMessage()
                 << endl;
        }
    }


    return 0;
}
