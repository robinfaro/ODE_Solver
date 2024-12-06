#ifndef BDF_H
#define BDF_H

#pragma once

#include <Eigen/Dense>
#include "MultiStep.h"

class BDF : public MultiStep
{
public:
    BDF();
    BDF(double step_size, double initial_time, double final_time, Eigen::MatrixXd initial_condition, Function function, Eigen::VectorXd alpha);
    ~BDF();
    Eigen::MatrixXd Solve() override;
    
private:
    void SetBeta();

};

#endif