# CMake generated Testfile for 
# Source directory: /home/rfaro/anaconda3/programmingConcepts/project/ODE_Solver
# Build directory: /home/rfaro/anaconda3/programmingConcepts/project/ODE_Solver/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(ODE_Solver_Tests "/home/rfaro/anaconda3/programmingConcepts/project/ODE_Solver/build/ODE_Solver_Tests")
set_tests_properties(ODE_Solver_Tests PROPERTIES  _BACKTRACE_TRIPLES "/home/rfaro/anaconda3/programmingConcepts/project/ODE_Solver/CMakeLists.txt;63;add_test;/home/rfaro/anaconda3/programmingConcepts/project/ODE_Solver/CMakeLists.txt;0;")
subdirs("gtest")
