/**
 * @file BDF.h
 * @brief Defines the BDF class for solving ordinary differential equations (ODEs) using the Backward Differentiation Formula (BDF) method.
 */
#ifndef BDF_H
#define BDF_H

#pragma once

#include <Eigen/Dense>
#include "MultiStep.h"

/**
 * @brief A class for solving ordinary differential equations (ODEs) using the Backward Differentiation Formula method.
 * 
 * It extends the MultiStep class implementing an implict multi-step method with fixed beta vector.
* 
 * The \f[ k \f]-step BDF method is given by:
 * 
 * \f[
 * \sum_{i=0}^{k} \alpha_i y_{n-i} = h f(t_{n}, y_{n}),
 * \f]
 * 
 * where \f[ \beta_0 = 1 \f] and the others \f[ \beta_i = 0 \f].
 */

class BDF : public MultiStep
{
public:
    /**
     * @brief Construct a new BDF object.
     */
    BDF();

    /**
     * @brief Construct a new BDF object with full parameters.
     * 
     * @param step_size The step size for the solver.
     * @param initial_time The initial time of the problem.
     * @param final_time The final time of the problem.
     * @param initial_condition The initial condition of the problem.
     * @param function A Function object that includes the actual function of the problem and its Jacobian.
     * @param alpha The vector of coefficients for the BDF method.
     */
    BDF(double step_size, double initial_time, double final_time, Eigen::MatrixXd initial_condition, Function function, Eigen::VectorXd alpha);

    /**
     * @brief Destroy the BDF object.
     */
    ~BDF();

    /**
     * @brief Solve the ODE using the BDF method.
     * @return An Eigen::MatrixXd containing the solution of the ODE at each time step.
     */
    Eigen::MatrixXd Solve() override;
    
private:
    /**
     * @brief Set the beta coefficients for the BDF method.
     * This method sets the coefficients of the BDF method. It is not intended for external use as the behavior is fixed for this solver.
     */
    void SetBeta();

};

#endif