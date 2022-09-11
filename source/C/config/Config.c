#include "../../../header/config/Config.h"
#include <time.h>


/**
 * @brief  check if a given folder exists 
 * 
 * @param filename :path to file 
 * @return true if file exists
 * @return false if file does not exist 
 */
bool file_exists (char *filename) {
    struct stat   buffer;   
    return (stat (filename, &buffer) == 0);
}
/**
 * @brief generates the time stamp combining the current date and time 
 * 
 * @return char* current time in formatt YY.MM.DD_HH.MM.SS
 */
char* genrateTimeStamp(){

    time_t pctime = time(NULL);
    struct tm localTime = *localtime(&pctime);
    char* timeStr = (char*) malloc(100);

    sprintf(timeStr,"%02d.%02d.%02d_%02d.%02d.%02d", localTime.tm_year - 100  , localTime.tm_mon + 1, localTime.tm_mday, localTime.tm_hour, localTime.tm_min, localTime.tm_sec);

    return timeStr;

}
/**
 * @brief returns pointer to the results file for given orbit
 * 
 * @param orbit Struct orbit {n,k,m}
 * @param genratedTimeStamp time stamp used to finde approprite file
 * @return FILE* 
 */
FILE* getOrbitFile(Orbit orbit,char* genratedTimeStamp){

    int len = strlen(genratedTimeStamp);
    char orbitPath[len+100];

    if(orbit.m == -1){
        
        sprintf(orbitPath,"%s/%s/results_N%hi/results_K%hi.txt",RESULT_P,genratedTimeStamp,orbit.n,orbit.k);
        
    }else{

        sprintf(orbitPath,"%s/%s/results_N%hi/results_K%hi/results_M%hi.txt",RESULT_P,genratedTimeStamp,orbit.n,orbit.k,orbit.m);

    }
    
    FILE* logFile =  fopen(orbitPath,"w");
    
    return logFile;
}
/**
 * @brief creates a copy of the current config file as meta.txt
 * 
 * @param path path to save copy
 * @return int 1 succses -1 fail
 */
int saveMetaData(char* path){

    FILE* config_f = fopen(CONFIG_PATH,"r");
    if (config_f == NULL){
        printf("ERROR opening Config file");
        exit(EXIT_FAILURE);
    }

    FILE* meta = fopen(path,"w");

    if (meta == NULL){
        printf("ERROR opening meta file");
        exit(EXIT_FAILURE);
    }
    int n = -1;
    char** configLines = readLines(config_f,&n);
    
    for (int i = 0 ;i < n ; i++ ){
        fprintf(meta,"%s\n",configLines[i]);
        free(configLines[i]);
    }
    free(configLines);
    fclose(config_f);
    fclose(meta);
    return 1;
}
/**
 * @brief Create a Results Path for all the folders and subfolders for results txt files
 * 
 * @param filterList LinkedList* of the current orbits to simulate
 * @return char* the current time stamp
 */
char* createResultsPath(LinkedList* filterList){
    
    char* path = genrateTimeStamp(); 
    char command[200];
    
    memset(command,0,200);

    int last_n = 0;
    int last_k = 0;
    int listSize = L_Size(filterList);
    if (!file_exists(RESULT_P)){
        sprintf(command,"mkdir %s",RESULT_P);
        if(system(command)<0){
            printf("error creating file");
            return NULL;
        }
    }
    #ifdef _WIN32 // make dir for windows
        sprintf(command,"mkdir %s\\%s",RESULT_P,path);
    #endif
    #ifndef _WIN32
        sprintf(command,"mkdir %s/%s",RESULT_P,path);
    #endif
        if(system(command)<0){
            printf("error creating file");
            return NULL;
        }

    for(int i = 0 ; i < listSize ; i++){
        Orbit* orbit = (Orbit*)L_Pop(filterList);

        if(orbit->n > last_n){
            #ifdef _WIN32 // make dir for windows
                sprintf(command,"mkdir %s\\%s\\results_N%hi",RESULT_P,path,orbit->n);
            #endif

            #ifndef _WIN32
                sprintf(command,"mkdir %s/%s/results_N%hi",RESULT_P,path,orbit->n);
            #endif
            
            if(system(command)<0){
                printf("error creating file");
                return NULL;
            }

            last_k = 0;
            last_n = orbit->n;
        }
        if(orbit->k > last_k && orbit->m != -1){
            #ifdef _WIN32 // make dir for windows
                sprintf(command,"mkdir %s\\%s\\results_N%hi\\results_K%hi",RESULT_P,path,orbit->n,orbit->k);
            #endif

            #ifndef _WIN32
                sprintf(command,"mkdir %s/%s/results_N%hi/results_K%hi",RESULT_P,path,orbit->n,orbit->k);
            #endif
                    
            if(system(command)<0){
                printf("error creating file");
                return NULL;
            }

            
            last_k = orbit->k;
        }

        L_Append(filterList,orbit);

    }
    
    return path;
}

Config* getInitVals(){
    

    FILE* config_f = fopen(CONFIG_PATH,"r");
    if (config_f == NULL){
        perror("ERROR opening Config file");
        exit(EXIT_FAILURE);
    }


    int length = -1;
    
    char** configLines = readLines(config_f,&length);

    Config* config = (Config*)malloc(sizeof(Config));
    for(int i = 0 ; i < length ; i++){
    
        char* currLine = configLines[i];

        if(strstr(currLine,"revolutions =") == currLine){
            config->revolutions = parceDouble(currLine);
            continue;
        }else if(strstr(currLine,"iterationMode =") == currLine){
            config->itr_mode = (bool)parceInt(currLine);
            continue;
        }else if(strstr(currLine,"deltaPsiMode =") == currLine){
            config->deltaPsi_mode = (bool)parceInt(currLine);
            continue;
        }else if(strstr(currLine,"itrs =") == currLine){
            config->itrs = parceInt(currLine);
            continue;
        }else if(strstr(currLine,"Hbar =") == currLine){
            config->Hbar = parceDouble(currLine);
            continue;
        }else if(strstr(currLine,"charge =") == currLine){
            config->electron_charge = parceDouble(currLine);
            continue;
        }else if(strstr(currLine,"mass =") == currLine){
            config->electron_mass = parceDouble(currLine);
            continue;
        }else if(strstr(currLine,"t =") == currLine){
            config->time_intervolt = parceDouble(currLine);
            continue;
        }else if(strstr(currLine,"Type =") == currLine){
            config->type = parceInt(currLine);
            continue;
        }else if(strstr(currLine,"logPerod =") == currLine){
            config->log_p = parceInt(currLine);
            continue;
        }
    }
    
    config->filtterList = getFilterList(config->type);
    
    

    TIME_STAMP = createResultsPath(config->filtterList);

    int listSize = L_Size(FILTTER);

    LOG_FILES = newLinkedList();
    
    for(int i = 0 ; i < listSize ; i++){
        
        Orbit* orbit = (Orbit*)L_Pop(FILTTER);

        FILE* logfile = getOrbitFile(*orbit,TIME_STAMP);
        
        L_Append(LOG_FILES,logfile);

        L_Append(FILTTER,orbit);
    }

    fclose(config_f);

    config_f = fopen(CONFIG_PATH,"w");

    for(int i = 0 ; i <length ; i++){
        if(strstr(configLines[i],"TimeStamp =")!= NULL){
        fprintf(config_f,"TimeStamp =%s\n",TIME_STAMP);
        }else{
        fprintf(config_f,"%s\n",configLines[i]);
        }
        free(configLines[i]);
    }
    free(configLines);
    fclose(config_f);
    char metapath[100];
    sprintf(metapath,"%s/%s/meta.txt",RESULT_P,TIME_STAMP);

    if(saveMetaData(metapath)<0){
        printf("error saving meta data");
        return NULL;
    }
    

    return config;

}

