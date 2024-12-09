/**
 * @file OdeSolver.h
 * @brief Defines the OdeSolver class for solving ordinary differential equations (ODEs).
 * 
 * An ordinary differential equation (ODE) is generally written in the form:
 * 
 * \f[
 * \frac{dy}{dt} = f(t, y),
 * \f]
 * 
 * To solve such equation numerically, the following inputs are required:
 * - **Initial time** (\f[ t_0 \f]): the starting time for the solution.
 * - **Final time** (\f[ t_f \f]): the final time to which the solution is computed.
 * - **Initial condition** (\f[ y_0 \f]): the value of \f[ y \f] at \f[ t = t_0 \f].
 * - **Time step** (\f[ h \f]): the increment of time between successive solution points.
 * 
 */


#ifndef ODESOLVER_H
#define ODESOLVER_H

#pragma once
#include <Eigen/Dense>
#include <iostream>
#include <fstream>
#include "Function.h"

/**
 * @brief A class for solving ordinary differential equations (ODEs).
 */
class OdeSolver
{
protected:
    double step_size;  ///< The step size for the solver.
    double initial_time;  ///< The initial time of the problem.
    double final_time;   ///< The final time of the problem.
    Eigen::MatrixXd initial_condition;  ///< The initial condition of the problem.
    Function function;   ///< A Function object that includes the actual function of the problem and optionally its derivative (needed if the method is implicit).
public:

    /**
     * @brief Construct a new OdeSolver object.
     */
    OdeSolver();

    /**
     * @brief Construct a new OdeSolver object.
     * @param step_size The step size for the solver.
     * @param initial_time The initial time of the problem.
     * @param final_time The final time of the problem.
     * @param initial_condition The initial condition of the problem.
     * @param function A Function object that includes the actual function of the problem and optionally its derivative (needed if the method is implicit).
     */
    OdeSolver(double step_size, double initial_time, double final_time, Eigen::MatrixXd initial_condition, Function function);
    
    /**
     * @brief Destroy the OdeSolver object.
     */
    ~OdeSolver();

    /**
     * @brief Set the step size for the solver.
     * @param step_size The step size for the solver.
     */
    void SetStepSize(double step_size);

    /**
     * @brief Set the time interval of the problem.
     * @param initial_time The initial time of the problem.
     * @param final_time The final time of the problem.
     */
    void SetTimeInterval(double initial_time, double final_time);

    /**
     * @brief Set the initial condition of the problem.
     * @param initial_condition The initial condition of the problem.
     */
    void SetInitialCondition(Eigen::MatrixXd initial_condition);

    /**
     * @brief Set the Function object of the problem.
     * @param function A Function object that includes the actual function of the problem and optionally its derivative (needed if the method is implicit).
     */
    void SetFunction(Function function);
    
    /**
     * @brief Solve the ODE problem.
     * 
     * This is a pure virtual function that must be implemented by derived classes.
     * It solves the ordinary differential equation over the specified time interval
     * with the given initial conditions and step size.
     * 
     * @return Eigen::MatrixXd A matrix containing the solution of the ODE at each time step.
     */
    virtual Eigen::MatrixXd Solve() = 0;
};

#endif //ODESOLVER_H