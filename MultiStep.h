#ifndef MULTISTEP_H
#define MULTISTEP_H

#pragma once
#include <Eigen/Dense>
#include "OdeSolver.h"

enum CoeffType { ALPHA, BETA };

class MultiStep : public OdeSolver
{
public:
    MultiStep();
    ~MultiStep();
    MultiStep(double step_size, double initial_time, double final_time, Eigen::MatrixXd initial_condition, Function function, Eigen::VectorXd alpha, Eigen::VectorXd beta);
    MultiStep(double step_size, double initial_time, double final_time, Eigen::MatrixXd initial_condition, Function function, Eigen::VectorXd coefficent, CoeffType coeff_type);
    //MultiStep(double step_size, double initial_time, double final_time, Eigen::MatrixXd initial_condition, Function function, Eigen::VectorXd beta);
    MultiStep(double step_size, double initial_time, double final_time, Eigen::MatrixXd initial_condition, Function function);
    void SetAlpha(Eigen::VectorXd alpha);
    void SetBeta(Eigen::VectorXd beta);

protected:
    Eigen::VectorXd alpha;
    Eigen::VectorXd beta;
};

#endif