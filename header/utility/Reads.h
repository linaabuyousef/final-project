

#ifndef READS_H_
#define READS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/**

    return from a given char* the url in the string  

    @param char* str expected format "path ="<URL>""
    @return char* with the extracted url


*/
char* get_filepath(char* str);
/**

    reads one line from a given file  

    note: this function uses malloc and realloc so the returned value must be freed after use

    @param FILE* fd file expected to be opend with fopen with read access
    @return char* containing the line read from file / NULL if the file is empty or all lines are already read


*/
char* readLine(FILE* fd);
/**

    reads n lines from a given file  

    note: this function uses malloc and realloc so the returned value must be freed after use

    @param FILE* fd file expected to be opend with fopen with read access , int* n = number of lines to read -1 => all lines 
    @return char** conataing the lines read each line is saved in char* and are sorted according to the orignal file 
            int* n the value inside n is changed according to the number of lines read from the file    
            
*/
char** readLines(FILE* fd, int* n);


#endif // READS_H_
