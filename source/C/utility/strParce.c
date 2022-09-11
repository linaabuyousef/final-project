#include "../../../header/utility/strParce.h"


int parceInt(char* str){

    int n = strlen(str);
    bool isZero = false;
    int num = 0;
    short sig = 1;
    for(int i = 0 ; i < n ; i++){
        if(str[i] == '-'){
            sig = -1;
        }
        int curr_num = (int)(str[i]);
        if(curr_num >= 0x30 && curr_num <= 0x39){
            if(curr_num == 0x30){
                isZero = true;
            }
            num*=10;
            num+=(sig*(curr_num-0x30));

        }else if(num != 0){
            break;
        }else if(isZero){
            break;
        }
    }
    return num;
}

long parceLong(char* str){

    int n = strlen(str);
    bool isZero = false;
    long num = 0;
    short sig = 1;
    for(int i = 0 ; i < n ; i++){
        if(str[i] == '-'){
            sig = -1;
        }
        int curr_num = (int)(str[i]);
        if(curr_num >= 0x30 && curr_num <= 0x39){
            if(curr_num == 0x30){
                isZero = true;
            }
            num*=10;
            num+=(sig*(curr_num-0x30));

        }else if(num != 0){
            break;
        }else if(isZero){
            break;
        }
    }
    return num;
}

short parceShort(char* str){

    int n = strlen(str);
    bool isZero = false;
    short num = 0;
    short sig = 1;
    for(int i = 0 ; i < n ; i++){
        if(str[i] == '-'){
            sig = -1;
        }
        int curr_num = (int)(str[i]);
        if(curr_num >= 0x30 && curr_num <= 0x39){
            if(curr_num == 0x30){
                isZero = true;
            }
            num*=10;
            num+=(sig*(curr_num-0x30));

        }else if(num != 0){
            break;
        }else if(isZero){
            break;
        }
    }
    return num;
}

float parceFloat(char* str){

    int n = strlen(str);
    float num = 0;
    bool isZero = false;
    short sig = 1;
    short disp = 0;
    short powoft = 0;
    for(int i = 0 ; i < n ; i++){

        if(str[i] == '-'){
            sig = -1;
        }
        if(str[i] == '.'){
            disp = 1;
            continue;
        }
        int curr_num = (int)(str[i]);

        if(str[i]== 'E'){
            powoft += parceInt((str+i));
            break;
        }else if((curr_num >= 0x30 && curr_num <= 0x39) || disp == 1){
            if(curr_num == 0x30){
                isZero = true;
            }
            if(disp){
                powoft--;
            }
            num*=10;
            num+=(sig*(curr_num-0x30));
        }else if(num != 0){
            break;
        }else if(isZero){
            break;
        }
    }
    return num*pow(10,powoft);
}

double parceDouble(char* str){
    int n = strlen(str);
    double num = 0;
    bool isZero = false;
    short sig = 1;
    short disp = 0;
    short powoft = 0;
    for(int i = 0 ; i < n ; i++){

        if(str[i] == '-'){
            sig = -1;
        }
        if(str[i] == '.'){
            disp = 1;
            continue;
        }
        int curr_num = (int)(str[i]);

        if(str[i]== 'E'){
            powoft += parceInt((str+i));
            break;
        }else if((curr_num >= 0x30 && curr_num <= 0x39) || disp == 1){
            if(curr_num == 0x30){
                isZero = true;
            }
            if(disp){
                powoft--;
            }
            num*=10;
            num+=(sig*(curr_num-0x30));
        }else if(num != 0){
            break;
        }else if(isZero){
            break;
        }
    }
    return num*pow(10,powoft);
}

int* parceIntArray(char* str,int* size){



    int* arr = NULL;    
    int j = 0;
    while ((int)str[j]< 0x30 || (int)str[j]< 0x30)
    {
        j++;
    }
    
    int n = strlen(str);
    int numCount = 0;
    for(int i = j ; i < n ; i++){
        if(str[i]==',' || i == n-1){
            numCount++;
            if(numCount == 1){
                arr = (int*)malloc(sizeof(int)*numCount);
            }else{
                arr = (int*)realloc(arr,sizeof(int)*numCount);
            }
            arr[numCount-1] = parceInt((str+j));
            j = i+1;
        }
    }
    *size = numCount;
    return arr;

}

double* parceDoubleArray(char* str,int* size){

    if(((int)str[0]) < 0x30 ||((int)str[0])>0x39){
        return NULL;
    }
    double* arr = NULL;    
    int j = 0;
    int n = strlen(str);
    int numCount = 0;
    for(int i = 0 ; i < n ; i++){
        if(str[i]==',' || i == n-1){
            numCount++;
            if(numCount == 1){
                arr = (double*)malloc(sizeof(double)*numCount);
            }else{
                arr = (double*)realloc(arr,sizeof(double)*numCount);
            }
            arr[numCount-1] = parceDouble((str+j));
            j = i+1;
        }
    }
    (*size)= numCount;
    return arr;

}

#ifdef LINKEDLIST_H_

LinkedList* parceIntLinkedList(char* str){

    
    int size = strlen(str);
    bool leftBrakit;
    LinkedList* list = NULL;

    for(int i = 0 ; i < size ; i++){
        

        if(str[i] == '[' && !leftBrakit){
            leftBrakit = true;
            list = newLinkedList();
        
        }else if(str[i] == '['){
        
            LinkedList_append(list,parceIntLinkedList(str+i));
            
            while (str[i] == '\0'){
                i++;
            }
            i--;
        
        }else if((int)str[i] >= 0x30 && (int)str[i] <= 0x39){
            
            int numData = parceInt(str+i);
            int* nodeData = (int*) malloc(sizeof(int));
            *nodeData = numData; 
            LinkedList_append(list,nodeData);

            while ((int)str[i] >= 0x30 && (int)str[i] <= 0x39)
            {
                str[i] = '\0';
                i++;
            }
            i--;
            
        }else if(str[i] == ']' && leftBrakit){
            str[i] = '\0';
            return list;
        
        }
        str[i] = '\0';
    }

}

#endif