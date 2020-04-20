/************************************************************
 ,*  Play Sudoku by interacting with the user, or solve a
 ,* board by forcing or backtracking.
 ,************************************************************/
#include <cassert>
#include <cstring>
#include <fstream>
#include <iostream>
#include <iomanip>
using namespace std;

#define N 9
#define SRN 3
#define MAX 256
#define abs(x) ((x < 0) ? -x : x)
#define getSubgridOrigin(n) (n / SRN * SRN)

void getFilename(char fileName[], const char *prompt);
void showOptions();
void interact(int board[][N], bool readOnlyGreen, char *writeFileName);
bool readBoard(char fileName[], int board[][N]);
bool readGame(int board[][N], char *readFileName);
bool verifyBoard(int board[][N]);

bool writeBoard(char fileName[], int board[][N]);
bool writeGame(int board[][N], char *writeFileName);
void showBoard(int board[][N], bool readOnlyGreen);

bool getCoordinates(char square[], int board[][N], int &r, int &c,
                    bool &readOnly, bool readOnlyGreen);

void editSquare(int board[][N], bool readOnlyGreen);
void showPossible(int board[][N], bool readOnlyGreen);
int  computeValues(int board[][N], int r, int c, bool possible[]);

void solveBoard(int board[][N]);
bool solved(int board[][N]);
bool solveBoardEasily(int board[][N]);
bool solveBoardByBacktracking(int board[][N], int row, int col);

long numCallsToSolveBoardByBacktracking = 0;

/****************************************************************
 ,* MAIN
 ,***************************************************************/
int main(int argc, char *argv[])
{
    int board[N][N];

#ifdef EXTRA
    bool readOnlyGreen = true;
#else
    bool readOnlyGreen = false;
#endif

    char  readFileName[MAX] = "";
    char writeFileName[MAX] = "";

    if (argc >= 2)
        strcpy(readFileName, argv[1]);
    if (argc >= 3)
        strcpy(writeFileName, argv[2]);

    if (readGame(board, readFileName))
    {
        showOptions();

        showBoard(board, readOnlyGreen);

        interact(board, readOnlyGreen, writeFileName);
    }

#ifdef SOLVE
    cout << "numCallsToSolveBoardByBacktracking = "
          << numCallsToSolveBoardByBacktracking << endl;
#endif
    return 0;
}



/****************************************************************
 ,* GET FILENAME
 ,***************************************************************/
void getFilename(char fileName[], const char *prompt)
{
    cout << prompt << " ";
    cin >> fileName;
}

/****************************************************************
 ,* SHOW OPTIONS
 ,***************************************************************/
void showOptions()
{
    cout << "Options:\n"
         << "   ?  Show these instructions\n"
         << "   D  Display the board\n"
         << "   E  Edit one square\n"
         << "   S  Show the possible values for a square\n"
         << "   F  Solve Board\n"
         #ifdef SOLVE
         << "   F  Solve the board\n"
         #endif
         << "   Q  Save and Quit\n\n";
}

/****************************************************************
 ,* INTERACT
 ,***************************************************************/
void interact(int board[][N], bool readOnlyGreen, char* writeFileName)
{
    char input = 'Q';

    do
    {
        cout << "\n> ";
        cin  >> input;

        input = toupper(input);

        switch (input)
        {
            case '?':
                showOptions();
                break;
            case 'D':
                showBoard(board, readOnlyGreen);
                break;
            case 'E':
                editSquare(board, readOnlyGreen);
                break;
            case 'F':
                solveBoard(board);
                showBoard(board, readOnlyGreen);
                break;
            case 'S':
                showPossible(board, readOnlyGreen);
                break;
            case 'Q':
                writeGame(board, writeFileName);
                break;
            default:
                cout << "ERROR: Invalid command\n";
                break;
        }
    }
    while (input != 'Q');
}

/****************************************************************
 ,* READ GAME
 ,***************************************************************/
bool readGame(int board[][N], char* readFileName)
{
    char fileName[MAX];

    if (strlen(readFileName) == 0)
        getFilename(fileName, "Where is your board located?");
    else
        strcpy(fileName, readFileName);

    return (readBoard(fileName, board));
}

/****************************************************************
 ,* READ BOARD
 ,***************************************************************/
bool readBoard(char fileName[], int board[][N])
{
    ifstream fin(fileName);

    if (fin.fail())
    {
        cerr << "ERROR: unable to read " << fileName << endl;
        return false;
    }
    else
    {
        for (int r = 0; r < N; r++)
        {
            for (int c = 0; c < N; c++)
            {
                if (! (fin >> board[r][c]))
                {
                    fin.close();
                    return false;
                }
            }
        }
        fin.close();
        return verifyBoard(board);
    }
}

/****************************************************************
 ,* WRITE GAME
 ,***************************************************************/
bool writeGame(int board[][N], char* writeFileName)
{
    char fileName[MAX];
    if (strlen(writeFileName) == 0)
        getFilename(fileName, "What file would you like to write your board to:");
    else
        strcpy(fileName, writeFileName);

    if (writeBoard(fileName, board))
    {
        cout << "Board written successfully\n";
        return true;
    }
    else
    {
        cerr << "ERROR: unable to write " << fileName << endl;
        return false;
    }
}

/****************************************************************
 ,* WRITE BOARD
 ,***************************************************************/
bool writeBoard(char fileName[], int board[][N])
{
    ofstream fout(fileName);

    if (fout.fail())
    {
        return false;
    }
    else
    {
        for (int r = 0; r < N; r++)
        {
            for (int c = 0; c < N; c++)
            {
                fout << board[r][c] << " ";
                if (c == 8)
                {
                    fout << endl;
                }
                if (fout.fail())
                {
                    fout.close();
                    return false;
                }
            }
        }
        fout.close();
        return true;
    }
}

/****************************************************************
 ,* SHOW BOARD
 ,***************************************************************/
void showBoard(int board[][N], bool readOnlyGreen)
{
    cout << "   A B C D E F G H I\n";
    for (int r = 0; r < N; r++)
    {
        cout << (r + 1) << "  ";
        for (int c = 0; c < N; c++)
        {
            int val = board[r][c];
            if (val == 0)
                cout << " ";
            else if (val < 0)
                cout << -val;
            else if (readOnlyGreen)
                cout << "\E[22;32m" << val << "\E[0m";
            else
                cout << val;

            if (c % 3 == 2)
                cout << ((c == 8) ? '\n' : '|');
            else
                cout << " ";
        }
        if (r == 2 || r == 5)
            cout << "   -----+-----+-----\n";
    }
}

/****************************************************************
 ,* GET COORDINATES
 ,***************************************************************/
bool getCoordinates(char square[3], int board[][N], int &r, int &c,
                    bool &readOnly, bool readOnlyGreen)
{
    r = -1;
    c = -1;

    cout << "What are the coordinates of the square: ";
    cin  >> square;
    char orig1 = square[0];
    char orig2 = square[1];

    char first = toupper(orig1);
    char second = toupper(orig2);

    if (isalpha(first))
    {
        c = first - 'A';
        if ('1' <= second && second <= '9')
        {
            r = second - '1';
        }
        square[0] = first;
        square[1] = second;
    }
    else
    {
        if ('1' <= first && first <= '9')
        {
            r = first - '1';
        }
        c = second - 'A';
        square[0] = second;
        square[1] = first;
    }

    if (0 <= r && r <= N && 0 <= c && c <= N)
    {
        if (board[r][c] <= 0)
        {
            return true;
        }
        else
        {
            readOnly = readOnlyGreen;
            cout << "ERROR: Square '" << square << "' is "
                 << (readOnly ? "read-only" : "filled")
                 << endl;
            return true;
        }
    }
    else
    {
        cout << "ERROR: Square '" << orig1 << orig2 << "' is invalid\n";
        return false;
    }
}

/****************************************************************
 ,* DETECT READ-ONLY
 ,* Returns true if any number in the board is negative, which
 ,* indicates that the positive numbers are read-only.
 ,* Returns false if no number in the board is negative.
 ,***************************************************************/
bool detectReadOnly(int board[][N])
{
    for (int r = 0; r < N; r++)
    {
        for (int c = 0; c < N; c++)
        {
            if (board[r][c] < 0)
            {
                return true;
            }
        }
    }
    return false;
}

/****************************************************************
 ,* EDIT SQUARE
 ,***************************************************************/
void editSquare(int board[][N], bool readOnlyGreen)
{
    int r;
    int c;
    char square[] = "A1";
    bool readOnly = false;
    while (! getCoordinates(square, board, r, c, readOnly, readOnlyGreen))
    {
        ; // intentionally left empty
    }
    if (! readOnly)
    {
        int value;
        bool possible[N + 1];

        cout << "What is the value at '" << square << "': ";
        cin >> value;

#ifdef EXTRA
        if (value == 0)
        {
           board[r][c] = value;
           return;
        }
#endif

        if (1 <= value && value <= N &&
            (computeValues(board, r, c, possible) > 0) &&
            possible[value])
        {
            board[r][c] = -value;
        }
        else
        {
            cout << "ERROR: Value '" << value
                 << "' in square '" << square
                 << "' is invalid\n";
        }
    }
}

/****************************************************************
 ,* VERIFY BOARD
 ,***************************************************************/
bool verifyBoard(int board[][N])
{
    int numEachRow[N + 1];
    int numEachCol[N + 1];
    int numEachSubGrid[N + 1];

    for (int r = 0; r < N; r++)
    {
        for (int i = 1; i <= N; i++)
        {
            numEachRow[i] = 0;
        }

        for (int c = 0; c < N; c++)
        {
            numEachRow[abs(board[r][c])]++;
        }

        for (int i = 1; i <= N; i++)
        {
            if (numEachRow[i] > 1)
            {
                cout << "ERROR: Duplicate value '"
                     << i
                     << "' in row "
                     << (r + 1)
                     << endl;

                return false;
            }
        }
    }

    for (int c = 0; c < N; c++)
    {
        for (int i = 1; i <= N; i++)
        {
            numEachCol[i] = 0;
        }

        for (int r = 0; r < N; r++)
        {
            numEachCol[abs(board[r][c])]++;
        }

        for (int i = 1; i <= N; i++)
        {
            if (numEachCol[i] > 1)
            {
                cout << "ERROR: Duplicate value '" << i
                     << "' in column "
                     << (char) (c + 'A' - 1)
                     << endl;

                return false;
            }
        }
    }

    for (int rOffset = 0; rOffset < SRN; rOffset++)
    {
        for (int cOffset = 0; cOffset < SRN; cOffset++)
        {
            for (int i = 1; i <= N; i++)
            {
                numEachSubGrid[i] = 0;
            }

            int rOffending = -1;
            int cOffending = -1;

            for (int r = rOffset * SRN; r < (rOffset + 1) * SRN; r++)
            {
                for (int c = cOffset * SRN; c < (cOffset + 1) * SRN; c++)
                {
                    int index = abs(board[r][c]);
                    numEachSubGrid[index]++;
                    if (numEachSubGrid[index] > 1)
                    {
                        rOffending = getSubgridOrigin(r) + 1;
                        cOffending = getSubgridOrigin(c) + 1;
                    }
                }
            }

            for (int i = 1; i <= N; i++)
            {
                if (numEachSubGrid[i] > 1)
                {
                    cout << "ERROR: Duplicate value '" << i
                         << "' in inside square represented by '"
                         << (char) (cOffending + 'A')
                         << (rOffending + 1)
                         << "'\n";

                    return false;
                }
            }
        }
    }
    return true;
}

/****************************************************************
 ,* SHOW POSSIBLE
 ,***************************************************************/
void showPossible(int board[][N], bool readOnlyGreen)
{
    int r;
    int c;
    bool possible[N + 1];
    char square[] = "A1";
    bool readOnly = false;
    while (! getCoordinates(square, board, r, c, readOnly, readOnlyGreen))
    {
        ; // intentionally left empty
    }
    if (! readOnly)
    {
        cout << "The possible values for '" << square << "' are: ";

        if (computeValues(board, r, c, possible) > 0)
        {
            bool putSeparator = false;

            for (int i = 1; i <= N; i++)
            {
                if (possible[i])
                {
                    if (putSeparator)
                    {
                        cout << ", ";
                    }
                    else
                    {
                        putSeparator = true;
                    }
                    cout << i;
                }
            }
            cout << endl;
        }
    }
}

/****************************************************************
 ,* COMPUTE VALUES
 ,***************************************************************/
int computeValues(int board[][N], int r, int c, bool possible[])
{
    assert(0 <= r && r < N && 0 <= c && c < N);
    int numPossible = 0;

    for (int i = 0; i <= N; i++)
    {
        possible[i] = true;
    }

    for (int i = 0; i < N; i++)
    {
        possible[abs(board[r][i])] = false;
        possible[abs(board[i][c])] = false;
    }

    int rOffset = getSubgridOrigin(r);
    int cOffset = getSubgridOrigin(c);

    for (int iRow = rOffset; iRow < rOffset + SRN; iRow++)
    {
        for (int iCol = cOffset; iCol < cOffset + SRN; iCol++)
        {
            possible[abs(board[iRow][iCol])] = false;
        }
    }

    for (int i = 1; i <= N; i++)
    {
        if (possible[i])
        {
            numPossible++;
        }
    }
    return numPossible;
}

bool isPossibleToPut(int board[][N], int row, int col, int n)
{
    // for checking in the subgrid containing row, col
    int rOffset = getSubgridOrigin(row);
    int cOffset = getSubgridOrigin(col);

    for (int i = 0; i < N; i++)
    {
        if (abs(board[row][i]) == n)
        {
            return false;
        }
        if (abs(board[i][col]) == n)
        {
            return false;
        }
        if (abs(board[rOffset + (i % SRN)][cOffset + (i / SRN)]) == n)
        {
            return false;
        }
    }
    // not proven impossible, therefore proven possible
    return true;
}

/****************************************************************
 ,* SOLVE BOARD
 ,***************************************************************/
void solveBoard(int board[][N])
{
    if (solveBoardEasily(board))
    {
        cout << "Board solved:\n";
    }
    else
    {
        cout << "Not easily solved, trying again with backtracking...\n";
        if (solveBoardByBacktracking(board, 0, 0))
        {
            cout << "Board solved:\n";
        }
    }
}

/****************************************************************
 ,* SOLVE BOARD BY BACKTRACKING
 ,* Algorithm: Backtrack(X[1..i])
 ,* // Gives a template of a generic backtracking algorithm
 ,* // Input: X[1..i] specifies first i promising components of
 ,* //        a solution
 ,* // Output: All the tuples representing the problem's solutions
 ,* if X[1..i] is a solution Write X[1..i]
 ,* else
 ,*    for each element x in S_{i + 1} consistent with X[1..i]
 ,*        and the problem's constraints
 ,*      do
 ,*         X[i + 1] <-- x
 ,*         Backtrack(X[1..i + 1])
 ,*
 ,* To start this backtracking algorithm, call it for i = 0;
 ,* X[1..0] represents the empty tuple.
 ,***************************************************************/
bool solveBoardByBacktracking(int board[][N], int row, int col)
{
    numCallsToSolveBoardByBacktracking++;
    if (col >= 9)
    {
        col = 0;
        ++row;
        if (row >= 9)
        {
            return true; // no more rows or cols to fill
        }
    }

    if (board[row][col] != 0) // pre-filled
    {
        // try the next one
        return solveBoardByBacktracking(board, row, col + 1);
    }
    else
    {
        for (int n = 1; n <= 9; n++)
        {
            if (isPossibleToPut(board, row, col, n))
            {
                board[row][col] = -n;

                if (solveBoardByBacktracking(board, row, col + 1))
                {
                    return true;
                }
                else // undo and try the next n
                {
                    board[row][col] = 0;
                }
            }
        }
    }
    // nothing possible at row, col
    return false;
}

int findFirstPossible(bool possible[])
{
    for (int i = 1; i <= N; i++)
    {
        if (possible[i])
        {
            return i;
        }
    }
    return 0;
}

/****************************************************************
 ,* SOLVED
 ,* Returns true if no value in the board is 0, false otherwise.
 ,***************************************************************/
bool solved(int board[][N])
{
    for (int r = 0; r < N; r++)
    {
        for (int c = 0; c < N; c++)
        {
            if (board[r][c] == 0)
            {
                return false;
            }
        }
    }
    return true;
}

/****************************************************************
 ,* SOLVE BOARD EASILY
 ,***************************************************************/
bool solveBoardEasily(int board[][N])
{
    bool possible[N + 1];
    int numForced;

    do
    {
        numForced = 0;

        for (int r = 0; r < N; r++)
        {
            for (int c = 0; c < N; c++)
            {
                if (board[r][c] == 0 &&
                    computeValues(board, r, c, possible) == 1)
                {
                    // here computeValues has guaranteed (via the == 1)
                    // that only one value is possible, so
                    // find that one value that's possible to go at r, c
                    // and put it there (negating first)
                    int p = findFirstPossible(possible);
                    board[r][c] = -p;
                    numForced++;
                }
            }
        }
    }
    while (! solved(board) && numForced != 0);
    return solved(board);
}

