#include <iostream>
#include <Eigen/Dense>
#include <vector>
#include <cmath>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <cctype>
#include <stdexcept>
#include "utils.h"

double ParseFraction(const std::string& fraction) {
    size_t pos = fraction.find("/");
    if (pos == std::string::npos) {
        return std::stod(fraction);
    }
    double numerator = std::stod(fraction.substr(0, pos));
    double denominator = std::stod(fraction.substr(pos + 1));
    if (denominator == 0) {
        throw std::invalid_argument("Denominator cannot be zero: " + fraction);
    }
    return numerator / denominator;
}

bool IsLowerTriangular(const Eigen::MatrixXd& matrix) {
    if (matrix.rows() != matrix.cols()) {
        return false; // A triangular matrix must be square
    }
    for (int i = 0; i < matrix.rows(); ++i) {
        for (int j = i + 1; j < matrix.cols(); ++j) {
            if (matrix(i, j) != 0) {
                return false;
            }
        }
    }
    return true;
}

bool IsSquareMatrix(const std::vector<std::vector<std::string>>& matrix) {
    size_t numRows = matrix.size();
    if (numRows == 0) {
        return false; // Empty matrix is not square
    }

    for (const auto& row : matrix) {
        if (row.size() != numRows) {
            return false; // Number of columns in a row does not match the number of rows
        }
    }
    return true;
}

// Function to print Eigen vectors
void PrintVector(const Eigen::VectorXd& vec, const std::string& name) {
    std::cout.precision(4);
    std::cout << name << " (" << vec.size() << "): [ ";
    for (int i = 0; i < vec.size(); ++i) {
        std::cout << vec[i];
        if (i != vec.size() - 1) std::cout << ", ";
    }
    std::cout << " ]" << std::endl;
}

// Function to print Eigen matrices
void PrintMatrix(const Eigen::MatrixXd& mat, const std::string& name) {
    std::cout.precision(4);
    std::cout << name << " (" << mat.rows() << "x" << mat.cols() << "):" << std::endl;
    for (int i = 0; i < mat.rows(); ++i) {
        std::cout << "[ ";
        for (int j = 0; j < mat.cols(); ++j) {
            std::cout << mat(i, j);
            if (j != mat.cols() - 1) std::cout << ", ";
        }
        std::cout << " ]" << std::endl;
    }
}

InputParameters ParseInputFile(const std::string& filename) {
    InputParameters params;
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + filename);
    }

    std::string line;
    std::string current_key; // Tracks the current key
    std::map<std::string, std::vector<std::string>> data; // Map to store parsed lines for each key

    // Helper function to trim leading/trailing whitespace
    auto trim = [](const std::string& str) {
        size_t first = str.find_first_not_of(" \t");
        size_t last = str.find_last_not_of(" \t");
        return (first == std::string::npos || last == std::string::npos) ? "" : str.substr(first, last - first + 1);
    };

    // Read the file and parse into a map
    while (std::getline(file, line)) {
        line = trim(line);

        if (line.empty()) continue; // Skip empty lines

        if (std::isalpha(line[0])) {
            // New key starts with an alphabetic character
            size_t colonPos = line.find(":");
            if (colonPos == std::string::npos) {
                throw std::runtime_error("Invalid format: Missing colon in line: " + line);
            }
            current_key = trim(line.substr(0, colonPos));
            data[current_key].push_back(line.substr(colonPos + 1));
        } else if (!current_key.empty()) {
            // Continuation of the previous key
            data[current_key].push_back(trim(line));
        } else {
            throw std::runtime_error("Invalid format: Value without a key: " + line);
        }
    }

    file.close();

    // Process the parsed map into InputParameters
    if (data.count("Number of equations")) {
        params.num_equations = std::stoi(data["Number of equations"][0]);
    }

    if (data.count("Function combination")) {
        for (const auto& line : data["Function combination"]) {
            std::istringstream iss(line);
            std::vector<std::string> row;
            std::string entry;
            while (iss >> entry) {
                row.push_back(entry);
            }
            params.function_matrix.push_back(row);
        }
    }

    if (data.count("Derivative combination") && trim(data["Derivative combination"][0]) != "NA") {
        for (const auto& line : data["Derivative combination"]) {
            std::istringstream iss(line);
            std::vector<std::string> row;
            std::string entry;
            while (iss >> entry) {
                row.push_back(entry);
            }
            params.derivative_matrix.push_back(row);
        }
    }
    else {
        params.derivative_matrix = {{""}};
    }

    if (data.count("Method")) {
        params.method = std::stoi(data["Method"][0]);
    }

    if (data.count("Initial Time") && data.count("Final Time") && data.count("Step Size")) {
        params.initial_time = ParseFraction(data["Initial Time"][0]);
        params.final_time = ParseFraction(data["Final Time"][0]);
        params.step_size = ParseFraction(data["Step Size"][0]);
    }

    if (data.count("Number of Steps")) {
        params.num_steps = std::stoi(data["Number of Steps"][0]);
    }

    if (data.count("Initial Condition") && trim(data["Initial Condition"][0]) != "NA") {
        std::vector<double> flat_matrix;
        for (const auto& line : data["Initial Condition"]) {
            std::istringstream iss(line);
            double value;
            while (iss >> value) {
                flat_matrix.push_back(value);
            }
        }
        params.initial_condition = Eigen::Map<Eigen::MatrixXd>(flat_matrix.data(), params.num_equations, params.num_steps);
    }

    if (data.count("Number of Stages")) {
        params.num_stage = std::stoi(data["Number of Stages"][0]);
    }

    if (data.count("A") && trim(data["A"][0]) != "NA") {
        std::vector<double> flat_matrix;
        for (const auto& line : data["A"]) {
            std::istringstream iss(line);
            std::string value;
            while (iss >> value) {
                flat_matrix.push_back(ParseFraction(value));
            }
        }
        params.a = Eigen::Map<Eigen::MatrixXd>(flat_matrix.data(), params.num_stage, params.num_stage).transpose();
    }

    if (data.count("B") && trim(data["B"][0]) != "NA") {
        std::istringstream iss(data["B"][0]);
        std::vector<double> vector;
        std::string value;
        while (iss >> value) {
            vector.push_back(ParseFraction(value));
        }
        params.b = Eigen::Map<Eigen::VectorXd>(vector.data(), vector.size());
    }

    if (data.count("C") && trim(data["C"][0]) != "NA") {
        std::istringstream iss(data["C"][0]);
        std::vector<double> vector;
        std::string value;
        while (iss >> value) {
            vector.push_back(ParseFraction(value));
        }
        params.c = Eigen::Map<Eigen::VectorXd>(vector.data(), vector.size());
        PrintVector(params.c, "C");
    }

    if (data.count("Alpha") && trim(data["Alpha"][0]) != "NA") {
        std::cout << data["Alpha"][0] << std::endl;
        std::istringstream iss(data["Alpha"][0]);
        std::vector<double> vector;
        std::string value;
        while (iss >> value) {
            vector.push_back(ParseFraction(value));
        }
        params.alpha = Eigen::Map<Eigen::VectorXd>(vector.data(), vector.size());

    }

    if (data.count("Beta") && trim(data["Beta"][0]) != "NA") {
        std::istringstream iss(data["Beta"][0]);
        std::vector<double> vector;
        std::string value;
        while (iss >> value) {
            vector.push_back(ParseFraction(value));
        }
        params.beta = Eigen::Map<Eigen::VectorXd>(vector.data(), vector.size());
    }

    return params;
}
