/**
 * @file AdamMoulton.h
 * @brief Defines the AdamMoulton class for solving ordinary differential equations (ODEs) using the Adams-Moulton method.
 */


#ifndef ADAMMOULTON_H
#define ADAMMOULTON_H

#pragma once

#include <Eigen/Dense>
#include "MultiStep.h"

/**
 * @brief A class for solving ordinary differential equations (ODEs) using the Adams-Moulton method.
 * 
 * It extends the MultiStep class and implementing an implicit solver with fixed alpha.
 * 
 * The general \f[ k \f]-step Adams-Moulton method is given by:
 * 
 * \f[
 * y_{n+1} = \alpha_0 y_n + h \left( \beta_0 f(t_{n+1}, y_{n+1}) + \sum_{i=1}^{k} \beta_i f(t_{n+1-i}, y_{n+1-i}) \right),
 * \f]
 * 
 * where \f[ \alpha_0 = 1 \f] the others \f[ \alpha_i = 0 \f].
 */
class AdamMoulton : public MultiStep
{
public:
    /**
     * @brief Construct a new AdamMoulton object.
     */
    AdamMoulton();

    /**
     * @brief Destroy the AdamMoulton object.
     */
    ~AdamMoulton();

    /**
     * @brief Construct a new AdamMoulton object with full parameters.
     * 
     * @param step_size The step size for the solver.
     * @param initial_time The initial time of the problem.
     * @param final_time The final time of the problem.
     * @param initial_condition The initial condition of the problem.
     * @param function A Function object that includes the actual function of the problem and its Jacobian.
     * @param beta The vector of coefficients for the Adam-Moulton method.
     */
    AdamMoulton(double step_size, double initial_time, double final_time, Eigen::MatrixXd initial_condition, Function function, Eigen::VectorXd beta);

    /**
     * @brief Construct a new AdamMoulton object with no coefficients.
     * 
     *  Initializes the AdamMoulton solver with default values, allowing coefficients to be set later.
     * 
     * @param step_size The step size for the solver.
     * @param initial_time The initial time of the problem.
     * @param final_time The final time of the problem.
     * @param initial_condition The initial condition of the problem.
     * @param function A Function object that includes the actual function of the problem and its Jacobian.
     */
    AdamMoulton(double step_size, double initial_time, double final_time, Eigen::MatrixXd initial_condition, Function function);

    /**
     * @brief Solve the ODE using the Adam-Moulton method.
     * @return An Eigen::MatrixXd containing the solution of the ODE at each time step.
     */
    Eigen::MatrixXd Solve() override;

private:
    /**
     * @brief Set the alpha coefficients for the Adam-Moulton method.
     * 
     * This method sets the coefficients of the Adam-Moulton method. It is not intended for external use as the behavior is fixed for this solver.
     */
    void SetAlpha();

};

#endif