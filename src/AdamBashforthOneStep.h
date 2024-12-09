/**
 * @file AdamBashforthOneStep.h
 * @brief Defines the AdamBashforthOneStep class for solving ordinary differential equations (ODEs) using the Adams-Bashforth one-step method.
 * 
 */

#ifndef ADAMBASHFORTHONESTEP_H
#define ADAMBASHFORTHONESTEP_H

#pragma once

#include <Eigen/Dense>
#include "AdamBashforth.h"

/**
 * @brief A class for solving ordinary differential equations (ODEs) using the Adams-Bashforth one-step method. 
 * 
 * The method is given by:
 * 
 * \f[
 * y_{n+1} = y_n + h f(t_n, y_n),
 * \f]
 * 
 * where \f$ \beta_0 = 1 \f$ is the only non-zero coefficient in this one-step method.
 */
class AdamBashforthOneStep : public AdamBashforth
{
public:
    /**
     * @brief Construct a new AdamBashforthOneStep object.
     */
    
    AdamBashforthOneStep();
    /**
     * @brief Destroy the AdamBashforthOneStep object.
     */
    ~AdamBashforthOneStep();

    /**
     * @brief Construct a new AdamBashforthOneStep object with full parameters.
     * 
     * @param step_size The step size for the solver.
     * @param initial_time The initial time of the problem.
     * @param final_time The final time of the problem.
     * @param initial_condition The initial condition of the problem.
     * @param function A Function object that includes the actual function of the problem.
     */
    AdamBashforthOneStep(double step_size, double initial_time, double final_time, Eigen::MatrixXd initial_condition, Function function);

private:
    /**
     * @brief Set the beta coefficients for the Adam-Bashforth one-step method.
     * This method sets the coefficients of the Adam-Bashforth one-step method. It is not intended for external use as the behavior is fixed for this solver.
     * 
     */
    void SetBeta();
};

#endif