/**
 * @file Function.h
 * @brief Defines the Function class for representing mathematical functions and their derivatives for ODE problems.
 */
#ifndef FUNCTION_H
#define FUNCTION_H

#pragma once
#include <Eigen/Dense>
#include <cmath>
#include <string>
#include <vector>
#include <regex>

/**
 * @brief A class for representing and evaluating mathematical functions and their derivatives.
 * 
 * This class is designed to handle mathematical functions used in ODE solvers.
 * It provides methods to define function combinations, apply them, and compute
 * the right-hand side and Jacobian matrices for ODE systems.
 */
class Function
{
public:
    /**
     * @brief Construct a new Function object.
     */
    Function();
   
   /**
     * @brief Construct a new Function object with function and derivative combinations.
     * 
     * @param function_combination A 2D vector of strings representing function combinations.
     * @param derivative_combination A 2D vector of strings representing derivative combinations.
     * @throws std::invalid_argument If the derivative combination is not a square matrix.
     */
    Function(std::vector<std::vector<std::string>> function_combination, std::vector<std::vector<std::string>> derivative_combination);

    /**
     * @brief Construct a new Function object with function combinations.
     * 
     * @param function_combination A 2D vector of strings representing function combinations.
     */
    Function(std::vector<std::vector<std::string>> function_combination);

    /**
     * @brief Destroy the Function object.
     */
    ~Function();

    /**
     * @brief Set the function combination for the Function object.
     * 
     * @param function_combination A 2D vector of strings representing function combinations.
     */
    void SetFunctionCombination(std::vector<std::vector<std::string>> function_combination);

    /**
     * @brief Set the derivative combination for the Function object.
     * 
     * @param derivative_combination A 2D vector of strings representing derivative combinations.
     */ 
    void SetDerivativeCombination(std::vector<std::vector<std::string>> derivative_combination);

    /**
     * @brief Apply a specified function to a given variable and parameter.
     * 
     * @param function The function ID (1-7) to apply.
     * @param variable The variable input to the function.
     * @param param The parameter input to the function.
     * @return double The result of applying the function.
     * @throws std::invalid_argument If the function ID is invalid.
     */
    double ApplyFunction(int function, double variable, double param);

    /**
     * @brief Build the right-hand side of the ODE system.
     * 
     * @param t The current time.
     * @param y The current state vector.
     * @return Eigen::VectorXd The right-hand side vector of the ODE system.
     * @throws std::invalid_argument If the input format for any function entry is invalid.
     */
    Eigen::VectorXd BuildRightHandSide(double t, Eigen::VectorXd y);

    /**
     * @brief Build the Jacobian matrix of the ODE system.
     * 
     * @param t The current time.
     * @param y The current state vector.
     * @return Eigen::MatrixXd The Jacobian matrix of the ODE system.
     * @throws std::invalid_argument If the input format for any derivative entry is invalid.
     */
    Eigen::MatrixXd BuildJacobian(double t, Eigen::VectorXd y);

private:
    
    std::vector<std::vector<std::string>> function_combination;  //< A 2D vector of strings representing function combinations.
    std::vector<std::vector<std::string>> derivative_combination;   //< A 2D vector of strings representing derivative combinations.
    std::regex pattern;  //< A regex pattern for parsing function entries.
    std::smatch match;  //< A regex match object for parsing function entries.

    /**
     * @brief Function 1: sine function.
     * 
     * @param x The input variable.
     * @param param The input parameter.
     * 
     * @return The result of the sin (param * x) 
     */
    double f1(double x, double param);

    /**
     * @brief Function 2: cosine function.
     * 
     * @param x The input variable.
     * @param param The input parameter.
     * 
     * @return The result of the cos (param * x) 
     */
    double f2(double x, double param);

    /**
     * @brief Function 3: exponential function.
     * 
     * @param x The input variable.
     * @param param The input parameter.
     * 
     * @return The result of the exp (param * x) 
     */
    double f3(double x, double param);

    /**
     * @brief Function 4: power function.
     * 
     * @param x The input variable.
     * @param param The input parameter.
     * 
     * @return The result of the pow (x, param) 
     */
    double f4(double x, double param);

    /**
     * @brief Function 5: logarithmic function.
     * 
     * @param x The input variable.
     * @param param The input parameter.
     * 
     * @return The result of the log (param * x) 
     */
    double f5(double x, double param);

    /**
     * @brief Function 6: identity function.
     * 
     * @param x The input variable.
     * @param param The input parameter.
     * 
     * @return The result of the param * x 
     */
    double f6(double x, double param);

    /**
     * @brief Function 7: constant function.
     * 
     * @param x The input variable.
     * @param param The input parameter.
     * 
     * @return The result of the param 
     */
    double f7(double x, double param); //constant
};


#endif