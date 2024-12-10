#include "Function.h"
#include "utils.h"
#include <cmath>
#include <string>
#include <regex>
#include <iostream>


Function::Function()
{
    //this->pattern = std::regex("([-+]?[0-9]+)_([1-7])_\\(?([-]?[0-9]+)\\)?");
    this->pattern = std::regex("([-+]?[0-9]*\\.?[0-9]+)_([1-7])_\\(?([-+]?[0-9]*\\.?[0-9]+)\\)?");
    this->match = std::smatch();
}

Function::Function(std::vector<std::vector<std::string>> function_combination, std::vector<std::vector<std::string>> derivative_combination)
{
    if (!IsSquareMatrix(derivative_combination))
        throw std::invalid_argument("Derivative combination must be square matrix");
    this->function_combination = function_combination;
    this->derivative_combination = derivative_combination;
    //this->pattern = std::regex("([-+]?[0-9]+)_([1-7])_\\(?([-]?[0-9]+)\\)?");
    this->pattern = std::regex("([-+]?[0-9]*\\.?[0-9]+)_([1-7])_\\(?([-+]?[0-9]*\\.?[0-9]+)\\)?");
    this->match = std::smatch();
}

Function::Function(std::vector<std::vector<std::string>> function_combination)
{
    this->function_combination = function_combination;
    //this->pattern = std::regex("([-+]?[0-9]+)_([1-7])_\\(?([-]?[0-9]+)\\)?");
    this->pattern = std::regex("([-+]?[0-9]*\\.?[0-9]+)_([1-7])_\\(?([-+]?[0-9]*\\.?[0-9]+)\\)?");
    this->match = std::smatch();
}

Function::~Function()
{

}

void Function::SetFunctionCombination(std::vector<std::vector<std::string>> function_combination)
{
    this->function_combination = function_combination;
}

void Function::SetDerivativeCombination(std::vector<std::vector<std::string>> derivative_combination)
{
    this->derivative_combination = derivative_combination;
}

double Function::f1(double x, double param)
{
    return sin(param * x);
}

double Function::f2(double x, double param)
{
    return cos(param * x);
}

double Function::f3(double x, double param)
{
    return exp(param * x);
}

double Function::f4(double x, double param)
{
    return pow(x, param);
}

double Function::f5(double x, double param)
{
    return log(param * x);
}

double Function::f6(double x, double param)
{
    return param * x;
}

double Function::f7(double x, double param)
{
    return param;
}

double Function::ApplyFunction(int function, double variable, double param)
{
    switch (function)
    {
        case 1: return f1(variable, param);
        case 2: return f2(variable, param);
        case 3: return f3(variable, param);
        case 4: return f4(variable, param);
        case 5: return f5(variable, param);
        case 6: return f6(variable, param);
        case 7: return f7(variable, param);
        default: throw std::invalid_argument("Invalid function: " + std::to_string(function));
    }
}

Eigen::VectorXd Function::BuildRightHandSide(double t, Eigen::VectorXd y)
{
    Eigen::VectorXd rhs(y.size());
    for (int i = 0; i < y.size(); i++)
    {
        rhs(i) = 0;

        for (int j = 0; j < function_combination[i].size(); j++)
        {
            auto entry = function_combination[i][j];
            
            if (entry == "0") 
                continue;

            if (!std::regex_match(entry, match, pattern))
                throw std::invalid_argument("Invalid input: " + entry);

            double multiplier  = std::stod(match[1]);
            int function = std::stoi(match[2]);
            double param = std::stod(match[3]);

            double variable = (j == 0) ? t : y(j-1);
            rhs(i) += multiplier * ApplyFunction(function, variable, param);
        }
    }
    return rhs;
}

Eigen::MatrixXd Function::BuildJacobian(double t, Eigen::VectorXd y)
{
    Eigen::MatrixXd jacobian(y.size(), y.size());

    for (int i = 0; i < y.size(); i++)
    {
        for (int j = 0; j < y.size(); j++)
        {
            auto entry = derivative_combination[i][j];  
            
            if (entry == "0")
                continue; 

            if (!std::regex_match(entry, match, pattern))
                throw std::invalid_argument("Invalid input: " + entry);

            int multiplier  = std::stoi(match[1]);
            int function = std::stoi(match[2]);
            double param = std::stod(match[3]);

            jacobian(i, j) = multiplier * ApplyFunction(function, y(j), param);

        }
    }

    return jacobian;
}






