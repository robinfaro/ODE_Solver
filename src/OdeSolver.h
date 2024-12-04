#ifndef ODESOLVER_H
#define ODESOLVER_H

#pragma once
#include <Eigen/Dense>
#include <iostream>
#include <fstream>
#include "Function.h"

class OdeSolver
{
protected:
    double step_size;
    double initial_time;
    double final_time;
    Eigen::MatrixXd initial_condition;
    Function function;
public:
    OdeSolver();
    OdeSolver(double step_size, double initial_time, double final_time, Eigen::MatrixXd initial_condition, Function function);
    ~OdeSolver();
    void SetStepSize(double step_size);
    void SetTimeInterval(double initial_time, double final_time);
    void SetInitialCondition(Eigen::MatrixXd initial_condition);
    void SetFunction(Function function);
    virtual Eigen::MatrixXd Solve() = 0;
};

#endif //ODESOLVER_H