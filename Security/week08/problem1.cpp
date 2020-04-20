#include <iostream>
#include <string.h>
using namespace std;

/**************************************************************
 * MAIN : A simple program to authenticate the user
 **************************************************************/
int main()
{
   // list of valid users
   char username[17];
   char password[8];
   const char * passwords[3] = { "PA$W0RD", "1234567", "Rosebud" };
   const char * usernames[3] = { "Admin",    "User",     "Kane"    };

   // prompt for username and password
   cout << "What is your username? ";
   cin.getline(username, 17);
   cout << "What is your password? ";
   cin.getline(password, 17);

   // identify the user
   int id = -1;
   for (int i = 0; i < 3; i++)
      if (strcmp(username, usernames[i]) == 0 &&
          strcmp(password, passwords[i]) == 0)
         id = i;

   // make a decision
   switch (id)
   {
      case 0:
         cout << "Welcome, " << usernames[id] << " you have full access\n";
         break;
      case 1:
         cout << "Users have limited access to many things\n";
         break;
      case 2:
         cout << "Mr. " << usernames[id] << ", so kind of you to visit\n";
         break;
      default:
         cout << "You are not authorized to access anything on the system.\n";
   }

   return 0;
}
