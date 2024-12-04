#ifndef RUNGEKUTTA_H
#define RUNGEKUTTA_H

#pragma once
#include <Eigen/Dense>
#include "OdeSolver.h"

class RungeKutta: public OdeSolver
{
public:
    RungeKutta();
    RungeKutta(double step_size, double initial_time, double final_time, Eigen::MatrixXd initial_condition, Function function, Eigen::MatrixXd a, Eigen::VectorXd b, Eigen::VectorXd c);
    RungeKutta(double step_size, double initial_time, double final_time, Eigen::MatrixXd initial_condition, Function function);
    ~RungeKutta();
    void SetA(Eigen::MatrixXd a);
    void SetB(Eigen::VectorXd b);
    void SetC(Eigen::VectorXd c);
    Eigen::MatrixXd Solve() override;
    
protected: 
    Eigen::MatrixXd a;
    Eigen::VectorXd b;
    Eigen::VectorXd c;
};

#endif