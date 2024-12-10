#include "AdamBashforth.h"

AdamBashforth::AdamBashforth()
{

}

AdamBashforth::~AdamBashforth()
{

}

AdamBashforth::AdamBashforth(double step_size, double initial_time, double final_time, Eigen::MatrixXd initial_condition, Function function, Eigen::VectorXd beta) : MultiStep(step_size, initial_time, final_time, initial_condition, function, beta, BETA)
{
    SetAlpha();
}

AdamBashforth::AdamBashforth(double step_size, double initial_time, double final_time, Eigen::MatrixXd initial_condition, Function function) : MultiStep(step_size, initial_time, final_time, initial_condition, function)
{
    SetAlpha();
}

void AdamBashforth::SetAlpha()
{
    this->alpha = Eigen::VectorXd::Zero(this->beta.size());
}

Eigen::MatrixXd AdamBashforth::Solve()
{
    auto y0 = initial_condition;
    Eigen::MatrixXd approximations = Eigen::MatrixXd::Zero(y0.col(0).size(), (int)((final_time - initial_time) / step_size) + 1);
    int n_max = approximations.cols();
    for(int i = 0; i < beta.size(); i++)
    {
        approximations.col(i) = initial_condition.col(i);
    }
    int current_col = beta.size();


    for (int n = current_col; n < n_max; n++)
    {
        double t = initial_time + (n * step_size);
        Eigen::VectorXd sum = Eigen::VectorXd::Zero(y0.col(0).size());
        for(int i = 0; i < beta.size(); i++)
        {
            auto rhs = function.BuildRightHandSide(t - ((i + 1) * step_size), approximations.col(current_col - i - 1));
            sum = sum + beta(i) * function.BuildRightHandSide(t - ((i + 1) * step_size),  approximations.col(current_col - i - 1));
        }

        auto y1 = approximations.col(current_col - 1) + step_size * sum;
        approximations.col(current_col) = y1;
        current_col++;
    }

    return approximations;
}