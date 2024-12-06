#ifndef BACKWARDEULER_H
#define BACKWARDEULER_H

#pragma once

#include <Eigen/Dense>
#include "AdamMoulton.h"

class BackwardEuler : public AdamMoulton
{
public:
    BackwardEuler();
    BackwardEuler(double step_size, double initial_time, double final_time, Eigen::MatrixXd initial_condition, Function function);
    ~BackwardEuler();

private:
    void SetBeta();
};

#endif