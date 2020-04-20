/***********************************************************************
* Program:
*    Lab 11, Password Strength
*    Brother Wilson, CS470
* Author:
*    your name
* Summary:
*    Please include a detailed description of:
*    1. What this program is designed to do
*    2. How this program will go about solving the problem
*    3. What assumptions about input (file or user) is made
*    4. Citations if the algorithm was borrowed or inspired from any source
************************************************************************/
#include <iostream>
#include <cmath>
using namespace std;

int alphabet = 0;
bool flag_CA = false;
bool flag_SA = false;
bool flag_D = false;
bool flag_SC = false;


void charCheck(char input_char)
{
   // CHECKING FOR CAPITAL ALPHABET 
   if (input_char >= 65 && input_char <= 90)
   {
       if (!flag_CA)
       {
           flag_CA = true;
           alphabet += 26;
       }
   }

   // CHECKING FOR SMALL ALPHABET 
   else if (input_char >= 97 && input_char <= 122)
   {
       if (!flag_SA)
       {
           flag_SA = true;
           alphabet += 26;
       }
   }

   // CHECKING FOR DIGITS 
   else if (input_char >= 48 && input_char <= 57)
   {
       if (!flag_D)
       {
           flag_D = true;
           alphabet += 10;
       }
   }

   // OTHERWISE SPECIAL CHARACTER 
   else
       if (!flag_SC)
       {
           flag_SC = true;
           alphabet += 32;
       }
}

int main()
{
   //Unsetting the scientific notation for cout
   cout.setf(ios::fixed);
   cout.precision(0);

   string password;
   cout << "Please enter the password: ";
   cin >> password;

   int size = password.size();
   for (int i = 0; i < size; i++)
   {
       charCheck(password[i]);
   }

   cout << "There are " << pow(alphabet, size) << " combinations\n";
   cout << "That is equivalent to a key of " << floor(log2(pow(alphabet, size))) << " bits\n";

   return 0;
