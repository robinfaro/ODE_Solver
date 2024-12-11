#include "BackwardEuler.h"

BackwardEuler::BackwardEuler()
{

}

BackwardEuler::BackwardEuler(double step_size, double initial_time, double final_time, Eigen::MatrixXd initial_condition, Function function) : AdamMoulton(step_size, initial_time, final_time, initial_condition, function)
{
    SetBeta();
}

BackwardEuler::~BackwardEuler()
{

}

void BackwardEuler::SetBeta()
{
    beta = Eigen::VectorXd::Zero(2);
    beta(0) = 1.0;
    beta(1) = 0.0;
}