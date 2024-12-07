#include "AdamBashforthTwoSteps.h"

AdamBashforthTwoSteps::AdamBashforthTwoSteps()
{

}

AdamBashforthTwoSteps::~AdamBashforthTwoSteps()
{

}

AdamBashforthTwoSteps::AdamBashforthTwoSteps(double step_size, double initial_time, double final_time, Eigen::MatrixXd initial_condition, Function function) : AdamBashforth(step_size, initial_time, final_time, initial_condition, function)
{
    SetBeta();
}

void AdamBashforthTwoSteps::SetBeta()
{
    beta = Eigen::VectorXd::Zero(2);
    beta(0) = 3.0 / 2.0;
    beta(1) = -1.0 / 2.0;
}