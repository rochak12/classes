/***********************************************************************
* Program:
*    Lab C_lab, ECEN 324 Learning C Lab
*    Brother Jones, ECEN 324
* Author:
*    Rochak Kunwar
* Summary:
*    Lab 01 of Ecen 324
************************************************************************/

#include <stdlib.h>
#include <stdio.h>

#define PI 3.1415926



int main (void) {
    const char LETTER = 'A';
    int n1 = 24;
    
    /* %d is is for integer 
     *  %f is for floating point
     *  %.5 does 5 precision
     *  %c is for char
     *  %x is for hexa
     */ 
    printf("%d\n%.5f\n%c\n", n1, PI, LETTER);
    float payRate = 10.50;
    int hours = 40;


    printf("Users pay rate: $%.1f\n", payRate);
    printf(" Hours worked: %d\n", hours);
    printf("    Gross Pay: $%.f\n", hours * payRate);
    int number;
    
    //this is the syntax of cerr in c++ is stderr in C
    fprintf(stderr, "Enter number: ");
    //scanf is cin of C. and do not forget "&" sign infront of input
    scanf("%d", &number);
    printf("Twice %d is %d\n", number, number * 2);


  /*  %10d means setwidth of 10 and rightalign d-int by default
   *  %-10d means setwidth of 10 and left aligh d-int
   *  whereas %.10f means 10 point precision
   */
    int anInt = 99;
    float aFloat = 43.2;
    printf("\n");
    printf("Integer: %d ###\n", anInt);
    printf("Integer: %10d ###\n", anInt);
    printf("Integer: %-10d ###\n\n", anInt);
    printf("  Float: %.1f ###\n", aFloat);
    printf("  Float: %-10.1f ###\n", aFloat);
    printf("  Float: %10.2f ###\n", aFloat);
    printf("  Float: %.3f ###\n", aFloat);
    printf("  Float: %10.3f ###\n", aFloat);
    printf("  Float: %-10.4f ###\n", aFloat);



/*   decimals or any type can be converted into 
 *  hex, oct, or char just by the use of type casting
 */
    printf("\n\tOct   Dec   Hex   Char\n");
    printf("\t----------------------\n");
    int i = (int) 'a';
    for (i; i <= (int) 'z'; i++) {
        printf("\t%-6o%-6d%-6x%c\n", i, i, i, i);
    }




    int *p1;
    int *p2;

   // same as p1 = new *int;
   // malloc and free are keywords for dynamic memory allocation in C
    p1 = malloc(sizeof(*p1));
    *p1 = 42;
    p2 = p1;
    printf("\n*p1 == %d\n", *p1);
    printf("*p2 == %d\n", *p2);

    *p2 = 53;
    printf("*p1 == %d\n", *p1);
    printf("*p2 == %d\n", *p2);
    p1 = malloc(sizeof(*p1));
    *p1 = 88;
    printf("*p1 == %d\n", *p1);
    printf("*p2 == %d\n", *p2);
    printf("Hope you got the point of this example!\n");
    printf("");

    free(p1);
    free(p2);

    return 0;

}