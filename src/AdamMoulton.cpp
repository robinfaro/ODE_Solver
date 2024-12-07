#include "AdamMoulton.h"
#include "NewtonMethod.h"
#include <typeinfo>

AdamMoulton::AdamMoulton()
{

}

AdamMoulton::AdamMoulton(double step_size, double initial_time, double final_time, Eigen::MatrixXd initial_condition, Function function, Eigen::VectorXd beta) : MultiStep(step_size, initial_time, final_time, initial_condition, function, beta, BETA)
{
    SetAlpha();
}

AdamMoulton::AdamMoulton(double step_size, double initial_time, double final_time, Eigen::MatrixXd initial_condition, Function function) : MultiStep(step_size, initial_time, final_time, initial_condition, function)
{
    SetAlpha();
}

AdamMoulton::~AdamMoulton()
{

}

void AdamMoulton::SetAlpha()
{
    this->alpha = Eigen::VectorXd::Zero(this->beta.size());
}

Eigen::MatrixXd AdamMoulton::Solve()
{
    auto y0 = initial_condition;
    Eigen::MatrixXd approximations = Eigen::MatrixXd::Zero(y0.col(0).size(), (int)((final_time - initial_time) / step_size) + 1);
    int n_max = approximations.cols();
    for(int i = 0; i < (beta.size() - 1); i++)
    {
        approximations.col(i) = initial_condition.col(i);
    }
    int current_col = beta.size() - 1;

    //for (double t =  initial_time + (current_col * step_size); t < final_time; t += step_size)
    for (int n = current_col; n < n_max; n++)
    {
        double t = initial_time + (n * step_size);
        Eigen::VectorXd sum = Eigen::VectorXd::Zero(y0.col(0).size());
        for(int i = 0; i < (beta.size() - 1); i++)
        {
            sum = sum + beta(i + 1) * function.BuildRightHandSide(t - ((i + 1) * step_size),  approximations.col(current_col - i - 1));
        }
        NewtonMethod newton_solver(function, approximations.col(current_col - 1), t, beta(0), sum, step_size);
        auto y1 = newton_solver.Solve();
        // destroy newton_solver
        //newton_solver.~NewtonMethod();

        approximations.col(current_col) = y1;
        current_col++;
    }

    return approximations;
}