#include "../../../../header/Spin/calculations/SpinCalc.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


double spin_calc_r_dot_dot(double r , double theta , double theta_dot , double Phi_dot_0 , double epsilon , double mass , double charge){
    
    double arg1 = theta_dot*theta_dot;

    double arg2 = sin(theta)*Phi_dot_0;
    arg2*= arg2;

    double arg3 = (1 - (3*epsilon) + (2*epsilon*epsilon) );

    arg2*= arg3;

    arg1+= arg2;
    arg1*= r;

    arg2 = mass*r*r;
    arg2 = (charge* charge)/ arg2;

    return(arg1 - arg2);  
}   

double spin_calc_theta_dot_dot(double r ,double r_dot , double theta , double theta_dot , double phi_dot_0 , double epsilon){

    double arg1 = sin(theta)*cos(theta);
    arg1*= (phi_dot_0*phi_dot_0) ;
    arg1*= (1 - (epsilon*epsilon));

    double arg2 = 2*r_dot*theta_dot;
    arg2/= r;

    return (arg1 - arg2);
}

double spin_calc_phi_dot(double phi_dot_0 , double epsilon){
    
    double arg1 = (1 - epsilon);

    return(arg1 * phi_dot_0);
}

double spin_calc_phi_dot_0(double r , double mass ,double nphi , double hbar , double theta){
    
    double arg1 = nphi*hbar;
    
    double arg2 = sin(theta);
    arg2*= arg2;
    arg2*= (mass*r*r);
    
    return (arg1 / arg2);
}

double spin_calc_epsilon(double r , double mass , double charge , double theta ,double nphi){

    double arg1 = sin(theta);
    arg1*= arg1;
    arg1*= (charge*charge);

    double arg2 = 2*nphi*mass*C*C*r;

    return (arg1 / arg2);

}
