#include <iostream>
#include <Eigen/Dense>
#include <vector>
#include <cmath>
#include <string>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include "utils.h"

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
void printVector(const Eigen::VectorXd& vec, const std::string& name) {
    std::cout.precision(4);
    std::cout << name << " (" << vec.size() << "): [ ";
    for (int i = 0; i < vec.size(); ++i) {
        std::cout << vec[i];
        if (i != vec.size() - 1) std::cout << ", ";
    }
    std::cout << " ]" << std::endl;
}

// Function to print Eigen matrices
void printMatrix(const Eigen::MatrixXd& mat, const std::string& name) {
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


InputParameters parseInputFile(const std::string& filename) {
    InputParameters params;
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + filename);
    }

    std::string line;
    std::istringstream iss;

    // Read number of equations
    std::getline(file, line);
    iss.str(line);
    iss >> params.num_equations;
    iss.clear();

    // Read functionMatrix
    for (int i = 0; i < (params.num_equations + 1); ++i) {
        std::getline(file, line);
        std::istringstream matrix_line(line);
        std::vector<std::string> row;
        std::string entry;
        while (matrix_line >> entry) {
            row.push_back(entry);
        }
        params.function_matrix.push_back(row);
    }

    std::getline(file, line);
    // Read derivativeMatrix (optional)
    if (line != "NA") 
    { 
        for (int i = 0; i < params.num_equations; ++i) {
            if (i != 0) {
                std::getline(file, line);
            }
            std::istringstream matrix_line(line);
            std::vector<std::string> row;
            std::string entry;
            while (matrix_line >> entry) {
                row.push_back(entry);
            }
            params.derivative_matrix.push_back(row);
        }
    }

    std::getline(file, line);
    iss.str(line);
    iss >> params.method;
    iss.clear();

    // Read initial time, final time, and step size
    std::getline(file, line);
    iss.str(line);
    iss >> params.initial_time >> params.final_time >> params.step_size;
    iss.clear();

    // Read number of steps
    std::getline(file, line);
    iss.str(line);
    iss >> params.num_steps;
    iss.clear();

    // Read initial condition matrix
    std::getline(file, line);
    if (line != "NA") 
    {
        // Temporary storage for all matrix entries in a single vector
        std::vector<double> flat_matrix;

        int num_rows = params.num_steps;
        int num_cols = params.num_equations;

        // Read the first row
        std::istringstream matrix_line(line);
        double value;
        int col_count = 0;
        while (matrix_line >> value) {
            flat_matrix.push_back(value);
            ++col_count;
        }
        std :: cout << "col_count: " << col_count << std::endl;
        std :: cout << "read : " << flat_matrix.size() << std::endl;
        if (col_count != num_cols) {
            throw std::runtime_error("Invalid number of columns in initial condition matrix");
        }

        // Read the remaining rows
        for (int i = 1; i < num_rows; ++i) {
            std::getline(file, line);
            std::istringstream matrix_line(line);
            while (matrix_line >> value) {
                flat_matrix.push_back(value);
            }
        }

        Eigen::MatrixXd initial_condition(num_rows, num_cols);
        for (int i = 0; i < num_rows; ++i) {
            for (int j = 0; j < num_cols; ++j) {
                std :: cout << flat_matrix[i*num_cols + j] << " ";
                initial_condition(i, j) = flat_matrix[i*num_cols + j];
            }
            std :: cout << std::endl;
        }

        params.initial_condition = initial_condition.transpose();
        
        // Use Eigen::Map to construct an Eigen::MatrixXd from the flat vector
        //params.initial_condition = Eigen::Map<Eigen::MatrixXd>(flat_matrix.data(), num_rows, num_cols);
    }

    std::getline(file, line);
    if (line != "NA") 
    {
        iss.str(line);
        iss >> params.num_stage;
        iss.clear();
    }

    std::getline(file, line);
    //std::cout << "line: " << (line=="NA") << std::endl;
    // Read A (optional)
    if (line != "NA") 
    {
        // Temporary storage for all matrix entries in a single vector
        std::vector<double> flat_matrix;

        int num_rows = params.num_stage;
        int num_cols = params.num_stage;

        // Read the first row
        std::istringstream matrix_line(line);
        double value;
        int col_count = 0;
        while (matrix_line >> value) {
            flat_matrix.push_back(value);
            ++col_count;
        }
        if (col_count != num_cols) {
            throw std::runtime_error("Invalid number of columns in matrixA");
        }

        // Read the remaining rows
        for (int i = 1; i < num_rows; ++i) {
            std::getline(file, line);
            std::istringstream matrix_line(line);
            while (matrix_line >> value) {
                flat_matrix.push_back(value);
            }
        }

        Eigen::MatrixXd a(num_rows, num_cols);
        for (int i = 0; i < num_rows; ++i) {
            for (int j = 0; j < num_cols; ++j) {
                a(i, j) = flat_matrix[i*num_cols + j];
            }
        }

        params.a = a;
    }


    // Read B vector (optional)
    std::getline(file, line);

    if (line != "NA") {
        std::istringstream vector_line(line);
        double value;
        std::vector<double> vector;
        while (vector_line >> value) {
            vector.push_back(value);
        }
        params.b = Eigen::Map<Eigen::VectorXd>(vector.data(), vector.size());
    }

    // Read C vector (optional)
    std::getline(file, line);

    if (line != "NA") {
        std::istringstream vector_line(line);
        double value;
        std::vector<double> vector;
        while (vector_line >> value) {
            vector.push_back(value);
        }
        params.c = Eigen::Map<Eigen::VectorXd>(vector.data(), vector.size());
    }

    // Read alpha vector (optional)

    std::getline(file, line);
    if (line != "NA") {
        std::istringstream vector_line(line);
        double value;
        std::vector<double> vector;
        while (vector_line >> value) {
            vector.push_back(value);
        }
        params.alpha = Eigen::Map<Eigen::VectorXd>(vector.data(), vector.size());
    }

    // Read beta vector (optional)

    std::getline(file, line);
    if (line != "NA") {
        std::istringstream vector_line(line);
        double value;
        std::vector<double> vector;
        while (vector_line >> value) {
            vector.push_back(value);
        }
        params.beta = Eigen::Map<Eigen::VectorXd>(vector.data(), vector.size());
    }

    file.close();
    return params;
}