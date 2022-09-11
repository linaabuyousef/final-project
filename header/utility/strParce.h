#ifndef STRPARCE_H_
#define STRPARCE_H_

#include "types.h"
#include "linkedList.h"
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

/**

    converts string to int value

    @param char* str the string to convert 
    @return int the value of the number inside the string
*/
int parceInt(char* str);


/**

    converts string to long value

    @param char* str the string to convert 
    @return long the value of the number inside the string
*/
long parceLong(char* str);


/**

    converts string to short value

    @param char* str the string to convert 
    @return short the value of the number inside the string
*/
short parceShort(char* str);


/**

    converts string to float value the function can also convert the numbers of the format (1.0E-19)

    @param char* str the string to convert 
    @return float the value of the number inside the string
*/
float parceFloat(char* str);


/**

    converts string to float value the function can also convert the numbers of the format (1.0E-19)

    @param char* str the string to convert 
    @return double the value of the number inside the string
*/
double parceDouble(char* str);

#ifdef LINKEDLIST_H_
    LinkedList* parceIntLinkedList(char* str);
#endif

/**

    converts string to int* array

    @param char* str the string to convert int* n the size of the array after parcing
    @return int* the array of the numbers inside the string note: this function uses malloc to create the array of numbers  
    the retruned pointer needs to be fread to avoid memory leaks
*/
int* parceIntArray(char* str ,int* n);
/**

    converts string to double array

    @param char* str the string to convert int* n the size of the array after parcing
    @return double* the array of the numbers inside the string note: this function uses malloc to create the array of numbers
    the retruned pointer needs to be fread to avoid memory leaks  
*/
double* parceDoubleArray(char* str ,int* n);

#endif // STRPARCE_H_