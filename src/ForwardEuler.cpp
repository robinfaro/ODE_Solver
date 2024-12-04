#include "ForwardEuler.h"
#include "OdeSolver.h"

ForwardEuler::ForwardEuler()
{

}

ForwardEuler::~ForwardEuler()
{

}

ForwardEuler::ForwardEuler(double step_size, double initial_time, double final_time, Eigen::MatrixXd initial_condition, Function function) : RungeKutta(step_size, initial_time, final_time, initial_condition, function)
{
    SetA();
    SetB();
    SetC();
}

void ForwardEuler::SetA()
{
    this->a = Eigen::MatrixXd::Zero(1, 1);
}

void ForwardEuler::SetB()
{
    this->b = Eigen::VectorXd::Ones(1);
}

void ForwardEuler::SetC()
{
    this->c = Eigen::VectorXd::Zero(1);
}