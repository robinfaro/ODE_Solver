#include "OdeSolver.h"

OdeSolver::OdeSolver()
{
}

OdeSolver::OdeSolver(double step_size, double initial_time, double final_time, Eigen::MatrixXd initial_condition, Function function)
{   
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
    this->step_size = step_size;
}

void OdeSolver::SetTimeInterval(double initial_time, double final_time)
{
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


