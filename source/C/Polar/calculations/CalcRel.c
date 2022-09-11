#include "../../../../header/Polar/calculations/CalcRel.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

// Valid
double calc_rel_phi_dot(double l , double gamma , double r , double m){
    
    r*=r;
    
    double arg1 = gamma * m;
    arg1 *= r;
    return(l/arg1);

}
// Valid
double calc_rel_gamma(double l , double m , double r, double r_dot){
   
    double arg1 = C;
    arg1 *= m*r;
    arg1 = l/arg1; 
    arg1*=arg1;
    arg1++;

    double arg2 = C;
    arg2 = r_dot/arg2;
    arg2*= arg2;
    arg2 = 1-arg2;

    arg1 = sqrt(arg1/arg2);

    return arg1;
}
// Valid
double calc_rel_r_dot_dot(double l_sqr , double m , double gamma , double r , double e , double r_dot){
    
    double arg1,arg2,arg3;
    
    double r_sq = r*r; 
    
    arg1 = l_sqr;
    arg1/= gamma*m*r_sq*r;
    
    arg2 = e*e;
    arg2/= r_sq;
    
    arg3 = r_dot/C;
    arg3*= arg3;
    arg3 = 1-arg3;

    arg2 *= arg3;

    arg1 = arg1-arg2;

    arg1/= gamma*m;

    return arg1;
}
// Valid
long double calc_rel_rmin(long double a ,long double b , long double c){

    
    long double arg1 = b*b;
    
    arg1-=(a*c);
    if(arg1 < 0){
        printf("WARNING negative under sqrt with value = %LE\n\n",arg1);
        arg1 = 0;   
    }
    arg1 = sqrtl(arg1);

    long double arg2 = -1*b;

    arg2+=arg1;

    return(arg2/a);

}
// Valid
long double calc_rel_A(long double m ,long  double w){


    long double arg1 = w*w;
    arg1 /= (C*C);

    long double arg2 = 2*m*w;

    return(arg1 + arg2);
}
// Valid
long double calc_rel_B(long double m , long double e , long double w){

    long double e_sqr = e*e;
    long double arg1 = e_sqr*w;
    arg1 /= (C*C);

    long double arg2 = m*e_sqr;

    return(arg1 +arg2);

}
// Valid
long double calc_rel_C(long double l_sqr , long double e){
    
    long double arg1 = powl(e,4);
    arg1/= (C*C);


    return(arg1 - l_sqr);

}

long double calc_rel_w(long double energy_level ,long double h_mult ,long double m ,long double alpha ){


    long double alpha_sqr = (alpha*alpha);
    
    long double h_mult_sqr = h_mult * h_mult;

    long double arg1 = (h_mult_sqr - alpha_sqr);

    arg1 = sqrtl(arg1);

    arg1 += (energy_level-h_mult);
    arg1 *=arg1;

    arg1 = alpha_sqr/arg1;
    arg1++;

    arg1 = sqrtl(arg1);
    arg1 = 1/arg1;

    arg1--;

    long double arg2 = m*C*C;
    return(arg1*arg2);
}

double calc_rel_chi(double h_bar ,double e,double energy_level)
{
    

    double arg1 = h_bar*C*energy_level;
    arg1 = (e*e)/arg1;
    arg1*=arg1;
    arg1 = 1-arg1;

    return(sqrt(arg1));


}

long double calc_alpha(long double charge ,long double hbar ){
    long double e_sqr = charge*charge;
    long double arg1 = hbar*C;
    return(e_sqr/arg1); 
}