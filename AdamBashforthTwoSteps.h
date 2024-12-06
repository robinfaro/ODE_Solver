#ifndef ADAMBASHFORTHTWOSTEPS_H
#define ADAMBASHFORTHTWOSTEPS_H

#pragma once

#include <Eigen/Dense>
#include "AdamBashforth.h"

class AdamBashforthTwoSteps : public AdamBashforth
{
public:
    AdamBashforthTwoSteps();
    ~AdamBashforthTwoSteps();
    AdamBashforthTwoSteps(double step_size, double initial_time, double final_time, Eigen::MatrixXd initial_condition, Function function);

private:
    void SetBeta();
};



#endif