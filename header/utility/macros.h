#ifndef MACROS_H_
#define MACROS_H_
// -------------MACROS--------------------
    //--------simitrs macros--------
    #define T(itr)              (itr->t)
    #define R(itr)              (itr->r)
    #define R_DOT(itr)          (itr->r_dot)
    #define R_DOT_DOT(itr)      (itr->r_dot_dot)
    #define PHI(itr)            (itr->phi)
    #define PHI_DOT(itr)        (itr->phi_dot)
    #define PHI_DOT_0(itr)      (itr->phi_dot_0)
    #define DELTAPHI(itr)       (itr->delataphi)
    #define THETA(itr)          (itr->theta)
    #define THETA_DOT(itr)      (itr->theta_dot)
    #define THETA_DOT_DOT(itr)  (itr->theta_dot_dot)
    #define GAMMA(itr)          (itr->gamma)
    #define EPSILON(itr)        (itr->epsilon)
    //--------config macros--------
    #define MASS                (config->electron_mass) 
    #define CHARGE              (config->electron_charge)
    #define T_INTERVAL          (config->time_intervolt)
    #define HBAR                (config->Hbar)
    #define RES_PATH            (config->results_path)
    #define LOG_P               (config->log_p)
    #define TYPE                (config->type)
    #define FILTTER             (config->filtterList)
    #define LOG_FILES           (config->logFiles)
    #define TIME_STAMP          (config->timeStamp)
    #define REVOLUTIONS         (config->revolutions)
    //---------Result macros-------
    #define R_MIN               (rMinMax[0])
    #define R_MAX               (rMinMax[1])
    //------LinkedList macros------
    #define L_Size(list)        (LinkedList_getSize(list))
    #define L_Append(list,data) (LinkedList_append(list,data))
    #define L_Prepend(list,data)(LinkedList_prepend(list,data))
    #define L_Pop(list)         (LinkedList_pop(list))
    //-----calculations macros-----
    #define PI                  (3.14159265358979323846)
    #define _2_PI               (2 * PI)
    #define BOHR_R              (0.0000000052977210903)     //5.29*10^-9 = a_0 bohr radios 0.0000000052977210903
    #define C                   (double)(29979245800)
    #define RESULT_P            ("results")
//----------------------------------------
#endif//MACROS_H_