#ifndef CONFIG_H_
#define CONFIG_H_

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <stdbool.h>
#include "../utility/linkedList.h"
#include "../utility/Reads.h"
#include "../utility/strParce.h"
#include "../utility/types.h"
#include "../utility/macros.h"
#include "filter.h"
#define CONFIG_PATH "config.ini" // url of where the values are saved


/**
 * @brief Reads the inital configration values from the config.ini file and stores them in Config var
 * 
 * @return Config* with the config values
 */
Config* getInitVals();

#endif // CONFIG_H_