#include "AdamBashforthOneStep.h"

AdamBashforthOneStep::AdamBashforthOneStep()
{

}

AdamBashforthOneStep::~AdamBashforthOneStep()
{

}

AdamBashforthOneStep::AdamBashforthOneStep(double step_size, double initial_time, double final_time, Eigen::MatrixXd initial_condition, Function function) : AdamBashforth(step_size, initial_time, final_time, initial_condition, function)
{
    SetBeta();
}

void AdamBashforthOneStep::SetBeta()
{
    this->beta = Eigen::VectorXd::Ones(1);
}

