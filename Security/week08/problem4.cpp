#include <iostream>
#include <fstream>
using namespace std;

/*******************************************
 * ENCRYPT : Use a highly secret algorithm to encrypt the text
 *******************************************/
void encrypt(long * cipherText, int numElements, const string & plainText)
{
   for (int i = 0; i < numElements; i++)
      cipherText[i] += (i < plainText.size() ? plainText[i] : '\0');
}

/************************************************
 * READ : Read the secret from a file
 ***********************************************/
void readSecret(string & secret, char * fileName)
{
   // get the fileName
   cout << "What is the filename? ";
   cin.getline(fileName, 256);
   
   // open the file, read from it, and close it
   ifstream fin(fileName);
   if (!fin.fail())
      fin >> secret;
   fin.close();
}

/*************************************************
 * MAIN : there is nothing much else to say...
 *************************************************/
int main()
{
   // allocate the filename. It will be freed when done
   char * fileName = new char[64];
   long encrypted[12] = {54, 98, 21, 43, 69, 34, 78, 12, 14, 82, 40, 71 };
   string secret = "secret placeholder";

   // read the secret from a file
   readSecret(secret, fileName);
   delete [] fileName;

   // encrypt the text
   encrypt(encrypted, sizeof(encrypted), secret);

   // display results
   cout << "The ciphertext is:\n\t" << encrypted[0];
   for (int i = 1; i < 12; i++)
      cout << ", " << encrypted[i];
   cout << endl;
   
   return 0;
}
