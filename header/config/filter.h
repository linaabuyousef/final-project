#ifndef FILTER_H_
#define FILTER_H_

#include <stdio.h>
#include <stdlib.h>
#include "../utility/linkedList.h"
#include "../utility/types.h"

#define FILTER_PATH "filter.ini"
/**
 * @brief Creates a LinkedList of the orbits specfied in filter,ini
 * 
 * @param type ENUM simulation type 
 * @return LinkedList* LinkedList of Struct Orbit 
 */
LinkedList* getFilterList(simType type);

#endif//FILTER_H_