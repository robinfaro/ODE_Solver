#include "NewtonMethod.h"
#include <iostream>

NewtonMethod::NewtonMethod()
{

}

NewtonMethod::~NewtonMethod()
{

}

NewtonMethod::NewtonMethod(Function function, Eigen::VectorXd y0, double t)
{
    this->function = function;
    this->y0 = y0;
    this->t = t;
}

NewtonMethod::NewtonMethod(Function function, Eigen::VectorXd y0, double t, double beta, Eigen::VectorXd constant_term, double step_size)
{
    this->function = function;
    this->y0 = y0;
    this->t = t;
    this->beta = beta;
    this->constant_term = constant_term;
    this->step_size = step_size;

}

NewtonMethod::NewtonMethod(Function function, Eigen::VectorXd y0, double t, double alpha, double step_size)
{
    this->function = function;
    this->y0 = y0;
    this->t = t;
    this->alpha = alpha;
    this->step_size = step_size;
    this->constant_term = Eigen::VectorXd::Zero(y0.size());
}

void NewtonMethod::SetFunction(Function function)
{
    this->function = function;
}

void NewtonMethod::SetInitialGuess(Eigen::VectorXd y0)
{
    this->y0 = y0;
}

Eigen::VectorXd NewtonMethod::Solve()
{
    Eigen::VectorXd y = y0;
    Eigen::VectorXd y_new = y0;
    Eigen::VectorXd f = function.BuildRightHandSide(t, y);
    Eigen::MatrixXd J = function.BuildJacobian(t, y);

    f = alpha * y - y0 - step_size * (beta * f + constant_term);
    J = alpha * Eigen::MatrixXd::Identity(y.size(), y.size()) - step_size * beta * function.BuildJacobian(t, y);

    Eigen::VectorXd delta_y = J.colPivHouseholderQr().solve(-f);
    y_new += delta_y;
    while (delta_y.norm() > tol)
    {
        y = y_new;
        f = function.BuildRightHandSide(t,y);
        J = function.BuildJacobian(t,y);
        f = alpha * y - y0 - step_size * (beta * f + constant_term);
        J = alpha * Eigen::MatrixXd::Identity(y.size(), y.size()) - step_size * beta * function.BuildJacobian(t, y);
        delta_y = J.colPivHouseholderQr().solve(-f);
        y_new += delta_y;
    }
    return y_new;
}
