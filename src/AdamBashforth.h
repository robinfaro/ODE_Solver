/**
 * @file AdamBashforth.h
 * @brief Defines the AdamBashforth class for solving ordinary differential equations (ODEs) using the Adams-Bashforth method.
 */

#ifndef ADAMBASHFORTH_H
#define ADAMBASHFORTH_H

#pragma once
#include <Eigen/Dense>
#include "MultiStep.h"

/**
 * @brief A class for solving ordinary differential equations (ODEs) using the Adams-Bashforth method.
 * 
 * It extends the MultiStep class implementing an explicit multi-step method with fixed alpha vector. 
 * 
 *  
 * The general \f$ k \f$-step Adams-Bashforth method is given by:
 * 
 * \f[
 * y_{n+1} = \alpha_0 y_n + h \sum_{i=0}^{k-1} \beta_i f(t_{n-i}, y_{n-i}),
 * \f]
 * 
 * where \f$ \alpha_0 = 1 \f$ and the others \f$ \alpha_i = 0 \f$.
 */
class AdamBashforth : public MultiStep
{
public:
    /**
     * @brief Construct a new AdamBashforth object.
     */
    AdamBashforth();

    /**
     * @brief Destroy the AdamBashforth object.
     */
    ~AdamBashforth();

    /**
     * @brief Construct a new AdamBashforth object with full parameters.
     * 
     * @param step_size The step size for the solver.
     * @param initial_time The initial time of the problem.
     * @param final_time The final time of the problem.
     * @param initial_condition The initial condition of the problem.
     * @param function A Function object that includes the actual function of the problem.
     * @param beta The vector of coefficients for the Adam-Bashforth method.
     */
    AdamBashforth(double step_size, double initial_time, double final_time, Eigen::MatrixXd initial_condition, Function function, Eigen::VectorXd beta);

    /**
     * @brief Construct a new AdamBashforth object with no coefficients.
     * 
     * Initializes the AdamBashforth solver with default values, allowing coefficients to be set later.
     * 
     * @param step_size The step size for the solver.
     * @param initial_time The initial time of the problem.
     * @param final_time The final time of the problem.
     * @param initial_condition The initial condition of the problem.
     * @param function A Function object that includes the actual function of the problem.
     */
    AdamBashforth(double step_size, double initial_time, double final_time, Eigen::MatrixXd initial_condition, Function function);

    /**
     * @brief Solve the ODE using the Adam-Bashforth method.
     * @return An Eigen::MatrixXd containing the solution of the ODE at each time step.
     */
    Eigen::MatrixXd Solve() override;

private:
    /**
     * @brief Set the alpha coefficients for the Adam-Bashforth method.
     * 
     * This method sets the coefficients of the Adam-Bashforth method. It is not intended for external use as the
     * behavior is fixed for this solver.
     */
    void SetAlpha();
};

#endif