/**
 * @file main.cpp
 * @brief Main file for the ODE_Solver project.
 */

#include <iostream>
#include <Eigen/Dense>
#include <vector>
#include <cmath>
#include <string>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <regex>


#include "ForwardEuler.h"
#include "OdeSolver.h"
#include "RungeKutta.h"
#include "Function.h"
#include "AdamBashforth.h"
#include "AdamMoulton.h"
#include "BDF.h"
#include "MultiStep.h"
#include "NewtonMethod.h"
#include "AdamBashforthOneStep.h"
#include "AdamBashforthTwoSteps.h"
#include "AdamBashforthThreeSteps.h"
#include "AdamBashforthFourSteps.h"
#include "BackwardEuler.h"
#include "utils.h"

/**
 * @brief Parse the input file and Prints the solution of the required ODE with the specified method.
 * 
 * @param filename The name of the input file.
 * @throws std::runtime_error If the number of equations is not provided.
 * @throws std::runtime_error If the method is not provided.
 * @throws std::runtime_error If the initial time is not provided.
 * @throws std::runtime_error If the final time is not provided.
 * @throws std::runtime_error If the step size is not provided.
 * @throws std::runtime_error If the function matrix is not provided.
 * @throws std::runtime_error If the function matrix has a different number of rows than the number of equations.
 * @throws std::runtime_error If the initial condition matrix has a different number of rows than the number of equations.
 * @throws std::runtime_error If the initial condition matrix has a different number of columns than the number of steps.
 */
int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file>" << std::endl;
    }
    std::string filename = argv[1];
    InputParameters params = ParseInputFile(filename);

    if (params.num_equations == -1){
        throw std::runtime_error("Number of equations is not provided.");
    }

    if (params.method == -1){
        throw std::runtime_error("Method is not provided.");
    }

    if (params.initial_time == -1){
        throw std::runtime_error("Initial time is not provided.");
    }

    if (params.final_time == -1){
        throw std::runtime_error("Final time is not provided.");
    }

    if (params.step_size == -1){
        throw std::runtime_error("Step size is not provided.");
    }

    if (params.function_matrix.size() == 0){
        throw std::runtime_error("Function matrix is not provided.");
    }
    bool provided_derivative = false;
    if (params.function_matrix.size() != params.num_equations){
        throw std::runtime_error("Invalid row dimension in the function matrix.");
    }

    Function function(params.function_matrix);
    if (params.derivative_matrix[0][0] == ""){
        std::cout << "Derivative matrix is not provided. Be aware that only explicit methods can be employed." << std::endl;
    }
    else{
        function.SetDerivativeCombination(params.derivative_matrix);
        provided_derivative = true;
    }

    double step_size = params.step_size;
    double initial_time = params.initial_time;
    double final_time = params.final_time;
    if (params.num_equations != params.initial_condition.rows()){
        throw std::runtime_error("Invalid row dimension in the initial condition matrix, it should match the number of equations.");
    }
    if (params.num_steps!= params.initial_condition.cols()){
        throw std::runtime_error("Invalid column dimension in the initial condition matrix, it should match the number of steps.");
    }
    Eigen::MatrixXd initial_condition = params.initial_condition;
    int num_steps = params.num_steps;

    switch(params.method){
        case 1:
            {
            std::cout << "Forward Euler method" << std::endl;
            ForwardEuler solver(step_size, initial_time, final_time, initial_condition, function);
            Eigen::MatrixXd approximations = solver.Solve();
            PrintMatrix(approximations, "Approximations");
            break;
            }
            
        case 2:
            {
            std::cout << "Adam-Bashforth one-step" << std::endl;
            AdamBashforthOneStep solver(step_size, initial_time, final_time, initial_condition, function);
            Eigen::MatrixXd approximations = solver.Solve();
            PrintMatrix(approximations, "Approximations");
            break;
            }
        case 3:
            {
            std::cout << "Adam-Bashforth two-steps" << std::endl;
            AdamBashforthTwoSteps solver(step_size, initial_time, final_time, initial_condition, function);
            Eigen::MatrixXd approximations = solver.Solve();
            PrintMatrix(approximations, "Approximations");
            break;
            }
        case 4:
            {
            std::cout << "Adam-Bashforth three-steps" << std::endl;
            AdamBashforthThreeSteps solver(step_size, initial_time, final_time, initial_condition, function);
            Eigen::MatrixXd approximations = solver.Solve();
            PrintMatrix(approximations, "Approximations");
            break;
            }
        case 5:
            {
            std::cout << "Adam-Bashforth four-steps" << std::endl;
            AdamBashforthFourSteps solver(step_size, initial_time, final_time, initial_condition, function);
            Eigen::MatrixXd approximations = solver.Solve();
            PrintMatrix(approximations, "Approximations");
            break;
            }
        case 6:
            {
            if (!provided_derivative){
                throw std::runtime_error("Derivative matrix is not provided for the Backward Euler method");
            }
            std::cout << "Backward Euler method" << std::endl; 
            BackwardEuler solver(step_size, initial_time, final_time, initial_condition, function);
            Eigen::MatrixXd approximations = solver.Solve();
            PrintMatrix(approximations, "Approximations");
            break;
            }
        case 7:
            {
            Eigen::MatrixXd a = params.a;
            Eigen::VectorXd b = params.b;
            Eigen::VectorXd c = params.c;
            if (a.size() == 0 || b.size() == 0 || c.size() == 0){
                throw std::runtime_error("Invalid Runge-Kutta method parameters. You should provide the matrix A, vector b, and vector c in the input file.");
            }
            std::cout << "Runge Kutta Method" << std::endl;
            RungeKutta solver(step_size, initial_time, final_time, initial_condition, function, a, b, c);
            Eigen::MatrixXd approximations = solver.Solve();
            PrintMatrix(approximations, "Approximations");
            break;
            }
        case 8:
            {
            std::cout << "Backward Differentiation Formula" << std::endl;
            Eigen::VectorXd alpha = params.alpha;
            if (alpha.size() == 0){
                throw std::runtime_error("Invalid BDF method parameters. You should provide the vector alpha in the input file.");
            }
            BDF solver(step_size, initial_time, final_time, initial_condition, function, alpha);
            Eigen::MatrixXd approximations = solver.Solve();
            PrintMatrix(approximations, "Approximations");
            break;
            }
        case 9:
            {
            Eigen::VectorXd beta = params.beta;
            if (beta.size() == 0){
                throw std::runtime_error("Invalid Adam-Moulton method parameters. You should provide the vector beta in the input file.");
            }
            std::cout << "Adam Moulton Method" << std::endl;
            AdamMoulton solver(step_size, initial_time, final_time, initial_condition, function, beta);
            Eigen::MatrixXd approximations = solver.Solve();
            PrintMatrix(approximations, "Approximations");
            break;
            }
        case 10:
            {
            Eigen::VectorXd beta = params.beta;
            if (beta.size() == 0){
                throw std::runtime_error("Invalid Adam-Bashforth method parameters. You should provide the vector beta in the input file.");
            }            
            std::cout << "Generic Adam-Bashforth Method" << std::endl;
            AdamBashforth solver(step_size, initial_time, final_time, initial_condition, function, beta);
            Eigen::MatrixXd approximations = solver.Solve();
            PrintMatrix(approximations, "Approximations");
            break;
            }
        default:
            std::cout << "Invalid method" << std::endl;
            break;
    }

}
