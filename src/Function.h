#ifndef FUNCTION_H
#define FUNCTION_H

#pragma once
#include <Eigen/Dense>
#include <cmath>
#include <string>
#include <vector>
#include <regex>

class Function
{
public:
    Function();
    Function(std::vector<std::vector<std::string>> function_combination, std::vector<std::vector<std::string>> derivative_combination);
    Function(std::vector<std::vector<std::string>> function_combination);
    ~Function();
    void SetFunctionCombination(std::vector<std::vector<std::string>> function_combination);
    void SetDerivativeCombination(std::vector<std::vector<std::string>> derivative_combination);
    double ApplyFunction(int function, double variable, double param);
    Eigen::VectorXd BuildRightHandSide(double t, Eigen::VectorXd y);
    Eigen::MatrixXd BuildJacobian(double t, Eigen::VectorXd y);

private:
    
    std::vector<std::vector<std::string>> function_combination;
    std::vector<std::vector<std::string>> derivative_combination;
    std::regex pattern;
    std::smatch match;
    double f1(double x, double param); //sin
    double f2(double x, double param); //cos
    double f3(double x, double param); //exp
    double f4(double x, double param); //power
    double f5(double x, double param); //log
    double f6(double x, double param); //identity 
    double f7(double x, double param); //constant
};


#endif