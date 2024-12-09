/**
 * @file NewtonMethod.h
 * @brief Defines the NewtonMethod class for solving nonlinear equations using Newton's method.
 */
#ifndef NEWTONMETHOD_H
#define NEWTONMETHOD_H

#pragma once

#include <Eigen/Dense>
#include "Function.h"

/**
 * @brief A class for solving nonlinear equations using Newton's method.
 * 
 * This class implements a Newton solver, particularly for use in implicit
 * ODE solvers.
 */
class NewtonMethod
{
public:
    /**
     * @brief Construct a new NewtonMethod object.
     */
    NewtonMethod();

    /**
     * @brief Destroy the NewtonMethod object.
     */
    ~NewtonMethod();

    /**
     * @brief Construct a NewtonMethod object with basic parameters.
     * 
     * @param function The function object representing the system.
     * @param y0 The initial guess for the solution.
     * @param t The current time value.
     */
    NewtonMethod(Function function, Eigen::VectorXd y0, double t);

    /**
     * @brief Construct a NewtonMethod object with beta and constant term.
     * 
     * @param function The function object representing the system.
     * @param y0 The initial guess for the solution.
     * @param t The current time value.
     * @param beta The coefficient for the system's right-hand side.
     * @param constant_term A constant vector added to the system's right-hand side.
     * @param step_size The time step size for the solver.
     */
    NewtonMethod(Function function, Eigen::VectorXd y0, double t, double beta, Eigen::VectorXd constant_term, double step_size);

    /**
     * @brief Construct a NewtonMethod object with alpha coefficient.
     * 
     * @param function The function object representing the system.
     * @param y0 The initial guess for the solution.
     * @param t The current time value.
     * @param alpha The coefficient for the solution term.
     * @param step_size The time step size for the solver.
     */
    NewtonMethod(Function function, Eigen::VectorXd y0, double t, double alpha, double step_size);

    /**
     * @brief Set the function object for the NewtonMethod.
     * 
     * @param function The function object representing the system.
     */
    void SetFunction(Function function);

    /**
     * @brief Set the initial guess for the NewtonMethod.
     * 
     * @param y0 The initial guess as a vector.
     */
    void SetInitialGuess(Eigen::VectorXd y0);

    /**
     * @brief Solve the nonlinear system using Newton's method.
     * 
     * @return Eigen::VectorXd The solution of the nonlinear system.
     */
    Eigen::VectorXd Solve();
private:
    Function function;  //< The function object representing the system.
    Eigen::VectorXd y0;  //< The initial guess for the solution.
    double tol = 1e-4;   //< The tolerance for the solver.
    double t;  //< The current time value.
    double h = 0.01;  //< The step size for numerical differentiation.
    double step_size;  //< The time step size for the solver.
    Eigen::VectorXd constant_term;  //< A constant vector added to the system's right-hand side.
    double beta = 1.0;  //< The coefficient for the system's right-hand side.
    double alpha = 1.0;  //< The coefficient for the solution term.

};

#endif