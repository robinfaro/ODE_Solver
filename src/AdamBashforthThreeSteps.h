/**
 * @file AdamBashforthThreeStep.h
 * @brief Defines the AdamBashforthThreeStep class for solving ordinary differential equations (ODEs) using the Adams-Bashforth three-step method.
 */

#ifndef ADAMBASHFORTHTHREESTEPS_H
#define ADAMBASHFORTHTHREESTEPS_H

#pragma once

#include <Eigen/Dense>
#include "AdamBashforth.h"

/**
 * @brief A class for solving ordinary differential equations (ODEs) using the Adams-Bashforth three-step method.
 * 
 * The Adams-Bashforth three-step method is a third-order explicit method for solving ordinary differential equations (ODEs).
 * 
 * The method is given by:
 * 
 * \f[
 * y_{n+1} = y_n + h \left( \frac{23}{12} f(t_n, y_n) - \frac{16}{12} f(t_{n-1}, y_{n-1}) + \frac{5}{12} f(t_{n-2}, y_{n-2}) \right),
 * \f]
 * 
 * where \( \beta_0 = \frac{23}{12} \), \( \beta_1 = -\frac{16}{12} \), and \( \beta_2 = \frac{5}{12} \) are the non-zero coefficients of the method.
 * 
 */
class AdamBashforthThreeSteps : public AdamBashforth
{
public:
    /**
     * @brief Construct a new AdamBashforthThreeSteps object.
     */
    AdamBashforthThreeSteps();

    /**
     * @brief Destroy the AdamBashforthThreeSteps object.
     */
    ~AdamBashforthThreeSteps();

    /**
     * @brief Construct a new AdamBashforthThreeSteps object with full parameters.
     * 
     * @param step_size The step size for the solver.
     * @param initial_time The initial time of the problem.
     * @param final_time The final time of the problem.
     * @param initial_condition The initial condition of the problem.
     * @param function A Function object that includes the actual function of the problem.
     */
    AdamBashforthThreeSteps(double step_size, double initial_time, double final_time, Eigen::MatrixXd initial_condition, Function function);

private:
    /**
     * @brief Set the beta coefficients for the Adam-Bashforth three-step method.
     * This method sets the coefficients of the Adam-Bashforth three-step method. It is not intended for external use as the behavior is fixed for this solver.
     * 
     */
    void SetBeta();

};

#endif