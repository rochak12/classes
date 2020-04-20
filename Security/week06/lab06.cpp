/***********************************************************************
* Program:
*    Lab 08, Vulnerabilities and Exploits
*    Brother Wilson, CS470
* Author:
*    Rochak Kunwar
* Summary:
*    This program is designed to demonstrate memory injection vulnerabilities.
*    We are testing the code to better understand memory injection.
************************************************************************/

#include <iostream>
#include <cassert>
#include <cstring>
using namespace std;

void stackExploit();
void heapExploit();
void arrayExploit();
void intExploit();
void arcExploit();
void subterfugeExploit();
void vtableExploit();
void ansiExploit();

/******************************************************
 * MAIN
 * This function take you to the various exploits
 *****************************************************/
int main()
{
	// prompt
	cout << "  1. Array index\n"
		<< "  2. Pointer subterfuge\n"
		<< "  3. ARC injection\n"
		<< "  4. VTable spraying\n"
		<< "  5. Stack smashing\n"
		<< "  6. Heap spraying\n"
		<< "  7. Integer overflow\n"
		<< "  8. ANSI-Unicode conversion\n"
		<< "> ";
	int select;
	cin >> select;

	switch (select)
	{
	case 1:
		arrayExploit();
		break;
	case 2:
		subterfugeExploit();
		break;
	case 3:
		arcExploit();
		break;
	case 4:
		vtableExploit();
		break;
	case 5:
		stackExploit();
		break;
	case 6:
		heapExploit();
		break;
	case 7:
		intExploit();
		break;
	case 8:
		ansiExploit();
		break;
	default:
		cout << "Unknown option " << select << endl;
	}
	return 0;
}

/**************************************************************
* A helper function
 **************************************************************/
void hacked()
{
	cout << "You have been hacked.\n";
}

/**************************************************************
* A helper function
 **************************************************************/
void safe()
{
	cout << "You are safe.\n";
}

/**************************************************************
* A helper function
 **************************************************************/
void dangerous()
{
	cout << "You have been hacked.\n";
}


/**************************************************************
 **************************************************************
 *******************    SUBTERFUGE    *************************
 **************************************************************
 **************************************************************/

 /****************************************
  * Pointer Subterfuge Vulnerability
  * 1. There must be a pointer used in the code.
  * 2. There must be a way to overwrite the pointer
  * 3. After the pointer is overwritten, the pointer is dereferenced
  ****************************************/
void subterfugeVulnerability(long* array, int size)
{
	long int buffer[2] = { 0, 1 };
	const char* message = "All is safe; nothing bad happened\n";  // 1. Pointer

	for (int i = 0; i < size; i++)  // 2. Overwrite
		buffer[i] = array[i];

	cout << message;                // 3. Dereference

}

/****************************************
 * Pointer Subterfuge Exploitation
 * 1. The attacker must exploit a vulnerability allowing
 *    unintended access to the pointer
 * 2. The attacker must be able to provide a new pointer
 *    referring to data altering the normal flow of the program
 ****************************************/
void subterfugeExploit()
{
	// an attacker's array
	long int array[3] =             // 1. Exploit
	{
	   0,
	   1,
	   (long int)"!!!!!!!!!!!!! You've been hacked !!!!!!!!!!!!!\n"
	   // 2. Provide pointer
	};

	// exploit it
	subterfugeVulnerability(array, 3);
}

/**************************************************************
 **************************************************************
 ********************     ARRAY      **************************
 **************************************************************
 **************************************************************/

 /*************************************
  * ARRAY VULNERABILTY
  * 1. There must be an array and an array index variable
  * 2. The array index variable must be reachable through external input.
  * 3. There must not be bounds checking on the array index variable.
  ************************************/
void arrayVulnerability(int index, char value)    //2. index value by external 
{
	char array[4] = {};                            //1. an array

	for (int i = 0; i < 100; i++);                 //streamlines the memory

	assert(array[index] == 'n');
	array[index] = value;                         //3. no bound checking

	for (int i = 0; i < 100; i++);                 //streamlines the memory
}

/**************************************
 * ARRAY EXPLOIT
 * 1. The attacker provides an array index value outside the expected range
 * 2. The attacker must be able to provide input or redirect
 *    existing input into the array at the index he provided
 * 3. The injected value must alter program state in a way
 *    that is desirable to the attacker
 *************************************/
void arrayExploit()
{
	char hacked = 'n';

	arrayVulnerability(43,                     //1. expected range in 0....3
		'y');                //2. provive input

	if (hacked == 'y')                         //3. alter program state
		cout << "!!!!!!!!!!!!! You've been hacked !!!!!!!!!!!!!\n";
	else if (hacked == 'n')
		cout << "You missed. Not able to hack\n";

}

/**************************************************************
 **************************************************************
 ********************      ARC       **************************
 **************************************************************
 **************************************************************/

 /*********************************
  * ARC VULNERABILITY
  * 1. There must be a function pointer used in the code.
  * 2. Through some vulnerability, there must be a way for user input
  *    to overwrite the function pointer. This typically happens through
  *    a stack buffer vulnerability.
  * 3. After the memory is overwritten, the function pointer must
  *    be dereferenced
  ********************************/
void arcVulnerability(long* array, int size)
{
	long int buffer[2];
	void (*pointerFunction)() = safe;   //1. function pointer

	for (int i = 0; i < size; i++)      //user input overwrite
		buffer[i] = array[i];

	pointerFunction();                  //3. deferenced
}

/*********************************
 * ARC EXPLOIT
 * 1. The attacker must exploit a vulnerability allowing
 *    unintended access to the function pointer
 * 2. The attacker must have the address to another function
 *    which is to be used to replace the existing function pointer
  ********************************/
void arcExploit()
{
	long int array[3] = { 0 , 1,
	   (long int)dangerous };           //2. address to other function

	arcVulnerability(array, 3);         //1. exploit vulnerability
}

/**************************************************************
 **************************************************************
 ********************     VTABLE     **************************
 **************************************************************
 **************************************************************/

 /***********************************
  * VULNERABILITY
  * 1. The vulnerable class must be polymorphic.
  * 2. The class must have a buffer as a member variable.
  * 3. Through some vulnerability, there must be a way for user input
  *    to overwrite parts of the VTable.
  * 4. After a virtual function pointer is overwritten,
  *    the virtual function must be called.
  **********************************/
class Vulnerability
{
public:
	long numbers[2];                        //2. Buffer as memory

	void setNumber(long value, int index)
	{
		numbers[index] = value;              //3. override parts of vtable
	}
	virtual void display() const = 0;       //1. ploymorphic function
};

/************************************
 * Safe
 ***********************************/
class Safe : public Vulnerability
{
public:
	virtual void display() const          //4. Call the virtual function
	{
		cout << "All is safe; nothing bad happened\n";
	}
};

/************************************
 * VTABLE EXPLOIT
 * 1. Through some vulnerability, the VTable pointer
 *     or a function pointer within the VTable must be overwritten
 * 2. The attacker must have the address to another VTable pointer
 *     or a function pointer
 ***********************************/
void vtableExploit()
{
	Safe s;
	void (*pointerFunction)() = dangerous;    // 2. provide a pointer

	s.setNumber((long)pointerFunction, -2);    // 1. override the pointer
	s.display();
}


/**************************************************************
 **************************************************************
 ********************    STACK       **************************
 **************************************************************
 **************************************************************/

 /***********************************************
  * STACK VULNERABILITY
  * 1. There must be a buffer on the stack
  * 2. the buffer must be reachable from an external input
  * 3. The mechanism to fill the buffer must not check the correct buffersize
  **********************************************/
void stackVulnerability(long int input[], long int num)
//num must be greater than two for exploitation
{
	long int i = 0;
	long int buffer[2];        //1. buffer in stack

	for (i = 0; i < num; i++)     //3. wrong buffer size
	{
		cout << "\t" << i << " "
			<< hex << buffer[i]
			<< (buffer[i] > (long)stackExploit&&
				buffer[i] < (long)stackExploit + 0x200 ?
				"  <-----------return address " : " ")
			<< endl;
		buffer[i] = input[i];      //2. Buffer rechable
	}
}

/*********************************************
 * STACK EXPLOIT
 * 1. The attacker must provide more data into the
 *    outwardly facing buffer than the buffer is designed to hold
 * 2. The attacker must know where the the stack pointer resides
 *    on the stack. This should be just beyond the end of the buffer
 * 3. The attacker must insert machine language instructions in the buffer.
 *    This may occur before, after, or even around the stack pointer. The
 *    machine language could be already compiled code in the program
 * 4. The attacker must overwrite the stack pointer. The old value,
 *    directing the flow of the program after the function is returned,
 *    must be changed from the calling function to the provided
 *    machine language in step 3.
 *********************************************/
void stackExploit()
{
	long int buffer[12] =                    //1. more data
	{ 0,1,2,3,4,5,6, (long int)&hacked };      //2. stakpointer 3.pointer

	stackVulnerability(buffer, 8);

	cout << "You missed. Not able to hack\n";
}

/**************************************************************
 **************************************************************
 ********************      HEAP      **************************
 **************************************************************
 **************************************************************/


 /*************************************
  * HEAP VULNERABILITY
  * 1. There must be two adjacent heap buffers.
  * 2. The first buffer must be reachable through external input.
  * 3. The mechanism to fill the buffer from the external input must
  *    not correctly check for the buffer size.
  * 4. The second buffer must be released before the first.
  *************************************/
void heapVulnerability(long* input, long size)
{
	long* buffer1 = new long[4];
	long* buffer2 = new long[4];

	// two heap must be aligned
	assert(buffer1 < buffer2);                //1. Adjustment
	assert(buffer1 + 6 == buffer2);

	//we will overwrite the first buffer
	for (int i = 0; i < size; i++)           //Incorrect bound checking
	{
		buffer1[i] = input[i];                // 2. input is provided by attacker
	}

	delete[] buffer2;                       //4. Relese 2nd first
	delete[] buffer1;
}

/*************************************
 * HEAP EXPLOIT
 * 1. The attacker must provide more data into the outwardly facing
 *    heap buffer than the buffer is designed to hold
 * 2. The attacker must know the layout of the Memory Control Block (MCB)
 *    (essentially a linked list) residing just after the buffer
 * 3. The attacker must provide a new MCB containing both the location
 *    of the memory overwrite and the new data to be overwritten
 ***********************************/
void heapExploit()
{
	long int buffer[6] =             //1. more data than heap size
	{ 0, 0, 0, 0, -1, -1 };         //3. & 2.  heap spraying

	heapVulnerability(buffer, sizeof(buffer) / sizeof(buffer[0]));

	cout << "You missed. Not able to hack\n";
}


/**************************************************************
 **************************************************************
 *******************    INTEGER      **************************
 **************************************************************
 **************************************************************/

 /********************************************
  * INTEGER VULNERABILITY
  * 1. There must be a security check represented by an expression.
  * 2. The expression must have the potential for overflow.
  * 3. At least one of the numbers used to compute the sentinel
  *    must be reachable through external input.
  *********************************************/
void intVulnerability(const char* input)    //3. external input
{
	char output[32];
	bool danger = false;

	char sizeInput = strlen(input);        //2. potential for overflow
	char sizeOutput = sizeof(output);

	//copy the buffer - protected
	if (sizeInput < sizeOutput)            //1. security check
		strcpy(output, input);

	//I hope nothing bad happens!
	if (danger)
		cout << "You have been hacked.\n";
	else
		cout << "All is safe; nothing bad happened.\n";
}

/**********************************************
 * INTEGER EXPLOIT
 * 1. Provide input, either a buffer size or a single value,
 *    that is directly or indirectly used in the vulnerable expression
 * 2. The input must exceed the valid bounds of the data-type,
 *    resulting in an overflow or underflow condition
 **********************************************/
void intExploit()
{
	// Note :: According to Brother Helfrich 
	char text[] =
		"This text must be longer than 128 characters and less than 256 because 128, when cast to char, is -128. 256 when cast to a char is 0. This text is 189 characters in length is actually -67";

	intVulnerability(text);   // 1. used by strlen() to compute value  2. The value is 189 which is -67 as a char
}


/**************************************************************
 **************************************************************
 ******************    ANSI-Unicode    ************************
 **************************************************************
 **************************************************************/

 /*********************************************************
  * ANSI - UNICODE VULNERABILITY
  * 1. There must be a buffer where the basetype is greater than one.
  * 2. Validation of the buffer must check the size of the buffer
  *    rather than the number of elements in the buffer.
  ********************************************************/
void ansiVulnerability(const char* ansi, int size)
{
	short unicode[4];                    //basetype of short
	bool safe = true;

	//check to make sire our buffer is the right size
	if (size <= sizeof(unicode))        //2. Validate checks sizeof(unicode)
	{
		int i = 0;
		for (int j = 0; j < size; j++)
		{
			unicode[i] = (short)ansi[i];
			cout << i << "Size = " << size << "Safe = " << safe << "                   ";
			cout << j << "Size = " << size << "Safe = " << safe << endl;

			i++;
		}
	}

	//do the safety check
	if (safe)
		cout << "All is safe; nothing has happened.\n";
	else
		cout << "You have been Hacked.\n";
}

/***********************************************
 * ASCI - UNICODE EXPLOIT
 * 1. The attacker must provide more than half as much data
 *    into the outwardly facing buffer as it is designed to hold
 **********************************************/
void ansiExploit()
{
	char input[6] = "ANSI";
	cout << " Am i here?";

	ansiVulnerability(input, sizeof(input));
}
