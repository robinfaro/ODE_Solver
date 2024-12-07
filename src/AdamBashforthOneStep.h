#ifndef ADAMBASHFORTHONESTEP_H
#define ADAMBASHFORTHONESTEP_H

#pragma once

#include <Eigen/Dense>
#include "AdamBashforth.h"

class AdamBashforthOneStep : public AdamBashforth
{
public:
    AdamBashforthOneStep();
    ~AdamBashforthOneStep();
    AdamBashforthOneStep(double step_size, double initial_time, double final_time, Eigen::MatrixXd initial_condition, Function function);

private:
    void SetBeta();
};

#endif