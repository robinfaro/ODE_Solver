#ifndef FORWARDEULER_H
#define FORWARDEULER_H

#pragma once
#include <Eigen/Dense>
#include "OdeSolver.h"
#include "RungeKutta.h"

class ForwardEuler : public RungeKutta
{
public:
    ForwardEuler();
    ForwardEuler(double step_size, double initial_time, double final_time, Eigen::MatrixXd initial_condition, Function function);
    ~ForwardEuler();

private:
    void SetA();
    void SetB();
    void SetC();
};

#endif