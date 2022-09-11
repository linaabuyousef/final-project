#ifndef CALC_H_
#define CALC_H_

#include "../../utility/macros.h"


/*
*************************************************************************************************************
*** All calculations are done acording to Atomic Structure And Spectral Lines Vol. I by Arnold Sommerfeld ***
*************************************************************************************************************
*/

/**
    Calculates R_dot_dot "acceleration" of and electron
    where   

        m*r_dot_dot = (l^2)/(m*(r^3)) - (e^2)/(r^2)

    @param double m = 9.109383e-28 double e = 4.803 e-10 l_sqr = Calc_l_sqr r = r of the currnt itration
    @return double r_dot_dot 

*/
double calc_R_dot_dot(double m , double r , double e , double k_sqr, double Hbar_sqr );


/**

    Calculates the angel change rate of the electron movment
    where   

        phi_dot = L / m*(r^2)

    @param double m = 9.109383e-28 double e = 4.803 e-10  r = r of the currnt itration
    @return double phi_dot 


*/
double calc_phi_dot(double l,double m,double r);



/**
    Calculates the R_max and the R_min for a given electron orbit
    where   

        (1) r_min + r_max = 2*a
        (2) r_min*max = b^2

        where a = n^2 * BOHR_R 
        and   b = k/n * a

    @param double n double k
    @return double result[2] containing the r_min at index 0 and r_max at index 1

*/  
double* calc_rmin_rmax(double n , double k );




#endif // CALC_H_
