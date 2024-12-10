/**
 * @file utils.h
 * @brief Utility functions and structures for numerical methods and matrix operations.
 */
#ifndef UTILS_H
#define UTILS_H

#include <Eigen/Dense>

/**
 * @brief Parses a string potentially representing a fraction and returns the result as a double.
 * 
 * The function parses a string representing a fraction and returns the result as a double.
 * The fraction should be in the form "numerator/denominator". If the string does not contain
 * a '/', the function will attempt to parse the string as a plain number.
 * 
 * @param fraction The string representing the fraction.
 * @return double The result of the fraction as a double.
 * @throws std::invalid_argument if the denominator is zero.
 */
double ParseFraction(const std::string& fraction);

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
void PrintVector(const Eigen::VectorXd& vec, const std::string& name);

/**
 * @brief Prints a matrix to the console.
 * 
 * Useful for debugging or displaying matrix contents.
 * 
 * @param mat The matrix to print.
 * @param name The name or label of the matrix.
 */
void PrintMatrix(const Eigen::MatrixXd& mat, const std::string& name);

/**
 * @brief A structure to hold input parameters for numerical methods.
 * 
 * This structure encapsulates the required and optional parameters for
 * solving ODEs using various numerical methods, such as Runge-Kutta, 
 * Adams-Bashforth, and Backward Differentiation Formulas (BDF).
 */
struct InputParameters {
    int num_equations = 0; ///< Number of equations in the ODE system.
    std::vector<std::vector<std::string>> function_matrix; ///< Function matrix (mandatory).
    std::vector<std::vector<std::string>> derivative_matrix; ///< Derivative matrix (optional).
    int method = -1; ///< The method to use for solving the ODEs (e.g., RK, AB, AM, BDF).
    double initial_time = -1; ///< The initial time for the simulation.
    double final_time = -1; ///< The final time for the simulation.
    double step_size = -1; ///< The step size for the numerical method.
    int num_steps = -1; ///< Number of steps for the simulation.
    Eigen::MatrixXd initial_condition; ///< The initial condition matrix for the ODE system.
    int num_stage; ///< Number of stages for Runge-Kutta methods (mandatory).
    Eigen::MatrixXd a = Eigen::MatrixXd(0, 0); ///< The matrix for Runge-Kutta methods (optional).
    Eigen::VectorXd b = Eigen::VectorXd(0); ///< The coefficient vector for Runge-Kutta methods (optional).
    Eigen::VectorXd c = Eigen::VectorXd(0); ///< The node vector for Runge-Kutta methods (optional).
    Eigen::VectorXd alpha = Eigen::VectorXd(0); ///< Coefficients for Adams-Bashforth or BDF methods (optional).
    Eigen::VectorXd beta = Eigen::VectorXd(0); ///< Coefficients for Adams-Moulton or BDF methods (optional).
};

/**
 * @brief Parses an input file to extract parameters for numerical methods.
 * 
 * Reads an input file and extracts the parameters needed for solving ODEs.
 * 
 * @param filename The name of the input file.
 * @return InputParameters A structure containing the parsed parameters.
 * @throws std::runtime_error if the input file is not found or if there is an error in the input file.
 */
InputParameters ParseInputFile(const std::string& filename);


#endif // UTILS_H