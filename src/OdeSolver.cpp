#include "OdeSolver.h"

OdeSolver::OdeSolver()
{
}

OdeSolver::OdeSolver(double step_size, double initial_time, double final_time, Eigen::MatrixXd initial_condition, Function function)
{   
    if (step_size <= 0)
        throw std::invalid_argument("Step size must be positive");
    if (initial_time >= final_time)
        throw std::invalid_argument("Initial time must be smaller than final time");
    this->step_size = step_size;
    this->initial_time = initial_time;
    this->final_time = final_time;
    this->initial_condition = initial_condition;
    this->function = function;
}

OdeSolver::~OdeSolver()
{

}

void OdeSolver::SetStepSize(double step_size)
{
    if (step_size <= 0)
        throw std::invalid_argument("Step size must be positive");
    this->step_size = step_size;
}

void OdeSolver::SetTimeInterval(double initial_time, double final_time)
{
    if (initial_time >= final_time)
        throw std::invalid_argument("Initial time must be smaller than final time");
    this->initial_time = initial_time;
    this->final_time = final_time;
}

void OdeSolver::SetInitialCondition(Eigen::MatrixXd initial_condition)
{
    this->initial_condition = initial_condition;
}

void OdeSolver::SetFunction(Function function)
{
    this->function = function;
}


