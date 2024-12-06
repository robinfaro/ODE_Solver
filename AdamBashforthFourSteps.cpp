#include "AdamBashforthFourSteps.h"

AdamBashforthFourSteps::AdamBashforthFourSteps()
{

}

AdamBashforthFourSteps::~AdamBashforthFourSteps()
{

}

AdamBashforthFourSteps::AdamBashforthFourSteps(double step_size, double initial_time, double final_time, Eigen::MatrixXd initial_condition, Function function) : AdamBashforth(step_size, initial_time, final_time, initial_condition, function)
{
    SetBeta();
}

void AdamBashforthFourSteps::SetBeta()
{
    beta = Eigen::VectorXd::Zero(4);
    beta(0) = 55.0 / 24.0;
    beta(1) = -59.0 / 24.0;
    beta(2) = 37.0 / 24.0;
    beta(3) = -9.0 / 24.0;
}