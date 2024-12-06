#include "BDF.h"
#include "MultiStep.h"
#include "NewtonMethod.h"
#include <iostream>

BDF::BDF()
{

}

BDF::BDF(double step_size, double initial_time, double final_time, Eigen::MatrixXd initial_condition, Function function, Eigen::VectorXd alpha) : MultiStep(step_size, initial_time, final_time, initial_condition, function, alpha, ALPHA)
{
    SetBeta();
}

BDF::~BDF()
{

}

void BDF::SetBeta()
{
    beta = Eigen::VectorXd::Zero(alpha.size());

}

Eigen::MatrixXd BDF::Solve()
{
    auto y0 = initial_condition;
    Eigen::MatrixXd approximations = Eigen::MatrixXd::Zero(y0.col(0).size(), (int)((final_time - initial_time) / step_size) + 1);
    for(int i = 0; i < (alpha.size() - 1); i++)
    {
        approximations.col(i) = initial_condition.col(i);
    }
    int current_col = alpha.size() - 1;

    for (double t = initial_time + (current_col * step_size); t < final_time; t += step_size)
    {
        Eigen::VectorXd sum = Eigen::VectorXd::Zero(y0.col(0).size());
        for(int i = 0; i < (alpha.size() - 1); i++)
        {
            sum = sum + alpha(i+1) * approximations.col(current_col - i - 1);
        }
        
        NewtonMethod newton_solver(function, sum, t, alpha(0), step_size);
        auto y1 = newton_solver.Solve();

        approximations.col(current_col) = y1;
        //y0 = y1;
        current_col++;
    }

    return approximations;

}   


