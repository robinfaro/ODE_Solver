#ifndef ADAMBASHFORTHTHREESTEPS_H
#define ADAMBASHFORTHTHREESTEPS_H

#pragma once

#include <Eigen/Dense>
#include "AdamBashforth.h"

class AdamBashforthThreeSteps : public AdamBashforth
{
public:
    AdamBashforthThreeSteps();
    ~AdamBashforthThreeSteps();
    AdamBashforthThreeSteps(double step_size, double initial_time, double final_time, Eigen::MatrixXd initial_condition, Function function);

private:
    void SetBeta();

};

#endif