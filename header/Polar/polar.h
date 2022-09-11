#ifndef POLAR_H_
#define POLAR_H_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include "../config/Config.h"
#include "calculations/Calc.h"
#include "calculations/CalcRel.h"
#include "../utility/macros.h"
#include "../utility/types.h"
#include "../utility/iterator.h"





/**
 * @brief runs the simualtion using the non-relativistic equations in Calc.h
 * 
 * @param result_files array of files to to store the results
 * @param config the settings of the simualtion
 */
void polar_sim_ele(Config *config);
/**
 * @brief runs the simualtion using the relativistic equations in CalcRel.h
 * 
 * @param result_files array of files to to store the results
 * @param config the settings of the simualtion
 */
void polar_sim_rel_ele(Config *config);

#endif //POLAR_H_