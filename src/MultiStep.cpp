#include "MultiStep.h"

MultiStep::MultiStep()
{

}

MultiStep::~MultiStep()
{

}

MultiStep::MultiStep(double step_size, double initial_time, double final_time, Eigen::MatrixXd initial_condition, Function function, Eigen::VectorXd alpha, Eigen::VectorXd beta) : OdeSolver(step_size, initial_time, final_time, initial_condition, function)
{
    if (alpha.size() != beta.size())
        throw std::invalid_argument("Alpha and beta must have the same size");
    if (initial_condition.cols() != alpha.size() - 1)
        throw std::invalid_argument("Initial condition must have the same number of columns as the size of alpha and beta");
    this->alpha = alpha;
    this->beta = beta;
}

MultiStep::MultiStep(double step_size, double initial_time, double final_time, Eigen::MatrixXd initial_condition, Function function, Eigen::VectorXd coefficient, CoeffType coeff_type) : OdeSolver(step_size, initial_time, final_time, initial_condition, function)
{
    if (coefficient.size() - 1 != initial_condition.cols())
        throw std::invalid_argument("Coefficient must have the same size as the number of columns of the initial condition");
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