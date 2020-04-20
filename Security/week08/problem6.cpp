#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;

/*********************************************
 * INITIALIZE BOARD
 * Initialize the chess board
 *********************************************/
void initializeBoard(char board[])
{  // default position of the pieces
   const char *boardBlank[] = 
      {  "rnbqkbnr",
         "pppppppp",
         "        ",
         "        ",
         "        ",
         "        ",
         "PPPPPPPP",
         "RNBQKBNR" };
   
   for (int i = 0; i < 64; i++)
      board[i] = boardBlank[i / 8][i % 8];
}

/*****************************************
 * READ MOVES
 * Read a list of chess moves from a file
 *****************************************/
void readMoves(char moves[][32], int *pNum)
{  // open the file and beginn reading
   char *fileName = new char[256];
   cout << "Specify the filename fo the moves: ";
   cin  >> fileName;
   ifstream fin(fileName);
   
   *pNum = 0;
   while (fin >> moves[*pNum])
      (*pNum)++;
   
   fin.close();
}

/*****************************************
 * ZERO MOVES
 * Empty the move list
 *****************************************/
void zeroMoves(char moves[][32], int *pNum)
{
   *pNum = 0;
}

/****************************************
 * PLAY MOVES
 * Move a piece on the screen
 ****************************************/
void playMove(char *board, const char moves[][32], int num)
{  // for each move, play it
   for (int i = 0; i < num; i++)
   {
      int rSrc = moves[i][0] - 'A';
      int cSrc = moves[i][1] - '0';
      int rDes = moves[i][2] - 'A';
      int cDes = moves[i][3] - '0';
      board[rDes * 8 + cDes] = board[rSrc * 8 + cSrc];
      board[rSrc * 8 + cSrc] = ' ';
   }
}

/********************************************
 * CORRECT MOVES
 * What do you do when a mistake was made?
 ********************************************/
void correctMoves(char moves[][32], int *pNum)
{  // display the move list
   cout << "Current move list: \n";
   int iMove = 0;
   for (char *p[32] = moves; p < moves + *pNum; p++)
      cout << '\t' << ++iMove << ": " << *p << endl;
   
   // prompt for correction
   do
   {
      cout << "Which move would you like to fix?  Select 0 for 'none'\n";
      cin  >> iMove;
      if (iMove)
      {
         char input[32];
         cout << "Please select the new move for " << iMove << endl;
         cin  >> input;
         strcpy(moves[iMove - 1], input); // -1 because humans are 1-based
      }
   }
   while (iMove);
}

/***************************************
 * DISPLAY BOARD
 * Put the board on the screen. No frills
 **************************************/
void displayBoard(const char *board)
{
   for (const char *p = board; p < board + 64; p++)
      cout << *p << ((p - board) % 8 == 7 ? '\n' : ' ');
}


/********************************************
 * MAIN
 ********************************************/
int main()
{  // start the game
   char moves[50][32];
   int *pNumMoves = new int;
   char *board = new char[8 * 8];
   void (*pfn)(char (*)[32], int *) = correctMoves;
   initializeBoard(board);
   
   // read and correct the moves
   readMoves(moves, pNumMoves);
   pfn(moves, pNumMoves);
   
   // apply the moves to the game
   playMove(board, moves, *pNumMoves);
   displayBoard(board);
   
   // all done
   delete [] board;
   delete pNumMoves;
   return 0;
}
