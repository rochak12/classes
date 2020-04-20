#include <iostream>   // for CIN, COUT
#include <fstream>    // for FIN
#include <iomanip>    // for SETW
using namespace std;

void readGrades(int grades[], int * pNumGrades); // read grades from a file
void interact(  int grades[], int    numGrades); // let user edit the file
void display(   int grades[], int    numGrades); // display the results
void getFileName(char fileName[]);               // prompt for file name
int  getIndex();                                 // prompt for an index
int  getGrade();                                 // prompt user for a grade

/**************************************************************************
 * MAIN: simple program to keep track of a list of grades
 **************************************************************************/
int main()
{
   int grades[10];
   void (*pFunction)(int grades[], int numGrades) = display;
   int * pNumGrades = new int;

   // read the grades file
   readGrades(grades, pNumGrades);
   display(grades, *pNumGrades);

   // let the user interact with the grades
   interact(grades, *pNumGrades);

   // display the final list
   pFunction(grades, *pNumGrades);

   delete pNumGrades;
   return 0;
}

/**************************************************************************
 * READ GRADES: read a list of grades from a file
 **************************************************************************/
void readGrades(int grades[], int * pNumGrades)
{
   // open the file
   char fileName[256];
   getFileName(fileName);
   ifstream fin(fileName);

   // check for failure
   *pNumGrades = 0;
   if (fin.fail())
      return;

   // read the data
   while (fin >> grades[*pNumGrades])
      (*pNumGrades)++;

   // all done!
   fin.close();
   return;
}

/**************************************************************************
 * INTERACT: allow the user to change grades
 **************************************************************************/
void interact(int grades[], int numGrades)
{
   int index = getIndex();
   while (index != -1)
   {
      grades[index] = getGrade();
      index = getIndex();
   }
   return;
}

/**************************************************************************
 * DISPLAY: display the contents of the grades to the user
 **************************************************************************/
void display(int grades[], int numGrades)
{
   cout << setw(4) << "#"   << setw(10) << "grade" << endl;
   cout << setw(4) << "---" << setw(10) << "-----" << endl;

   // display all the grades
   for (int i = 0; i < numGrades; i++)
   {
      cout << setw(4)  << i + 1 << setw(10);
      if (grades[i] == -1)
         cout << "---\n";
      else
         cout << grades[i] << "%\n";
   }
}

/**************************************************************************
 * GET FILENAME: prompt the user for the file to read
 **************************************************************************/
void getFileName(char fileName[])
{
   cout << "Please specify the file name of the grades file: ";
   cin  >> fileName;
}

/**************************************************************************
 * GET INDEX: prompt the user for the index of the grade to change
 **************************************************************************/
int getIndex()
{
   int index;
   cout << "What grade would you like to change? Enter 0 to quit: ";
   cin  >> index;              // humans are 1-based
   return index - 1;           // computes are 0-based
}

/**************************************************************************
 * GET GRADE: prompt the user for the new grade value
 **************************************************************************/
int getGrade()
{
   int grade;
   cout << "What is the new grade value? Enter -1 for <none>: ";
   cin  >> grade;
   return grade;
}
