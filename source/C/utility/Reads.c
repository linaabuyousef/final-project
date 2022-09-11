#include "../../../header/utility/Reads.h"

char* get_filepath(char* str){

    char* path = NULL;

    int length = strlen(str);

    for(int i = 0 ; i < length ; i++){
        
        if(str[i] == '='){
            i+=2;
            int pathlength = strlen((str+i));
            path = (char*)malloc(pathlength+1);
            strcpy(path,(str+i));
        
            for(int j = pathlength ; j> 0 ; j--){
        
                if(path[j]=='\"'){
                    path[j] = '\0';
                    break;
                }
            }
            return path;
        }
    }
    return path;
}

char* readLine(FILE* fd){
    
    char curr_char[1];
    int length = 0;
    char* lineBuffer = NULL;

    while(fread(curr_char,1,1,fd) > 0){        
        if(length == 0){
            lineBuffer = (char*)malloc(2);
        }else{
            lineBuffer = (char*)realloc(lineBuffer,length+2);
        }
        lineBuffer[length] = curr_char[0];
        if(curr_char[0] == '\n'){
            break;
        }
        length++;
    }
    if(lineBuffer != NULL){
        lineBuffer[length] = '\0';
    }
    return lineBuffer;
}

char** readLines(FILE* fd, int* n){
    
    fseek(fd,0,SEEK_SET);

    char** Lines = NULL;
    int length = 0;
    char* line;
    
    while((line = readLine(fd))!= NULL){
        if(length == 0){
            Lines = (char**)malloc(sizeof(char*));
        }else{
            Lines = (char**)realloc(Lines,sizeof(char*)*(length+2));
        }
        Lines[length] = line;
        length++;
        (*n)--;
        if(*n == 0){    
            break;
        }
    }
    (*n) = length;
    return Lines;
}

