#include <iostream>
#include <Eigen/Dense>
#include <vector>
#include <cmath>
#include <string>
#include <fstream>
#include <sstream>
#include <stdexcept>


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


int main(int, char**){
    // InputParameters params = parseInputFile("../input_example.txt");

    // std::cout << "Number of equations: " << params.num_equations << std::endl;
    // std::cout << "Function matrix:" << std::endl;
    // for (const auto& row : params.function_matrix) {
    //     for (const auto& entry : row) {
    //         std::cout << entry << " ";
    //     }
    //     std::cout << std::endl;
    // }

    // std::cout << "Derivative matrix:" << std::endl;
    // for (const auto& row : params.derivative_matrix) {
    //     for (const auto& entry : row) {
    //         std::cout << entry << " ";
    //     }
    //     std::cout << std::endl;
    // }

    // std::cout << "Method: " << params.method << std::endl;

    // std::cout << "Initial time: " << params.initial_time << std::endl;

    // std::cout << "Final time: " << params.final_time << std::endl;

    // std::cout << "Step size: " << params.step_size << std::endl;

    // std::cout << "Number of steps: " << params.num_steps << std::endl;

    // std::cout << "Initial condition:" << std::endl;

    // printMatrix(params.initial_condition, "Initial condition");

    // std::cout << "Number of stages: " << params.num_stage << std::endl;

    // printMatrix(params.a, "Matrix A");

    // printVector(params.b, "Vector b");

    // printVector(params.c, "Vector c");

    // printVector(params.alpha, "Vector alpha");

    // printVector(params.beta, "Vector beta");


    std::vector<std::vector<std::string>> function_combination = {{"+1_6_1", "0", "+1_6_1"}, {"+1_1_1", "-1_6_1", "0"}};
    std::vector<std::vector<std::string>> derivative_combination = {{"0", "+1_7_1"}, {"-1_7_1", "0"}};

    Function function(function_combination, derivative_combination);


    // TEST FUNCTION CLASS

    // Eigen::VectorXd y0(2);
    // y0(0) = 1;
    // y0(1) = 0;

    // double t0 = 0;

    //auto rhs = function.BuildRightHandSide(t0, y0);
    //auto jacobian = function.BuildJacobian(t0, y0);

    //printVector(rhs, "Right hand side");

    //printMatrix(jacobian, "Jacobian");

    // TEST FORWARD EULER SOLVER

    // double initial_time = 0;
    // double final_time = 1.0;
    // double step_size = 0.1;
    // Eigen::VectorXd initial_condition(2);
    // initial_condition(0) = 1;
    // initial_condition(1) = 0;

    // ForwardEuler forward_euler(step_size, initial_time, final_time, initial_condition, function);

    // Eigen::MatrixXd solution = forward_euler.Solve();

    // printMatrix(solution, "Forward Euler solution");

    // RUNGE KUTTA 4 TEST CASE

    // double initial_time = 0;
    // double final_time = 1;
    // double step_size = 0.1;
    // Eigen::VectorXd initial_condition(2);
    // initial_condition(0) = 1;
    // initial_condition(1) = 0;
    // Eigen::VectorXd b(4);
    // b << 1.0/6.0, 1.0/3.0, 1.0/3.0, 1.0/6.0;
    // Eigen::VectorXd c(4);
    // c << 0, 0.5, 0.5, 1;
    // Eigen::MatrixXd a(4, 4);
    // a << 0, 0, 0, 0,
    //      0.5, 0, 0, 0,
    //      0, 0.5, 0, 0,
    //      0, 0, 1, 0;
    
    // RungeKutta runge_kutta(step_size, initial_time, final_time, initial_condition, function, a, b, c);
    // Eigen::MatrixXd solution = runge_kutta.Solve();

    // printMatrix(solution, "Runge Kutta solution");

    // ADAM BASHFORTH-1 TEST CASE

    // double initial_time = 0;
    // double final_time = 1;
    // double step_size = 0.1;
    // Eigen::VectorXd initial_condition(2);
    // initial_condition(0) = 1;
    // initial_condition(1) = 0;

    // AdamBashforthOneStep adam_bashforth1(step_size, initial_time, final_time, initial_condition, function);

    // Eigen::MatrixXd solution = adam_bashforth1.Solve();

    // printMatrix(solution, "Adam Bashforth 1 solution");

    // ADAM BASHFORTH-2 TEST CASE

    // double initial_time = 0;
    // double final_time = 1;
    // double step_size = 0.1;
    // Eigen::MatrixXd initial_condition(2, 2);
    // initial_condition(0, 0) = 1;
    // initial_condition(1, 0) = 0;
    // initial_condition(0, 1) = 1;
    // initial_condition(1, 1) = -0.1;

    // AdamBashforthTwoSteps adam_bashforth2(step_size, initial_time, final_time, initial_condition, function);

    // Eigen::MatrixXd solution = adam_bashforth2.Solve();

    // printMatrix(solution, "Adam Bashforth 2 solution");

    // ADAM BASHFORTH-3 TEST CASE

    // double initial_time = 0;
    // double final_time = 1;
    // double step_size = 0.1;
    // Eigen::MatrixXd initial_condition(2, 3);
    // initial_condition(0, 0) = 1;
    // initial_condition(1, 0) = 0;
    // initial_condition(0, 1) = 1;
    // initial_condition(1, 1) = -0.1;
    // initial_condition(0, 2) = 1;
    // initial_condition(1, 2) = -0.19;

    // AdamBashforthThreeSteps adam_bashforth3(step_size, initial_time, final_time, initial_condition, function);

    // Eigen::MatrixXd solution = adam_bashforth3.Solve();

    // printMatrix(solution, "Adam Bashforth 3 solution");

    // ADAM BASHFORTH-4 TEST CASE

    // double initial_time = 0;
    // double final_time = 1;
    // double step_size = 0.1;
    // Eigen::MatrixXd initial_condition(2, 4);
    // initial_condition(0, 0) = 1;
    // initial_condition(1, 0) = 0;
    // initial_condition(0, 1) = 1;
    // initial_condition(1, 1) = -0.1;
    // initial_condition(0, 2) = 1;
    // initial_condition(1, 2) = -0.19;
    // initial_condition(0, 3) = 1;
    // initial_condition(1, 3) = -0.27;

    // AdamBashforthFourSteps adam_bashforth4(step_size, initial_time, final_time, initial_condition, function);

    // Eigen::MatrixXd solution = adam_bashforth4.Solve();

    // printMatrix(solution, "Adam Bashforth 4 solution");


    // ADAM MOULTON-1 -> BE TEST CASE

    double initial_time = 0;
    double final_time = 1;
    double step_size = 0.05;
    Eigen::MatrixXd initial_condition(2, 1);
    initial_condition(0, 0) = 1;
    initial_condition(1, 0) = 0;

    BackwardEuler be(step_size, initial_time, final_time, initial_condition, function);

    Eigen::MatrixXd solution = be.Solve();

    printMatrix(solution, "Backward Euler solution");

    // ADAM MOULTON-3 TEST CASE

    // double initial_time = 0;
    // double final_time = 1;
    // double step_size = 0.1;
    // Eigen::MatrixXd initial_condition(2, 3);
    // initial_condition(0, 0) = 1;
    // initial_condition(1, 0) = 0;
    // initial_condition(0, 1) = 1;
    // initial_condition(1, 1) = -0.1;
    // initial_condition(0, 2) = 1;
    // initial_condition(1, 2) = -0.19;

    // Eigen::VectorXd beta(4);

    // beta << 5.0/12.0, 2.0/3.0, -1.0/12.0, 0.0;

    // AdamMoulton adam_moulton(step_size, initial_time, final_time, initial_condition, function, beta);

    // Eigen::MatrixXd solution = adam_moulton.Solve();

    // printMatrix(solution, "Adam Moulton solution");

    // BDF-1 TEST CASE

    // double initial_time = 0;
    // double final_time = 1;
    // double step_size = 0.1;
    // Eigen::MatrixXd initial_condition(2, 1);
    // initial_condition(0, 0) = 1;
    // initial_condition(1, 0) = 0;

    // Eigen::VectorXd alpha(2);

    // alpha << 1.0, 1.0;

    // BDF bdf(step_size, initial_time, final_time, initial_condition, function, alpha);

    // Eigen::MatrixXd solution = bdf.Solve();

    // printMatrix(solution, "BDF solution");

    // BDF-4 TEST CASE

    // double initial_time = 0;
    // double final_time = 1;
    // double step_size = 0.1;
    // Eigen::MatrixXd initial_condition(2, 4);
    // initial_condition(0, 0) = 1;
    // initial_condition(1, 0) = 0;
    // initial_condition(0, 1) = 1;
    // initial_condition(1, 1) = -0.1;
    // initial_condition(0, 2) = 1;
    // initial_condition(1, 2) = -0.19;
    // initial_condition(0, 3) = 1;
    // initial_condition(1, 3) = -0.27;

    // Eigen::VectorXd alpha(5);

    // alpha << 25.0/12.0, 4.0, -3.0, 4.0/3.0, -1.0/4.0;

    // BDF bdf(step_size, initial_time, final_time, initial_condition, function, alpha);

    // Eigen::MatrixXd solution = bdf.Solve();

    // printMatrix(solution, "BDF solution");


    // TEST SCALAR FUNCTION

    // std::vector<std::vector<std::string>> function_combination = {{"+1_3_-1", "0"}};
    // std::vector<std::vector<std::string>> derivative_combination = {{"0"}};

    // Function function(function_combination, derivative_combination);

    // // // FORWARD EULER TEST CASE

    // double initial_time = 0;
    // double final_time = 2.0;
    // double step_size = 0.1;
    // Eigen::MatrixXd initial_condition(1, 1);
    // initial_condition(0, 0) = 1;

    // ForwardEuler forward_euler(step_size, initial_time, final_time, initial_condition, function);

    // Eigen::MatrixXd solution = forward_euler.Solve();

    // printMatrix(solution, "Forward Euler solution");


    



}
