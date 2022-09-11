#ifndef SPHERICAL_H_
#define SPHERICAL_H_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include "../config/Config.h"
#include "calculations/SphericalCalc.h"
#include "calculations/RelSphericalCalc.h"
#include "../utility/macros.h"
#include "../utility/types.h"
#include "../utility/iterator.h"
#include "../Polar/calculations/Calc.h"
#include "../Polar/calculations/CalcRel.h"


/**
 * @brief runs the simualtion using the non-relativistic equations in SphericalCalc.h
 * 
 * @param result_files array of files to to store the results
 * @param config the settings of the simualtion
 */
void spherical_sim_ele(Config *config);
/**
 * @brief writes the current values from a given simItr to a given FILE*
 * 
 * @param result_f 
 * @param itr 
 */
void rel_spherical_sim_ele(Config *config);


#endif //SPHERICAL_H_