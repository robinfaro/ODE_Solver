/**
 * @file AdamBashforthTwoSteps.h
 * @brief Defines the AdamBashforthTwoStep class for solving ordinary differential equations (ODEs) using the Adams-Bashforth two-step method.
*/

#ifndef ADAMBASHFORTHTWOSTEPS_H
#define ADAMBASHFORTHTWOSTEPS_H

#pragma once

#include <Eigen/Dense>
#include "AdamBashforth.h"

/**
 * @brief A class for solving ordinary differential equations (ODEs) using the Adams-Bashforth two-step method.
 * 
 * The method is given by:
 * 
 * \f[
 * y_{n+1} = y_n + h \left( \frac{3}{2} f(t_n, y_n) - \frac{1}{2} f(t_{n-1}, y_{n-1}) \right),
 * \f]
 * 
 * where \f$ \beta_0 = \frac{3}{2} \f$ and \f$ \beta_1 = -\frac{1}{2} \f$ are the non-zero coefficients of the method.
 */
class AdamBashforthTwoSteps : public AdamBashforth
{
public:
    /**
     * @brief Construct a new AdamBashforthTwoSteps object.
     */
    AdamBashforthTwoSteps();
    
    /**
     * @brief Destroy the AdamBashforthTwoSteps object.
     */
    ~AdamBashforthTwoSteps();

    /**
     * @brief Construct a new AdamBashforthTwoSteps object with full parameters.
     * 
     * @param step_size The step size for the solver.
     * @param initial_time The initial time of the problem.
     * @param final_time The final time of the problem.
     * @param initial_condition The initial condition of the problem.
     * @param function A Function object that includes the actual function of the problem.
     */
    AdamBashforthTwoSteps(double step_size, double initial_time, double final_time, Eigen::MatrixXd initial_condition, Function function);

private:
    /**
     * @brief Set the beta coefficients for the Adam-Bashforth two-step method.
     * This method sets the coefficients of the Adam-Bashforth two-step method. It is not intended for external use as the behavior is fixed for this solver.
     * 
     */
    void SetBeta();
};



#endif