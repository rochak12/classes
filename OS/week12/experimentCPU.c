/***********************************************************************
 * Program:
 *    Experiment 02, CPU
 *    CS 345
 * Author:
 *    A former BYU-Idaho student
 * Summary:
 *    This program demonstrates the use of threads to perform matrix
 *    multiplication.  By using the time command from the terminal, I was
 *    able to obtain casual measurements on the effects different numbers
 *    of threads have on the running time of a program on single-processor
 *    and multiprocessor machines.
 *
 *    You may wish to make modifications to this program when doing
 *    experiments for the White Paper, but you will not be submitting
 *    this code.
 *
 *    Compile with code with:
 *         gcc experimentCPU.c -lpthread
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <bits/pthreadtypes.h>
#include <time.h>
#include <semaphore.h>

#define INDEX(horizontal_value, vertical_value, width) \
   ((horizontal_value) + ((vertical_value) * (width)))

int * MATRIX_A;
int MATRIX_A_WIDTH;
int MATRIX_A_HEIGHT;

int * MATRIX_B;
int MATRIX_B_WIDTH;
int MATRIX_B_HEIGHT;

int * MATRIX_C;
int MATRIX_C_WIDTH;
int MATRIX_C_HEIGHT;

#define MAX_THREADS 1000
int numThreads;

/************************************************************************
 * DISPLAY MATRIX
 * Print the contents of a given integer array, formatted as though it were a
 * width by height matrix.  Calls to this function are currently commented out,
 * but I have included it so that you may doublecheck the accuracy of my matrix
 * multiplication (if desired).
 ***********************************************************************/
void displayMatrix(int * matrix, int width, int height) 
{
   int x;
   int numElements = width * height;

   // initial display
   printf("Dumping %i x %i matrix: %x",width, height, matrix);

   // display the contents of the matrix
   for (x = 0; x < numElements; x++) 
   {
      if (x % width == 0)
         printf("\n");
      printf ("  %i  ", matrix[x]);      
   }
   
   printf("\n");
}

/********************************************************************
 * CREATE MATRIX
 * Returns a reference to an integer array of the requested width and height,
 * which has been filled with random numbers.  Also, takes care of allocating
 * memory for that integer array.
 ********************************************************************/
int * createMatrix(int width, int height) 
{
   int x;
   int numElements = width * height;
   int * matrix = (int *) malloc(numElements * sizeof(int));

   // fill in the matrix with random numbers
   for (x = 0; x < numElements; x++) 
   {
      matrix[x] = rand() % 100;
   }
   return matrix;
}

/******************************************************************
 * WORKER
 * Each thread created calls this function.  Each Xth of Y threads is
 * responsible for calculating every Yth row.  In other words, in a
 * 10 x 10 matrix, thread number 1 of 3 will calculate rows #1, 4, 7, 10;
 * thread number 2 of 3 will calculate rows #2, 5, 8; and thread number
 * 3 of 3 will calculate rows #3, 6, 9.
 *
 * I chose to assign rows to a thread, instead of creating a pool of
 * tasks, because each row will require (almost) exactly the same
 * amount of work as any other row, so we can be confident that we
 * are dividing the work evenly without spending extra processing
 * time on complex scheduling routines.
 ****************************************************************/
void * worker(void * p) 
{
   int threadNum = * ((int *) p);
   int row = threadNum;
   int col; 
   int x;
   int total;
      
   // printf("worker thread #%i created\n", thread_num);

   // perform the matrix multiplication
   while (row < MATRIX_A_HEIGHT) 
   {
      for (col = 0; col < MATRIX_A_WIDTH; col++) 
      {
         int aPos = INDEX(0, col, MATRIX_A_WIDTH);
         int bPos = INDEX(row, 0, MATRIX_B_WIDTH);
         total = 0;
         for (x = 0; x < MATRIX_A_WIDTH; x++) 
         {
            total += MATRIX_A[aPos] * MATRIX_B[bPos];
            aPos += 1;
            bPos += MATRIX_B_WIDTH;
         }
         MATRIX_C[INDEX(row, col, MATRIX_C_WIDTH)] = total;
      }
      row += numThreads;
   }
   
   // printf("worker thread #%i exiting\n", thread_num);
   
   free (p);
}

/************************************************
 * PERFORM EXPERIEMENT
 * Launch all the threads to perform the multiplications
 ************************************************/
void performExperiment()
{
   // create and start the worker threads
   int x;
   int *pointer;
   pthread_t threads[MAX_THREADS]; 
   for (x = 0; x < numThreads; x++) 
   {
      pointer = (int *) malloc(sizeof(int));
      *pointer = x;
      pthread_create( &threads[x], 
                      NULL,    //No special arguments for the thread type
                      worker,  //have the thread call the worker() function
                      pointer  //Pass a reference to the variable 
                               //holding that threads number
                      );   
   }
   
   // stall the main program until all of the threads have finished executing.
   for (x = 0; x < numThreads; x++) 
   {
      pthread_join(threads[x], NULL);   
   }
   
   // you may optionally un-comment this section to check the correctness
   // of the matrix multiplication    
   //displayMatrix(MATRIX_A, MATRIX_A_WIDTH, MATRIX_A_HEIGHT);
   //displayMatrix(MATRIX_B, MATRIX_B_WIDTH, MATRIX_B_HEIGHT);
   //displayMatrix(MATRIX_C, MATRIX_C_WIDTH, MATRIX_C_HEIGHT);
}

/*********************************************************
 * MAIN
 * Parse the command line and launch the experiment
 ********************************************************/
int main(int argc, char ** argv)
{
   // verify we have the correct number of parameters
   if (argc != 6) 
   {
      printf("ERROR: Unexpected number of arguments. Usage:\n" \
             "\texperimentCPU.out <matrix A rows> <A cols> "\
             "<B rows> <B cols> <# threads>\n");
      return 1;
   }
   
   //convert the argument from a string to a number   
   MATRIX_A_HEIGHT = atoi(argv[1]);
   MATRIX_A_WIDTH  = atoi(argv[2]);
   MATRIX_B_HEIGHT = atoi(argv[3]);
   MATRIX_B_WIDTH  = atoi(argv[4]);   
   numThreads      = atoi(argv[5]);
   
   // double-check the size of the matricies
   if (MATRIX_A_WIDTH != MATRIX_B_HEIGHT) 
   {
      printf("By definition of matrix multiplication, "\
             "Matrix A Width must equal Matrix B Height. Usage:\n");
      printf("\texperimentCPU.out <matrix A rows> <A cols> "\
             "<B rows> <B cols> <# threads>\n");
      return 1;
   }
   
   // fill the first and second matrix with random integers.   
   MATRIX_A = createMatrix(MATRIX_A_WIDTH, MATRIX_A_HEIGHT);
   MATRIX_B = createMatrix(MATRIX_B_WIDTH, MATRIX_B_HEIGHT);
   
   // prepare matrix C to recieve the results of the multiplication
   MATRIX_C_HEIGHT = MATRIX_A_HEIGHT;
   MATRIX_C_WIDTH = MATRIX_B_WIDTH;   
   MATRIX_C = (int *) malloc(MATRIX_C_WIDTH * MATRIX_C_HEIGHT * sizeof(int));

   //
   // all the work is done here.
   //
   performExperiment();

   // free the memory allocated by create_matrix   
   free(MATRIX_A);
   free(MATRIX_B);
   free(MATRIX_C);

   return 0;
}

