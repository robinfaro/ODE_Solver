/**
 * @file MultiStep.h
 * @brief Defines the MultiStep class for solving ordinary differential equations (ODEs) using multi-step methods.
 *
 */

#ifndef MULTISTEP_H
#define MULTISTEP_H

#pragma once
#include <Eigen/Dense>
#include "OdeSolver.h"

/**
 * @brief An enumeration for coefficient types used in the MultiStep method.
 */
enum CoeffType { ALPHA, BETA };

/**
 * @brief The MultiStep class for solving ordinary differential equations (ODEs) using multi-step methods.
 * 
 * Multi-step methods are solvers of ordinary differential equations (ODEs) which utilize
 * information from multiple previous steps to compute the next solution point. 
 * They are generally written in the form:
 * 
 * \f[
 * y_{n+1} = \sum_{i=0}^{k} \alpha_i y_{n-i} + h \sum_{i=0}^{k} \beta_i f(t_{n-i}, y_{n-i}),
 * \f]
 * 
 * where:
 * - \( y_{n+1} \): the solution at the next time step.
 * - \( y_{n-i} \): the solutions at previous time steps.
 * - \( f(t, y) \): the derivative of the function \( \frac{dy}{dt} \).
 * - \( \alpha_i, \beta_i \): coefficients that change according to the multi-step method employed.
 * - \( h \): the time step size.
 * - \( k \): the number of previous steps used in the method.
 * 
 */
class MultiStep : public OdeSolver
{
public:
    /**
     * @brief Construct a new MultiStep object.
     */
    MultiStep();
    /**
     * @brief Construct a new MultiStep object with full parameters.
     * 
     * @param step_size The step size for the solver.
     * @param initial_time The initial time of the problem.
     * @param final_time The final time of the problem.
     * @param initial_condition The initial condition of the problem.
     * @param function A Function object that includes the actual function of the problem.
     * @param alpha The vector of coefficients for the MultiStep method (used for previous solution terms).
     * @param beta The vector of coefficients for the MultiStep method (used for function terms).
     */
    MultiStep(double step_size, double initial_time, double final_time, Eigen::MatrixXd initial_condition, Function function, Eigen::VectorXd alpha, Eigen::VectorXd beta);

    /**
     * @brief Construct a new MultiStep object with a single coefficient type.
     * 
     * @param step_size The step size for the solver.
     * @param initial_time The initial time of the problem.
     * @param final_time The final time of the problem.
     * @param initial_condition The initial condition of the problem.
     * @param function A Function object that includes the actual function of the problem.
     * @param coefficient The vector of coefficients for the MultiStep method (either alpha or beta).
     * @param coeff_type Specifies whether the coefficient is ALPHA or BETA.
     */
    MultiStep(double step_size, double initial_time, double final_time, Eigen::MatrixXd initial_condition, Function function, Eigen::VectorXd coefficent, CoeffType coeff_type);

    /**
     * @brief Construct a new MultiStep object with no coefficients.
     * 
     * Initializes the MultiStep solver with default values, allowing coefficients to be set later.
     * 
     * @param step_size The step size for the solver.
     * @param initial_time The initial time of the problem.
     * @param final_time The final time of the problem.
     * @param initial_condition The initial condition of the problem.
     * @param function A Function object that includes the actual function of the problem.
     */
    MultiStep(double step_size, double initial_time, double final_time, Eigen::MatrixXd initial_condition, Function function);

    /**
     * @brief Destroy the MultiStep object.
     */
    ~MultiStep();

     /**
     * @brief Set the alpha coefficients for the MultiStep method.
     * 
     * The alpha coefficients are used for terms involving previous solutions.
     * 
     * @param alpha A vector containing the alpha coefficients.
     */
    void SetAlpha(Eigen::VectorXd alpha);

    /**
     * @brief Set the beta coefficients for the MultiStep method.
     * 
     * The beta coefficients are used for terms involving the function.
     * 
     * @param beta A vector containing the beta coefficients.
     */
    void SetBeta(Eigen::VectorXd beta);

protected:
    /**
     * @brief The alpha coefficients for the MultiStep method.
     * 
     * The alpha coefficients are used for terms involving previous solutions.
     * 
     */
    Eigen::VectorXd alpha;
    /**
     * @brief The beta coefficients for the MultiStep method.
     * 
     * The beta coefficients are used for terms involving the function.
     * 
     */
    Eigen::VectorXd beta;
};

#endif