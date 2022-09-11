#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "../../header/Polar/polar.h"
#include "../../header/Spherical/Spherical.h"
#include "../../header/Spin/Spin.h"

int main()
{
    
    Config *config = getInitVals();
    
    
    // start timer
    
    long begin_time = clock();

    switch (TYPE)
    {
        case POLAR:

            polar_sim_ele(config);

        break;
        case REL_POLAR:

            polar_sim_rel_ele( config);  

        break;
        case SPHERICAL:

            spherical_sim_ele(config);
        
        break;
        case REL_SPHERICAL:
        
            rel_spherical_sim_ele(config);
        
        break;
        case SPIN:
        
            spin_sim_ele(config);
        
        break;
    }
        // stop timer
    
        long end_time = clock();
    
        //-----------------------------------------

        // close results.txt file

    free(FILTTER);
    free(LOG_FILES);
    free(TIME_STAMP);
    free(config);

    return 0;
}
