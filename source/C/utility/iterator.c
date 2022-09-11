#include "../../../header/utility/iterator.h"
#include <time.h>

static long begin_time;
static long end_time;

void beginTime(){
    
    begin_time = clock();

}

void endTime(Orbit orbit){
    
    end_time = clock();
    printf("\n\nfinished calculation for orbit N = %hi , K = %hi , M = %hi time = %f s \n\n",orbit.n,orbit.k,orbit.m, (double)(end_time - begin_time) / CLOCKS_PER_SEC);

}

double calc_4_Runge_Kutta(double x , double dx){

    double k1 = x;
    double k2 = x+0.5*dx ;
    double k3 = x+0.5*dx ;
    double k4 = x+dx;    
    double res = x+((dx/6.0)*(k1+(2*k2)+(2*k3)+k4));
    // printf("k1 = %e , k2 = %e, k3 = %e, k4 = %e , res = %e\n",k1,k2,k3,k4,res);

    return res;
}

bool iterate(simItr* curr_itr , simItr* next_itr , Config* config){

    T(next_itr) += T_INTERVAL;

    R(next_itr) = R(curr_itr) + (R_DOT(curr_itr)*T_INTERVAL);

    R_DOT(next_itr) = R_DOT(curr_itr) + (R_DOT_DOT(curr_itr) * T_INTERVAL);
    
    PHI(next_itr) = PHI(curr_itr) + (PHI_DOT(curr_itr)* T_INTERVAL);
    
    if (PHI(next_itr) > _2_PI)
    {
        PHI(next_itr) = PHI(next_itr) - _2_PI;
    }
    if (TYPE == SPHERICAL || TYPE == REL_SPHERICAL || TYPE == SPIN)
    {
        THETA(next_itr) = THETA(curr_itr)+ (THETA_DOT(curr_itr)*T_INTERVAL);
        THETA_DOT(next_itr) = THETA_DOT(curr_itr)+(THETA_DOT_DOT(curr_itr)*T_INTERVAL);
        
    }
    if(R_DOT(next_itr) * R_DOT(curr_itr) < 0){
        return true;
    }
    
    return false;

}



void initItrations(simItr* itr , simType type){
    
    T(itr) = 0;
    R(itr) = 0;
    R_DOT(itr) = 0;
    R_DOT_DOT(itr) = 0;
    PHI(itr) = 0;
    PHI_DOT(itr) = 0;
    // REL
    GAMMA(itr) = -1.0;
    DELTAPHI(itr)= 0;
    // 3D
    THETA(itr) = -1.0;
    THETA_DOT(itr)=-1.0;
    THETA_DOT_DOT(itr)=-1.0;
    // spin
    EPSILON(itr) = -1.0;
    PHI_DOT_0(itr) = -1.0;

    
    if(type == REL_POLAR || type == REL_SPHERICAL || type == REL_SPIN){
    
        GAMMA(itr) = 0;

    }

    if(type == SPHERICAL || type == REL_SPHERICAL || type == SPIN){
    
        THETA(itr) = 0;
        THETA_DOT(itr) = 0;
        THETA_DOT_DOT(itr) = 0;
    
    }

    if(type == SPIN || type == REL_SPIN){

        EPSILON(itr) = 0;
        PHI_DOT_0(itr) = 0;

    }
    
}

void logItration(FILE *result_f ,simItr* itr){
    
    fprintf(result_f, "t= %E\t", T(itr) );

    fprintf(result_f, "r= %E\t", R(itr) );

    fprintf(result_f, "r'= %E\t", R_DOT(itr) );
    fprintf(result_f, "r''= %E\t", R_DOT_DOT(itr) );
    
    fprintf(result_f, "phi= %E\t", PHI(itr) );
    fprintf(result_f, "phi'= %E\t", PHI_DOT(itr));
    
    if(PHI_DOT_0(itr) != -1.0){ 
        fprintf(result_f, "phi'_0= %E\t", PHI_DOT_0(itr));
        
    }
    if(THETA(itr) != -1.0){
        fprintf(result_f,"theta= %E\t",THETA(itr));
    }
    if(THETA_DOT(itr) != -1.0){
        fprintf(result_f,"theta'= %E\t",THETA_DOT(itr));
    }
    if(THETA_DOT_DOT(itr) != -1.0){
        fprintf(result_f,"theta''= %E\t",THETA_DOT_DOT(itr));
    }
    if(GAMMA(itr) != -1.0){ 
        fprintf(result_f, "gamma= %E\t", GAMMA(itr));
    }
    if(DELTAPHI(itr) != -1.0){
        fprintf(result_f, "deltaPhi= %E\t", DELTAPHI(itr));
    }
    if(EPSILON(itr) != -1.0){
        fprintf(result_f, "epsilon= %E\t", EPSILON(itr));
    }

    fprintf(result_f, "\n");
    
}