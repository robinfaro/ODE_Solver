#include "MultiStep.h"

MultiStep::MultiStep()
{

}

MultiStep::~MultiStep()
{

}

MultiStep::MultiStep(double step_size, double initial_time, double final_time, Eigen::MatrixXd initial_condition, Function function, Eigen::VectorXd alpha, Eigen::VectorXd beta) : OdeSolver(step_size, initial_time, final_time, initial_condition, function)
{
    this->alpha = alpha;
    this->beta = beta;
}

MultiStep::MultiStep(double step_size, double initial_time, double final_time, Eigen::MatrixXd initial_condition, Function function, Eigen::VectorXd coefficient, CoeffType coeff_type) : OdeSolver(step_size, initial_time, final_time, initial_condition, function)
{
    if (coeff_type == ALPHA)
    {
        this->alpha = coefficient;
    }
    else if (coeff_type == BETA)
    {
        this->beta = coefficient;
    }
}


MultiStep::MultiStep(double step_size, double initial_time, double final_time, Eigen::MatrixXd initial_condition, Function function) : OdeSolver(step_size, initial_time, final_time, initial_condition, function)
{

}

void MultiStep::SetAlpha(Eigen::VectorXd alpha)
{
    this->alpha = alpha;
}

void MultiStep::SetBeta(Eigen::VectorXd beta)
{
    this->beta = beta;
}