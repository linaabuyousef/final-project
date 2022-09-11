#include "../../../header/Spin/Spin.h"
#include <stdio.h>
#include <float.h>

void spin_sim_ele(Config *config){

    simItr *curr_itr , *next_itr;

    curr_itr = (simItr*)malloc(sizeof(simItr));
    next_itr = (simItr*)malloc(sizeof(simItr));

    long double Hbar_sqr = HBAR*HBAR;
    
    int listSize = L_Size(FILTTER);
    bool at_intrest = false; 

    for (int i = 0 ; i < listSize ; i++){
        beginTime();
        Orbit* currOrbit = L_Pop(FILTTER);

        double N = currOrbit->n;
        double K = currOrbit->k;
        double m = currOrbit->m;
        
        double curr_l = HBAR*K;
        double K_sqr = K*K;

        double* rMinMax = calc_rmin_rmax(N,K);

        
        double Nphi = K-m;

        double thetamin= sphere_calc_theta_min(Nphi,K);
        
        FILE* res_f = (FILE*)L_Pop(LOG_FILES);
        
        initItrations(curr_itr,TYPE);
        initItrations(next_itr,TYPE);



        R(curr_itr) = R_MIN;
        THETA(curr_itr) = thetamin;
        
        PHI_DOT_0(curr_itr) = spin_calc_phi_dot_0(R(curr_itr),MASS,Nphi,HBAR,THETA(curr_itr));
        EPSILON(curr_itr) = spin_calc_epsilon(R(curr_itr),MASS,CHARGE,THETA(curr_itr),Nphi);

        PHI_DOT(curr_itr) = spin_calc_phi_dot(PHI_DOT_0(curr_itr),EPSILON(curr_itr));
        THETA_DOT_DOT(curr_itr) = spin_calc_theta_dot_dot(R(curr_itr),R_DOT(curr_itr),THETA(curr_itr),THETA(curr_itr),PHI_DOT_0(curr_itr),EPSILON(curr_itr));
        R_DOT_DOT(curr_itr) = spin_calc_r_dot_dot(R(curr_itr),THETA(curr_itr),THETA_DOT(curr_itr),PHI_DOT_0(curr_itr),EPSILON(curr_itr),MASS,CHARGE);
        
        logItration(res_f,curr_itr);

        double revolutions = REVOLUTIONS;

        unsigned long j = 1;
        for (unsigned long it = 1; j < config->itrs;it++){
        
                
            at_intrest = iterate(curr_itr,next_itr,config);
            
            PHI_DOT_0(next_itr) = spin_calc_phi_dot_0(R(curr_itr),MASS,Nphi,HBAR,THETA(curr_itr));
            EPSILON(next_itr) = spin_calc_epsilon(R(curr_itr),MASS,CHARGE,THETA(curr_itr),Nphi);

            PHI_DOT(next_itr) = spin_calc_phi_dot(PHI_DOT_0(curr_itr),EPSILON(curr_itr));
            THETA_DOT_DOT(next_itr) = spin_calc_theta_dot_dot(R(curr_itr),R_DOT(curr_itr),THETA(curr_itr),THETA(curr_itr),PHI_DOT_0(curr_itr),EPSILON(curr_itr));
            R_DOT_DOT(next_itr) = spin_calc_r_dot_dot(R(curr_itr),THETA(curr_itr),THETA_DOT(curr_itr),PHI_DOT_0(curr_itr),EPSILON(curr_itr),MASS,CHARGE);
        
            if(it % LOG_P == 0){
                logItration(res_f,curr_itr);
            }
            if(config->itr_mode){
                j++;
            }else if(at_intrest){
                revolutions -= 0.5;
                if(revolutions < 0){
                    break;
                }
            }
            simItr* temp = curr_itr;
            curr_itr = next_itr;
            next_itr = temp;
        }

        endTime(*currOrbit);
        logItration(res_f,curr_itr);

        free(rMinMax);
        fclose(res_f);
        
        free(currOrbit);


    }
    
    free(curr_itr);
    free(next_itr);
            printf("here\n");

}

//---------------------------------------------
