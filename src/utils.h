/**
 * @file utils.h
 * @brief Utility functions and structures for numerical methods and matrix operations.
 */
#ifndef UTILS_H
#define UTILS_H

#include <Eigen/Dense>

// Function to check if a matrix is lower triangular
/**
 * @brief Checks if a given matrix is lower triangular.
 * 
 * A matrix is lower triangular if all elements above the diagonal are zero.
 * 
 * @param matrix The matrix to check.
 * @return true if the matrix is lower triangular, false otherwise.
 */
bool IsLowerTriangular(const Eigen::MatrixXd& matrix);

/**
 * @brief Checks if a given 2D vector represents a square matrix.
 * 
 * A 2D vector is considered square if the number of rows equals the number of columns.
 * 
 * @param matrix The 2D vector to check.
 * @return true if the 2D vector is square, false otherwise.
 */
bool IsSquareMatrix(const std::vector<std::vector<std::string>>& matrix);

/**
 * @brief Prints a vector to the console.
 * 
 * Useful for debugging or displaying vector contents.
 * 
 * @param vec The vector to print.
 * @param name The name or label of the vector.
 */
void printVector(const Eigen::VectorXd& vec, const std::string& name);

/**
 * @brief Prints a matrix to the console.
 * 
 * Useful for debugging or displaying matrix contents.
 * 
 * @param mat The matrix to print.
 * @param name The name or label of the matrix.
 */
void printMatrix(const Eigen::MatrixXd& mat, const std::string& name);

/**
 * @brief A structure to hold input parameters for numerical methods.
 * 
 * This structure encapsulates the required and optional parameters for
 * solving ODEs using various numerical methods, such as Runge-Kutta, 
 * Adams-Bashforth, and Backward Differentiation Formulas (BDF).
 */
struct InputParameters {
    int num_equations; ///< Number of equations in the ODE system.
    std::vector<std::vector<std::string>> function_matrix; ///< Function matrix (mandatory).
    std::vector<std::vector<std::string>> derivative_matrix; ///< Derivative matrix (optional).
    int method; ///< The method to use for solving the ODEs (e.g., RK, AB, AM, BDF).
    double initial_time; ///< The initial time for the simulation.
    double final_time; ///< The final time for the simulation.
    double step_size; ///< The step size for the numerical method.
    int num_steps; ///< Number of steps for the simulation.
    Eigen::MatrixXd initial_condition; ///< The initial condition matrix for the ODE system.
    int num_stage; ///< Number of stages for Runge-Kutta methods (mandatory).
    Eigen::MatrixXd a; ///< The matrix for Runge-Kutta methods (optional).
    Eigen::VectorXd b; ///< The coefficient vector for Runge-Kutta methods (optional).
    Eigen::VectorXd c; ///< The node vector for Runge-Kutta methods (optional).
    Eigen::VectorXd alpha; ///< Coefficients for Adams-Bashforth or BDF methods (optional).
    Eigen::VectorXd beta; ///< Coefficients for Adams-Moulton or BDF methods (optional).
};

/**
 * @brief Parses an input file to extract parameters for numerical methods.
 * 
 * Reads an input file and extracts the parameters needed for solving ODEs.
 * 
 * @param filename The name of the input file.
 * @return InputParameters A structure containing the parsed parameters.
 */
InputParameters parseInputFile(const std::string& filename);


#endif // UTILS_H