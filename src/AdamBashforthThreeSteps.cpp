#include "AdamBashforthThreeSteps.h"

AdamBashforthThreeSteps::AdamBashforthThreeSteps()
{

}

AdamBashforthThreeSteps::~AdamBashforthThreeSteps()
{

}

AdamBashforthThreeSteps::AdamBashforthThreeSteps(double step_size, double initial_time, double final_time, Eigen::MatrixXd initial_condition, Function function) : AdamBashforth(step_size, initial_time, final_time, initial_condition, function)
{
    SetBeta();
}

void AdamBashforthThreeSteps::SetBeta()
{
    beta = Eigen::VectorXd::Zero(3);
    beta(0) = 23.0 / 12.0;
    beta(1) = -16.0 / 12.0;
    beta(2) = 5.0 / 12.0;
}