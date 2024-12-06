#ifndef NEWTONMETHOD_H
#define NEWTONMETHOD_H

#pragma once

#include <Eigen/Dense>
#include "Function.h"

class NewtonMethod
{
public:
    NewtonMethod();
    ~NewtonMethod();
    NewtonMethod(Function function, Eigen::VectorXd y0, double t);
    NewtonMethod(Function function, Eigen::VectorXd y0, double t, double beta, Eigen::VectorXd constant_term, double step_size);
    NewtonMethod(Function function, Eigen::VectorXd y0, double t, double alpha, double step_size);
    void SetFunction(Function function);
    void SetInitialGuess(Eigen::VectorXd y0);
    Eigen::VectorXd Solve();
private:
    Function function;
    Eigen::VectorXd y0;
    double tol = 1e-4;
    double t;
    double h = 0.01;
    double step_size;

    Eigen::VectorXd constant_term;
    double beta = 1.0;
    double alpha = 1.0;

};

#endif