#ifndef ADAMBASHFORTH_H
#define ADAMBASHFORTH_H

#pragma once
#include <Eigen/Dense>
#include "MultiStep.h"


class AdamBashforth : public MultiStep
{
public:
    AdamBashforth();
    ~AdamBashforth();
    AdamBashforth(double step_size, double initial_time, double final_time, Eigen::MatrixXd initial_condition, Function function, Eigen::VectorXd beta);
    AdamBashforth(double step_size, double initial_time, double final_time, Eigen::MatrixXd initial_condition, Function function);
    Eigen::MatrixXd Solve() override;

private:
    void SetAlpha();
};

#endif