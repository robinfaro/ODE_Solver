#ifndef ADAMBASHFORTHFOURSTEPS_H
#define ADAMBASHFORTHFOURSTEPS_H

#pragma once

#include <Eigen/Dense>
#include "AdamBashforth.h"

class AdamBashforthFourSteps : public AdamBashforth
{
public:
    AdamBashforthFourSteps();
    ~AdamBashforthFourSteps();
    AdamBashforthFourSteps(double step_size, double initial_time, double final_time, Eigen::MatrixXd initial_condition, Function function);

private:
    void SetBeta();

};

#endif