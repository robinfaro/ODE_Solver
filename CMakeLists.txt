cmake_minimum_required(VERSION 3.5.0)
project(ODE_Solver VERSION 0.1.0 LANGUAGES C CXX)

# Include Eigen directory
include_directories(eigen)

# Main application executable
add_executable(ODE_Solver
    src/main.cpp
    src/OdeSolver.cpp
    src/RungeKutta.cpp
    src/MultiStep.cpp
    src/AdamBashforth.cpp
    src/AdamMoulton.cpp
    src/BackwardEuler.cpp
    src/ForwardEuler.cpp
    src/BDF.cpp
    src/AdamBashforthOneStep.cpp
    src/AdamBashforthTwoSteps.cpp
    src/AdamBashforthThreeSteps.cpp
    src/AdamBashforthFourSteps.cpp
    src/NewtonMethod.cpp
    src/Function.cpp
    src/utils.cpp
)

# Enable testing
enable_testing()

# Add GoogleTest subdirectory
add_subdirectory(gtest)

# Define test sources
file(GLOB TEST_SOURCES test/*.cpp)

# Test executable
add_executable(ODE_Solver_Tests
    ${TEST_SOURCES}
    src/OdeSolver.cpp
    src/RungeKutta.cpp
    src/MultiStep.cpp
    src/AdamBashforth.cpp
    src/AdamMoulton.cpp
    src/BackwardEuler.cpp
    src/ForwardEuler.cpp
    src/BDF.cpp
    src/AdamBashforthOneStep.cpp
    src/AdamBashforthTwoSteps.cpp
    src/AdamBashforthThreeSteps.cpp
    src/AdamBashforthFourSteps.cpp
    src/NewtonMethod.cpp
    src/Function.cpp
    src/utils.cpp
)

# Include GoogleTest include directory for the test executable
target_include_directories(ODE_Solver_Tests PUBLIC gtest/include)

# Link GoogleTest libraries to the test executable
target_link_libraries(ODE_Solver_Tests gtest gtest_main pthread)

# Add tests to CTest
add_test(NAME ODE_Solver_Tests COMMAND ODE_Solver_Tests)
