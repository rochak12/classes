#include <iostream>
using namespace std;

struct Position { int row; int col; };

/****************************************************************
 * GET POSITION FROM TEXT: convert "d2" to row=1, col=3
 ****************************************************************/
Position getPosition()
{
   string text;
   cin >> text;
   Position pos;
   pos.row = text[1] - '1';
   pos.col = text[0] - 'a';
   return pos;
}

/***************************************************************
 * DISPLAY: Display the board on the screen
 ***************************************************************/
void display(const char chess[8][8])
{
   for (int row = 0; row < 8; row++)
      for (int col = 0; col < 8; col++)
         cout << chess[row][col] << (col == 7 ? '\n' : ' ');
}

/****************************************************************
 * MAIN: Simple chess playing program
 ****************************************************************/
int main()
{
   char chess[8][8] =
   {  {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'},
      {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
      {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
      {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
      {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
      {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
      {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
      {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'}};
   display(chess);
   
   cout << "From: ";
   Position from = getPosition();
   cout << "To:   ";
   Position to = getPosition();

   // move a piece
   char tmp = chess[to.row][to.col];
   chess[to.row][to.col] = chess[from.row][from.col];
   chess[from.row][from.col] = tmp;

   display(chess);
   return 0;
}
