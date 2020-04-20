#include <iostream>
using namespace std;

/******************************************************************
 * GENERATE FULL NAME : Create a full name from the components
 ******************************************************************/
void generateFullName(char * fullName, int sizeFullName,
                      const char firstName[], const char lastName[])
{
   unsigned char numUsed = 0;

   // copy last name
   for (const char * p = lastName; *p; p++)
      if (++numUsed < sizeFullName) // if we have space for 1 more
         *(fullName++) = *p;

   // copy on the comma and the space
   if (numUsed + 2 < sizeFullName)    // if we have space for 2 more
   {
      *(fullName++) = ',';
      *(fullName++) = ' ';
      numUsed += 2;
   }

   // copy first name
   for (const char * p = firstName; *p; p++)
      if (++numUsed < sizeFullName)  // if we have space for 1 more
         *(fullName++) = *p;

   // null character
   if (++numUsed < sizeFullName)    // if we have space for 1 more      
      *fullName = '\0';
}

/******************************************************************
 * MAIN : Display a person's full name from the components
 ******************************************************************/
int main()
{
   // prompt for the components
   string firstName;
   string lastName;
   cout << "First name: ";
   cin  >> firstName;
   cout << "Last name:  ";
   cin  >> lastName;

   // generate and display the full name
   char fullName[512];
   generateFullName(fullName, 512, firstName.c_str(), lastName.c_str());
   cout << "\tFull name: " << fullName << endl;
   return 0;
}
   


