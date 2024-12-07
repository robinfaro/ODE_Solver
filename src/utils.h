#ifndef UTILS_H
#define UTILS_H

#include <Eigen/Dense>

// Function to check if a matrix is lower triangular
bool IsLowerTriangular(const Eigen::MatrixXd& matrix);
bool IsSquareMatrix(const std::vector<std::vector<std::string>>& matrix);
void printVector(const Eigen::VectorXd& vec, const std::string& name);
void printMatrix(const Eigen::MatrixXd& mat, const std::string& name);
struct InputParameters {
    int num_equations;
    std::vector<std::vector<std::string>> function_matrix; // Function matrix (mandatory)
    std::vector<std::vector<std::string>> derivative_matrix; // Derivative matrix (optional)
    int method;
    double initial_time;
    double final_time;
    double step_size;
    int num_steps;
    Eigen::MatrixXd initial_condition;       // Initial condition matrix
    int num_stage;                              // Number of RK stages (mandatory)
    Eigen::MatrixXd a;             // RK method matrix (optional)
    Eigen::VectorXd b, c;                             // RK method vectors (optional)
    Eigen::VectorXd alpha, beta;        // For AB, AM, BDF methods (optional)
};
InputParameters parseInputFile(const std::string& filename);


#endif // UTILS_H