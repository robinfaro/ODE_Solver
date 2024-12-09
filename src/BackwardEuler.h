/**
 * @file BackwardEuler.h
 * @brief Defines the BackwardEuler class for solving ordinary differential equations (ODEs) using the Backward Euler method.
 */

#ifndef BACKWARDEULER_H
#define BACKWARDEULER_H

#pragma once

#include <Eigen/Dense>
#include "AdamMoulton.h"

/**
 * @brief The BackwardEuler class for solving ordinary differential equations (ODEs) using the Backward Euler method.
 * 
 * The Backward Euler method is a first-order implicit method and can be considered the simplest form of the Adams-Moulton family. 
 * It uses the derivative information at the next time step to compute the solution, requiring the solution of an implicit equation at each step.
 * 
 * The method is given by:
 * 
 * \f[
 * y_{n+1} = y_n + h f(t_{n+1}, y_{n+1}),
 * \f]
 * 
 * where \( \beta_0 = 1 \) is the single non-zero coefficient of this method.
 * 
 */
class BackwardEuler : public AdamMoulton
{
public:
    /**
     * @brief Construct a new BackwardEuler object.
     */
    BackwardEuler();

    /**
     * @brief Construct a new BackwardEuler object with full parameters.
     * @param step_size The step size for the solver.
     * @param initial_time The initial time of the problem.
     * @param final_time The final time of the problem.
     * @param initial_condition The initial condition of the problem.
     * @param function A Function object that includes the actual function of the problem and its Jacobian.
     */
    BackwardEuler(double step_size, double initial_time, double final_time, Eigen::MatrixXd initial_condition, Function function);

    /**
     * @brief Destroy the BackwardEuler object.
     */ 
    ~BackwardEuler();

private:
    /**
     * @brief Set the beta coefficients for the Backward Euler method.
     * This method sets the coefficients of the Backward Euler method. It is not intended for external use as the behavior is fixed for this solver.
     */
    void SetBeta();
};

#endif