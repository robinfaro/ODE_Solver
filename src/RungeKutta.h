/** 
 * @file RungeKutta.h
 * @brief Defines the RungeKutta class for solving ordinary differential equations (ODEs) using the Runge-Kutta method.
 */
#ifndef RUNGEKUTTA_H
#define RUNGEKUTTA_H

#pragma once
#include <Eigen/Dense>
#include "OdeSolver.h"

/**
 * @brief A class for solving ordinary differential equations (ODEs) using the Runge-Kutta method.
 * 
 * The Runge-Kutta methods are numerical solver of ordinary 
 * differential equations (ODEs). The generic formulation of an explicit 
 * Runge-Kutta method of order \( s \) is given by:
 * 
 * \f[
 * y_{n+1} = y_n + h \sum_{i=1}^{s} b_i k_i
 * \f]
 * 
 * where the stages \( k_i \) are defined as:
 * 
 * \f[
 * k_i = f\left(t_n + c_i h, y_n + h \sum_{j=1}^{i-1} a_{ij} k_j\right), \quad i = 1, \dots, s
 * \f]
 * 
 * The coefficients \( a_{ij} \), \( b_i \), and \( c_i \) are represented by:
 * 
 * \f[
 * \begin{array}{c|cccc}
 * c_1 & 0      & 0      & 0      & \cdots \\
 * c_2 & a_{21} & 0      & 0      & \cdots \\
 * c_3 & a_{31} & a_{32} & 0      & \cdots \\
 * \vdots & \vdots & \vdots & \vdots & \ddots \\
 * c_s & a_{s1} & a_{s2} & a_{s3} & \cdots \\
 * \hline
 *      & b_1    & b_2    & b_3    & \cdots & b_s
 * \end{array}
 * \f]
 * 
 */
class RungeKutta: public OdeSolver
{
public:
    /**
     * @brief Construct a new RungeKutta object.
     */
    RungeKutta();
    /**
     * @brief Construct a new RungeKutta object.
     * @param step_size The step size for the solver.
     * @param initial_time The initial time of the problem.
     * @param final_time The final time of the problem.
     * @param initial_condition The initial condition of the problem.
     * @param function A Function object that includes the actual function of the problem
     * @param a The matrix of coefficients for the Runge-Kutta method.
     * @param b The vector of coefficients for the Runge-Kutta method.
     * @param c The vector of coefficients for the Runge-Kutta method.
     */
    RungeKutta(double step_size, double initial_time, double final_time, Eigen::MatrixXd initial_condition, Function function, Eigen::MatrixXd a, Eigen::VectorXd b, Eigen::VectorXd c);
    /**
     * @brief Construct a new RungeKutta object.
     * @param step_size The step size for the solver.
     * @param initial_time The initial time of the problem.
     * @param final_time The final time of the problem.
     * @param initial_condition The initial condition of the problem.
     * @param function A Function object that includes the actual function of the problem
     */
    RungeKutta(double step_size, double initial_time, double final_time, Eigen::MatrixXd initial_condition, Function function);
    /**
     * @brief Destroy the RungeKutta object.
     */
    ~RungeKutta();
    /**
     * @brief Set the matrix of coefficients for the Runge-Kutta method.
     * @param a The matrix of coefficients for the Runge-Kutta method.
     */
    void SetA(Eigen::MatrixXd a);
    /**
     * @brief Set the vector of coefficients for the Runge-Kutta method.
     * @param b The vector of coefficients for the Runge-Kutta method.
     */
    void SetB(Eigen::VectorXd b);
    /**
     * @brief Set the vector of coefficients for the Runge-Kutta method.
     * @param c The vector of coefficients for the Runge-Kutta method.
     */
    void SetC(Eigen::VectorXd c);
    /**
     * @brief Solve the ODE using the Runge-Kutta method.
     * @return An Eigen::MatrixXd containing the solution of the ODE at each time step.
     */
    Eigen::MatrixXd Solve() override;
    
protected: 
    /**
     * @brief The matrix of coefficients for the Runge-Kutta method.
     */
    Eigen::MatrixXd a;
    /**
     * @brief The vector of coefficients for the Runge-Kutta method.
     */
    Eigen::VectorXd b;
    /**
     * @brief The vector of coefficients for the Runge-Kutta method.
     */
    Eigen::VectorXd c;
};

#endif