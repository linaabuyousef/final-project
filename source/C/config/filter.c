#include "../../../header/config/filter.h"
#include "../../../header/utility/Reads.h"
#include "../../../header/utility/strParce.h"
#include "../../../header/utility/macros.h"

void M_Block(simType type , LinkedList* list , char** filterLines , int lineCount ,int n ,int k){
    
    char* currLine = filterLines[0];

    int m =  parceInt(currLine);
    
    Orbit* orbit = (Orbit*)malloc(sizeof(Orbit));
    orbit->n = n;
    orbit->k = k;
    orbit->m = m;

    L_Append(list,orbit);

    return;
}

void K_Block(simType type , LinkedList* list , char** filterLines , int lineCount ,int n){

    int k = 0;
    for(int i = 0 ; i < lineCount ; i++){
        char* currLine = filterLines[i];
        if(strstr(currLine,"K")!= NULL){
            k =  parceInt(currLine);
            if(type == POLAR || type == REL_POLAR){
                
                Orbit* orbit = (Orbit*)malloc(sizeof(Orbit));
                orbit->n = n;
                orbit->k = k;
                orbit->m = -1;

                L_Append(list,orbit);
                return;
            }

        }
        if(strstr(currLine,"{}")!= NULL){ // if the block is empty simulate all
                
            if(type == SPIN || type == SPHERICAL || type == REL_SPHERICAL){
                
                for(int m = 0 ; m <= k ; m++){
                    
                    Orbit* orbit = (Orbit*)malloc(sizeof(Orbit));
                    orbit->n = n;
                    orbit->k = k;
                    orbit->m = m;

                    L_Append(list,orbit);
                    
                }

            }else{
                
                Orbit* orbit = (Orbit*)malloc(sizeof(Orbit));
                orbit->n = n;
                orbit->k = k;
                orbit->m = -1;

                L_Append(list,orbit);
                    
            }
            return;
        
        }else if(strstr(currLine,"M") != NULL){// block not empty

            M_Block(type,list,filterLines+i,lineCount-i,n,k);

        }else if(strstr(currLine,"}") != NULL){
            return;
        }


    }

}

void N_Block(simType type , LinkedList* list , char** filterLines , int lineCount){
    
    int n = 0;

    for(int i = 0 ; i < lineCount ; i++){
        char* currLine = filterLines[i];
        if(strstr(currLine,"N")!= NULL){
            n =  parceInt(currLine);
            if(strstr(currLine,"{}")!= NULL){ // if the block is empty simulate all
                for(int k = 1 ; k <= n ; k++){
                    
                    if(type == SPIN || type == SPHERICAL || type == REL_SPHERICAL){
                        
                        for(int m = 0 ; m <= k ; m++){
                            
                            Orbit* orbit = (Orbit*)malloc(sizeof(Orbit));
                            orbit->n = n;
                            orbit->k = k;
                            orbit->m = m;

                            L_Append(list,orbit);
                            
                        }

                    }else{
                        
                        Orbit* orbit = (Orbit*)malloc(sizeof(Orbit));
                        orbit->n = n;
                        orbit->k = k;
                        orbit->m = -1;

                        L_Append(list,orbit);
                        
                    }
                }
            }
        }else if(strstr(currLine,"K") != NULL){// block not empty
            K_Block(type,list,filterLines+i,lineCount-i,n);
        }

    }

}


char* printFilter(void* data){
    
    Orbit* orbit = (Orbit*) data;

    char* printStr = malloc(20);
    
    memset(printStr,(int)'\0',20);

    sprintf(printStr,"[%hi %hi %hi]",orbit->n,orbit->k,orbit->m);
    
    return printStr;

}

LinkedList* getFilterList(simType type){
    
    LinkedList* list = newLinkedList();

    FILE* filterFile = fopen(FILTER_PATH,"r");

    int lineCount = -1;
    
    char** filterLines = readLines(filterFile,&lineCount);

    N_Block(type,list,filterLines,lineCount);

    for(int i = 0 ; i < lineCount ; i++){
        free(filterLines[i]);
    }
    
    free(filterLines);
    fclose(filterFile);
    LinkedList_print(list,printFilter);
    return list;

}
