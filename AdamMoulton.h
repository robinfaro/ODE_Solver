#ifndef ADAMMOULTON_H
#define ADAMMOULTON_H

#pragma once

#include <Eigen/Dense>
#include "MultiStep.h"

class AdamMoulton : public MultiStep
{
public:
    AdamMoulton();
    ~AdamMoulton();
    AdamMoulton(double step_size, double initial_time, double final_time, Eigen::MatrixXd initial_condition, Function function, Eigen::VectorXd beta);
    AdamMoulton(double step_size, double initial_time, double final_time, Eigen::MatrixXd initial_condition, Function function);
    Eigen::MatrixXd Solve() override;

private:
    void SetAlpha();

};

#endif