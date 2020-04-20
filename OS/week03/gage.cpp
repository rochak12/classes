/***********************************************************************
 * Program:
 *    Lab 03, Shell Lab
 *    Brother Ball, CS 345
 * Author:
 *    Gage Mikos
 * Summary:
 *    Enter a brief description of your program here!
 *    Referenced: http://www.cplusplus.com/forum/general/46540/
 *                http://www.cs.ecu.edu/karl/4630/sum01/example1.html
 ************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <cstdlib>
#include <sys/types.h>
#include <sys/wait.h>
#include <cstring>

#define MAX_LINE 80 /* 80 chars per line, per command, should be enough. */

// Used to indicate if a SIGQUIT signal is caught
//int SIGQUIT_FLAG = 0;

void printHistory()
{
   printf("Signal Caught.\n");
}

void handle_SIGQUIT( int junk )
{
   //SIGQUIT_FLAG = 1;
   printHistory();
   
   // we want to continue execution so we use return
   return;
}

/***************************************************************************
 * SETUP
 * setup() reads in the next command line, separating it into distinct tokens
 * using whitespace as delimiters.
 *
 * setup() modifies the inputBuffer creating a set of null-terminated strings
 * and places pointers into the args[] array that point to the beginning of
 * each argument.  A NULL pointer is placed in the args[] array indicating
 * the end of the argument list.  This is what is needed for using execvp().
 *
 * A ^d input at the beginning of a line, by a user, exits the shell.
 **************************************************************************/
void setup(char inputBuffer[], char * args[], int * background, char (*ptr)[999][80], int * rowCounter)
{
   int length; // # of characters in the command line 
   int i;      // loop index for accessing inputBuffer array 
   int start;  // index where beginning of next command parameter is 
   int ct;     // index of where to place the next parameter into args[] 
    
   ct = 0;
    
   /* read what the user enters on the command line */
   length = read(STDIN_FILENO, inputBuffer, MAX_LINE);  

   start = -1;            /* Used as a flag to indicate that we are looking
                           * for the start of the command or an argument if
                           * it is a -1, or stores the starting position of
                           * the command or argument to be put in args[].
                           */
   if (length == 0)
      exit(0);            /* ^d was entered, end of user command stream */
   if (length < 0)
   {
      perror("error reading the command");
      exit(-1);           /* terminate with error code of -1 */
   }

   /* examine every character in the inputBuffer */
   for (i = 0; i < length; i++)
   { 
      switch (inputBuffer[i])
      {
         case ' ':
         case '\t' :               /* argument separators */
            if(start != -1)        /* found the end of the command or arg */
            {
               args[ct] = &inputBuffer[start]; /* set up pointer in args[] */
               ct++;
            }
            inputBuffer[i] = '\0'; /* add a null char; make a C string */
            start = -1;
            break;

         case '\n':                 /* should be the final char examined */
            if (start != -1)        /* if in the command or an argument */
            {
               args[ct] = &inputBuffer[start]; /* set up pointer in args[] */ 
               ct++;
            }
            inputBuffer[i] = '\0';
            args[ct] = NULL; /* no more arguments to this command */
            break;

         default :             /* some other character */
            if (start == -1 && inputBuffer[i] != '&')
               start = i;      /* starting position of the command or arg */
            if (inputBuffer[i] == '&')
            {
               *background  = 1;
               inputBuffer[i] = '\0';
            }
      }  /* end of switch */
   }  /* end of for loop looking at every character */
   
   // Copy to history buffer
   strncpy ((char *)ptr, inputBuffer, 80);
   *++ptr;
   ++(*rowCounter);
   
   args[ct] = NULL; /* just in case the input line was > 80 */
} 

void execute(char *args[], int * background)
{
    pid_t childPid;
    int childStatus;
    
    childPid = fork();
    
    // Child process.
    if(childPid == 0)
    {
        execvp(args[0], args);
        
        // We will only get here if execvp returns an error
        
        printf("command not found\n");
    }
    // Error Case
    else if (childPid < 0)
    {
        perror("ERROR: forking child process failed");
        exit(-1);           /* terminate with error code of -1 */
    }
    // Parent process
    else 
    {
        // Case where parent will wait for child process to end.   
        if (*background != 1)
        {
          waitpid(childPid, NULL, 0);
        }
        // Else the parent will run concurrently.
    }    
}

int main(void)
{

   /* set up the signal handler */
   struct sigaction handler;
   handler.sa_handler = handle_SIGQUIT;   /* function the handler will call */
   handler.sa_flags = SA_RESTART;
   sigaction(SIGQUIT, &handler, NULL);    /* handler to call for QUIT signal */

   char inputBuffer[MAX_LINE]; /* buffer to hold the command entered */
   int background;             /* equals 1 if a command is followed by '&' */
   char *args[MAX_LINE/2];   /* command line (of 80) has max of 40 arguments */
   
   int rows = 999; /* Hold up to 999 commands */

   char buff [999][80]; 
   char (*ptr)[999][80];
   ptr = &buff;
   
   int counter;
   int * rowCounter;
   
   rowCounter = &counter;
   *rowCounter = 0;
    
   while (1)                   /* Program terminates normally inside setup */
   {
      background = 0;
      printf(" COMMAND-> ");
      fflush(stdout);
      setup(inputBuffer, args, &background, ptr, rowCounter);       /* get next command */
      
      execute(args, &background);
      
      printf("The next command will be command number: %d\n", counter);
      printf("The last command was %s\n", buff[0]);
   }
}

