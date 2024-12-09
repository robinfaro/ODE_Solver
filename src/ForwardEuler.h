/**
 * @file ForwardEuler.h
 * @brief Defines the ForwardEuler class for solving ordinary differential equations (ODEs) using the Forward Euler method.
 */
#ifndef FORWARDEULER_H
#define FORWARDEULER_H

#pragma once
#include <Eigen/Dense>
#include "OdeSolver.h"
#include "RungeKutta.h"

/**
 * @brief A class for solving ordinary differential equations (ODEs) using the Forward Euler method.
 * 
 * The Forward Euler method is a first-order explicit method for solving ordinary differential equations (ODEs). 
 * 
 * The generic formulation of the Forward Euler method is given by:
 * 
 * \f[
 * y_{n+1} = y_n + h f\left(t_n , y_n \right)
 * \f]
 * 
 * In this setting, the coefficients \f[ a_{ij} \f], \f[ b_i \f], and \f[ c_i \f]  are:
 * 
 * \f[
 * \begin{array}{c|c}
 * 0 & 0 \\
 * \hline
 *      & 1
 * \end{array}
 * \f]
 */
class ForwardEuler : public RungeKutta
{
public:
    /**
     * @brief Construct a new ForwardEuler object.
     */
    ForwardEuler();
    /**
     * @brief Construct a new ForwardEuler object.
     * @param step_size The step size for the solver.
     * @param initial_time The initial time of the problem.
     * @param final_time The final time of the problem.
     * @param initial_condition The initial condition of the problem.
     * @param function A Function object that includes the actual function of the problem
     */
    ForwardEuler(double step_size, double initial_time, double final_time, Eigen::MatrixXd initial_condition, Function function);
    /**
     * @brief Destroy the ForwardEuler object.
     */
    ~ForwardEuler();

private:
    /**
     * @brief Set the A matrix for the Runge-Kutta method.
     * 
     * This method sets the coefficients of the Butcher tableau's A matrix for
     * the Forward Euler method. It is not intended for external use as the
     * behavior is fixed for this solver.
     */
    void SetA();
    /**
     * @brief Set the B vector for the Runge-Kutta method.
     * 
     * This method sets the coefficients of the Butcher tableau's B vector for
     * the Forward Euler method. It is not intended for external use as the
     * behavior is fixed for this solver.
     */
    void SetB();
    /**
     * @brief Set the C vector for the Runge-Kutta method.
     * 
     * This method sets the coefficients of the Butcher tableau's C vector for
     * the Forward Euler method. It is not intended for external use as the
     * behavior is fixed for this solver.
     */
    void SetC();
};

#endif