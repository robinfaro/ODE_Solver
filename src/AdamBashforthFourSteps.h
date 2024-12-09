/**
 * @file AdamBashforthFourSteps.h
 * @brief Defines the AdamBashforthFourStep class for solving ordinary differential equations (ODEs) using the Adams-Bashforth four-step method.
*/
#ifndef ADAMBASHFORTHFOURSTEPS_H
#define ADAMBASHFORTHFOURSTEPS_H

#pragma once

#include <Eigen/Dense>
#include "AdamBashforth.h"

/**
 * @brief A class for solving ordinary differential equations (ODEs) using the Adams-Bashforth four-step method.
 * 
 * The method is given by:
 * 
 * \f[
 * y_{n+1} = y_n + h \left( \frac{55}{24} f(t_n, y_n) - \frac{59}{24} f(t_{n-1}, y_{n-1}) 
 * + \frac{37}{24} f(t_{n-2}, y_{n-2}) - \frac{9}{24} f(t_{n-3}, y_{n-3}) \right),
 * \f]
 * 
 * where:
 * - \f$ \beta_0 = \frac{55}{24} \f$, \f$ \beta_1 = -\frac{59}{24} \f$, \f$ \beta_2 = \frac{37}{24} \f$, and \f$ \beta_3 = -\frac{9}{24} \f$ are the non-zero coefficients of the method.
 */
class AdamBashforthFourSteps : public AdamBashforth
{
public:
    /**
     * @brief Construct a new AdamBashforthFourSteps object.
     */
    AdamBashforthFourSteps();

    /**
     * @brief Destroy the AdamBashforthFourSteps object.
     */
    ~AdamBashforthFourSteps();

    /**
     * @brief Construct a new AdamBashforthFourSteps object with full parameters.
     * 
     * @param step_size The step size for the solver.
     * @param initial_time The initial time of the problem.
     * @param final_time The final time of the problem.
     * @param initial_condition The initial condition of the problem.
     * @param function A Function object that includes the actual function of the problem.
     */
    AdamBashforthFourSteps(double step_size, double initial_time, double final_time, Eigen::MatrixXd initial_condition, Function function);

private:
    /**
     * @brief Set the beta coefficients for the Adam-Bashforth four-step method. 
     * This method sets the coefficients of the Adam-Bashforth four-step method. It is not intended for external use as the behavior is fixed for this solver. 
     */
    void SetBeta();

};

#endif