#include "RungeKutta.h"

RungeKutta::RungeKutta()
{

}

RungeKutta::RungeKutta(double step_size, double initial_time, double final_time, Eigen::MatrixXd initial_condition, Function function, Eigen::MatrixXd a, Eigen::VectorXd b, Eigen::VectorXd c) : OdeSolver(step_size, initial_time, final_time, initial_condition, function) 
{
    this->a = a;
    this->b = b;
    this->c = c;
}

RungeKutta::RungeKutta(double step_size, double initial_time, double final_time, Eigen::MatrixXd initial_condition, Function function) : OdeSolver(step_size, initial_time, final_time, initial_condition, function)
{

}

RungeKutta::~RungeKutta()
{

}

void RungeKutta::SetA(Eigen::MatrixXd a)
{
    this->a = a;
}

void RungeKutta::SetB(Eigen::VectorXd b)
{
    this->b = b;
}

void RungeKutta::SetC(Eigen::VectorXd c)
{
    this->c = c;
}

Eigen::MatrixXd RungeKutta::Solve()
{
    //solve the Runge-Kutta method
    
    auto y0 = initial_condition;
    Eigen::MatrixXd approximations = Eigen::MatrixXd::Zero(y0.size(), (int)((final_time - initial_time) / step_size) + 1);
    int current_col= 0;    
    approximations.col(current_col) = y0;
    current_col++;

    for (double t = initial_time; t < (final_time - step_size); t += step_size)
    {
        int s = b.size();
        Eigen::MatrixXd k = Eigen::MatrixXd::Zero(y0.size(), s);

        for (int i = 0; i < s; i++)
        {
            double time_step = t + c(i) * step_size;
            Eigen::VectorXd y_step = y0;
            //std::cout << "y_step: " << y_step.size() << std::endl << std::flush;
            for (int j = 0; j < i; j++)
            {
                y_step = y_step + (step_size * a(i, j) * k.col(j));
            }
            //std::cout << "y_step: " << y_step << std::endl << std::flush;
            //std::cout << "time_step: " << time_step << std::endl << std::flush;
            auto new_rhs = function.BuildRightHandSide(time_step, y_step);
            //std::cout << "new_rhs: " << new_rhs << std::endl << std::flush;
            k.col(i) = new_rhs;
            //k.row(i) = function.BuildRightHandSide(time_step, y_step);
        }

        auto y1 = y0 + step_size * k * b;
        approximations.col(current_col) = y1;
        y0 = y1;
        current_col++;

    }
    

    return approximations;
}




