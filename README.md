# ODE Solver

## Optimized Render of the Equations

This file contains equations that are designed to be displayed on the main page of the Doxygen documentation, accessible through the `index.html` file in the documentation folder. To ensure proper rendering, the equations are formatted using LaTeX syntax. Make sure that the documentation environment supports MathJax or a similar LaTeX rendering tool for the best visual presentation.


## Setup Instructions

Follow these steps to set up and run the project:

### 1. Clone the Repository
Clone the repository to your local machine and open a terminal inside the cloned directory:
```bash
git clone https://github.com/robinfaro/ODE_Solver.git
cd ODE_Solver
```

### 2. Populate Submodules
Initialize the required submodules (`eigen` and `gtest`) using the following commands:
```bash
git submodule update --init eigen
git submodule update --init gtest
```

### 3. Set Up CMake Compilation
Create a `build` directory, configure the build system with CMake and compile the project:
```bash
mkdir build
cd build
cmake ..
cmake --build .
```

### 4. Run Tests
To verify the setup, run the tests:
```bash
./ODE_Solver_Tests
```

### 5. Run the Program
You can run the program by passing an input file as a parameter. For example:
```bash
./ODE_Solver <input_file>
```
This will allow you to solve a system of differential equations with your desired methods and parameters. It will print the numerical approximation of the solution at each time step.

---

### Example System
We provide 10 methods to solve Vectorial ODEs, assuming the system is in the form:
\f[
\frac{dy_1}{dt} = f_1(y_1, ..., y_n, t)\\
\vdots\\
\frac{dy_n}{dt} = f_n(y_1, ..., y_n, t)
\f]

Each \f$f_i(y_1, ..., y_n, t)\f$ is a combination of basic mathematical functions f. For example:
\f[
f_i(y_1, ..., y_n, t) = m_t \text{f}_t(t) + m_j \text{f}_j(y_1) +  \ldots + m_k\text{f}_k(y_n)
\f]

---

### Available Basic Functions
The following basic mathematical functions can be used to construct the system:

1. **Sine function:**
   \f[ \text{f1}(x, \text{param}) = \sin(\text{param} \cdot x) \f]

2. **Cosine function:**
   \f[ \text{f2}(x, \text{param}) = \cos(\text{param} \cdot x) \f]

3. **Exponential function:**
   \f[ \text{f3}(x, \text{param}) = e^{\text{param} \cdot x} \f]

4. **Power function:**
   \f[ \text{f4}(x, \text{param}) = x^{\text{param}} \f]

5. **Logarithmic function:**
   \f[ \text{f5}(x, \text{param}) = \log(\text{param} \cdot x) \f]

6. **Identity function:**
   \f[ \text{f6}(x, \text{param}) = \text{param} \cdot x \f]

7. **Constant function:**
   \f[ \text{f7}(x, \text{param}) = \text{param} \f]

Each function is combined within the system equations using a multiplier and parameter, following the format specified in the input file.

---

### Available Methods
The available numerical methods and their corresponding method numbers are as follows:

1. **Forward Euler (ForwardEuler):** No additional parameters needed.
2. **Adam-Bashforth One-Step (AdamBashforthOneStep):** No additional parameters needed.
3. **Adam-Bashforth Two-Steps (AdamBashforthTwoSteps):** No additional parameters needed.
4. **Adam-Bashforth Three-Steps (AdamBashforthThreeSteps):** No additional parameters needed.
5. **Adam-Bashforth Four-Steps (AdamBashforthFourSteps):** No additional parameters needed.
6. **Backward Euler (BackwardEuler):** Requires the Jacobian of the system to be provided.
7. **Runge-Kutta Explicit (RungeKutta):** Requires matrix A, vector b, and vector c. Matrix A must be lower triangular.
8. **Backward Differentiation Formula (BDF):** Requires the Jacobian of the system and vector alpha.
9. **Adam-Moulton (AdamMoulton):** Requires the Jacobian of the system and vector beta.
10. **Adam-Bashforth (AdamBashforth):** Requires vector beta.

---

### Input File Format
The input file must be a **txt** structured as follows:

```
Number of equations: 
Function combination: 
Derivative combination: NA
Method: 
Initial Time: 
Final Time: 
Step Size: 
Number of Steps: 
Initial Condition: 
Number of Stages: 
A: NA
B: NA
C: NA
Alpha: NA
Beta: NA
```

This format ensures all keys are present, even if no values are provided. If a value is not provided, use `NA` to signify it is not applicable.

#### Explanation of Entries:
- \f$\textbf{Number of equations}\f$: Number of ODEs in the system.
- \f$\textbf{Function combination}\f$: Defines the function matrix for \f$f(t, y_1, ..., y_n)\f$. Each row corresponds to one equation in the system, each entry in a row defines the contribution of a specific variable (\f$y_i\f$) or the time variable (\f$t\f$) in that equation. Entries follow the format `multiplier_functionNumber_parameter` or `0` if the corresponding variable (\f$t\f$ or \f$y_i\f$) does not contribute to that row. The value of functionNumber has to follow the list of available mathematical functions above. Multiplier and parameter are two signed floating point values.
- \f$\textbf{Derivative combination}\f$: Defines the Jacobian matrix (if needed). Each row corresponds to one equation in the system and entries follow the same format as the function combination.
- \f$\textbf{Method}\f$: Specifies the numerical method to use (see the method list above).
- \f$\textbf{Initial Time}\f$: The starting time for the simulation.
- \f$\textbf{Final Time}\f$ The ending time for the simulation.
- \f$\textbf{Step Size}\f$: The time step for the simulation.
- \f$\textbf{Number of Steps}\f$ Number of steps of the method.
- \f$\textbf{Initial Condition}\f$: Each row represents the values of \f$y_1, ..., y_n\f$ at a given time step. For example, if there are three initial conditions provided, the user will pass three rows, each containing the values for all variables in the system.
- \f$\textbf{Number of Stages, A, B, C, Alpha and Beta}\f$: Parameters for specific methods (e.g. RK and AM). For the Runge-Kutta method, the matrix A is provided by rows and the vectors B and C are listed as single-line entries. The A matrix must be lower triangular for explicit methods.

#### Note on Parsing:
- Each input parameter begins with a **key** (e.g., `Number of equations:`, `Derivative combination:`).
- The system will continue parsing subsequent lines as part of the current parameter until another key is encountered.
- This format allows multi-line entries for parameters such as `Function/Derivative combination`, `Initial Condition`, and matrix `A`.
- Input matrices and vectors can contain numerical values in either decimal floating-point format or fractional representation.

---

### Notes on Function Matrix
The first entry of each row in the function matrix refers to the time variable (\f$t\f$). Ensure that \f$t\f$ is appropriately included as the first parameter in all equations.

---

### Example Input File
Here is an example input file for the system:
\f[
\frac{dy_1}{dt} = t + y_2\\

\frac{dy_2}{dt} = \sin(t) - y_1
\f]

```
Number of equations: 2
Function combination: +1_6_1 0 1_6_1
1_1_1 -1_6_1 0
Derivative combination: 0 1_7_1
-1_7_1 0
Method: 1
Initial Time: 0.0
Final Time: 1.0
Step Size: 0.1
Number of Steps: 3
Initial Condition: 1 0
1 -0.1
1 -0.19
Number of Stages: 1
A: NA
B: NA
C: NA
Alpha: NA
Beta: NA
```

## Tests
As said above we provide several tests for our methods, in particular we test all the implemented methods both with a scalar and a vectorial ODE, by comparing each method's output with the approximations of a third-party solver with a tolerance of \f$10^{-4}\f$.

### Note on methods with no specific implemenation
For the methods with no specified version to implement, we tested the following ones:
- RK4 for Runge Kutta family.
- AM3 for Adam Moulton family.
- BDF1 for Backward Differentiation Formula family.

### 1. Scalar Test
We consider the ODE:
\f[
\frac{dy}{dt} = e^{-t} + cos(y)\\
\f]
where we set:
- Initial Time: 0.0
- Final Time: 2.0
- Step Size: 0.1
#### Initial Conditions
- For 1 step method we use \f$y(0) = 0.0\f$ as inital condition.
- For 2 step methods we use \f$y(0) = 0.0, y(0.1) = 0.2\f$ as initial condition.
- For 3 step methods we use \f$y(0) = 0.0, y(0.1) = 0.2, y(0.2)=0.3884\f$ as initial condition.
- For 4 step methods we use \f$y(0) = 0.0, y(0.1) = 0.2, y(0.2)=0.3884, y(0.3)=0.5629\f$ as initial condition.

### 2. Vectorial Test
We consider the ODE:
\f[
\frac{dy_1}{dt} = t + y_2\\
\frac{dy_2}{dt} = \sin(t) - y_1
\f]
where we set:
- Initial Time: 0.0
- Final Time: 1.0
- Step Size: 0.1
#### Initial Conditions
-  For 1 step method we set \f$\vec{y}(0) \f$ = \f$\begin{bmatrix}  y_1\\ y_2 \\  \end{bmatrix} \f$ = \f$\begin{bmatrix}  1.0\\ 0.0 \\  \end{bmatrix} \f$


-  For 2 step method we set \f$\vec{y}(0) \f$ = \f$\begin{bmatrix}  y_1\\ y_2 \\  \end{bmatrix} \f$ = \f$\begin{bmatrix}  1.0\\ 0.0 \\  \end{bmatrix}  \f$ and 
\f$\vec{y}(0.1) \f$ = \f$\begin{bmatrix}  y_1\\ y_2 \\  \end{bmatrix} \f$ = \f$\begin{bmatrix}  1.0\\ -0.1 \\  \end{bmatrix}  \f$


-  For 3 step method we set \f$\vec{y}(0) \f$ = \f$\begin{bmatrix}  y_1\\ y_2 \\  \end{bmatrix} \f$ = \f$\begin{bmatrix}  1.0\\ 0.0 \\  \end{bmatrix}  \f$ and 
\f$\vec{y}(0.1) \f$ = \f$\begin{bmatrix}  y_1\\ y_2 \\  \end{bmatrix} \f$ = \f$\begin{bmatrix}  1.0\\ -0.1 \\  \end{bmatrix}  \f$ and 
 \f$\vec{y}(0.2) \f$ = \f$\begin{bmatrix}  y_1\\ y_2 \\  \end{bmatrix} \f$ = \f$\begin{bmatrix}  1.0\\ -0.19 \\  \end{bmatrix}  \f$


-  For 4 step method we set \f$\vec{y}(0) \f$ = \f$\begin{bmatrix}  y_1\\ y_2 \\  \end{bmatrix} \f$ = \f$\begin{bmatrix}  1.0\\ 0.0 \\  \end{bmatrix}  \f$ and 
\f$\vec{y}(0.1) \f$ = \f$\begin{bmatrix}  y_1\\ y_2 \\  \end{bmatrix} \f$ = \f$\begin{bmatrix}  1.0\\ -0.1 \\  \end{bmatrix}  \f$ and 
 \f$\vec{y}(0.2) \f$ = \f$\begin{bmatrix}  y_1\\ y_2 \\  \end{bmatrix} \f$ = \f$\begin{bmatrix}  1.0\\ -0.19 \\  \end{bmatrix}  \f$ and 
 \f$\vec{y}(0.3) \f$ = \f$\begin{bmatrix}  y_1\\ y_2 \\  \end{bmatrix} \f$ = \f$\begin{bmatrix}  1.0\\ -0.27 \\  \end{bmatrix}  \f$

### Modify Test Systems Parameters

To customize the parameters of the test systems, you can use the input files provided in the `input_examples` folder. This folder contains example configurations for both scalar and vector ODE systems. You can edit these files to change parameters or specify different numerical methods.

#### Example Input Files:
1. **`input_file_vector_ODE.txt`**  
   - This file is pre-configured with parameters for the **Adam-Moulton 3-step (AM3)** method.  
   - Modify this file to adjust the vector ODE system or to experiment with other methods.

2. **`input_file_scalar_ODE.txt`**  
   - This file is pre-configured with parameters for the **Adam-Bashforth 2-step (AB2)** method.  
   - Use this file to tweak the scalar ODE system or test additional configurations.

Simply open the relevant input file, edit the parameters as needed, and pass the file to the program as an argument:
```bash
./ODE_Solver <input_file>
```

#### Empty Skeleton for New Configurations:
We also provide an empty skeleton file, **`empty_input_file.txt`**, where you can define your own parameters for a completely custom setup.


## Coding Convention

We follow the **Google C++ Style Guide** coding convenction for our project. You can find the full guidelines [here](https://google.github.io/styleguide/cppguide.html).

### Key Conventions Used:
1. **Variable naming:**
   - Variables are written in lowercase, with words separated by underscores.
   - Example: `variable_name`, `matrix_size`.

2. **Class and function naming:**
   - Classes and functions start with an uppercase letter, with subsequent words also capitalized (CamelCase).
   - Example: `ClassName`, `FunctionName`.

3. **Consistency with Google Style Guide:**
   - The overall structure, indentation, and formatting of the code align with the Google Style Guide recommendations.

## TODOs and future works

1. **Extend RK methods:** Add support for implicit Runge-Kutta methods.
2. **Advanced function combinations:** Allow more advanced functions, complex combinations, function of functions and the multiplication between different variables. 
3. **Parsing fraction as multiplier and parameters for the input function:** Enable the interpretation of fractions as multipliers and as parameters for input functions.
4. **Plotting for scalar equations:** Provide functions to visualize scalar solutions.
5. **Stability checks:** Implement stability checks for explicit methods to prevent non-converging approximations.





<!-- Runge Kutta Method:

$ y_{n+1} = y_n + h \sum_{i=1}^{s} b_i k_i $

$ k_i = f\left(t_n + c_i h, y_n + h \sum_{j=1}^{i-1} a_{ij} k_j\right), \quad i = 1, \dots, s $

\f[
\begin{array}{c|cccc}
c_1 & 0      & 0      & 0      & \cdots \\
c_2 & a_{21} & 0      & 0      & \cdots \\
c_3 & a_{31} & a_{32} & 0      & \cdots \\
\vdots & \vdots & \vdots & \vdots & \ddots \\
c_s & a_{s1} & a_{s2} & a_{s3} & \cdots \\
\hline
    & b_1    & b_2    & b_3    & \cdots & b_s
\end{array}
\f]

Forward Euler Method: 

$ y_{n+1} = y_n + h f\left(t_n , y_n \right) $

Note: stability of explicit methods 

Adam-Bashforth: 

$ y_{n+1} = \alpha_0 y_n + h \sum_{i=0}^{k-1} \beta_i f(t_{n-i}, y_{n-i})$

Adam-Bashforth 1:

$ y_{n+1} = y_n + h f(t_n, y_n) $

Adam-Bashforth 2:

$y_{n+1} = y_n + h \left( \frac{3}{2} f(t_n, y_n) - \frac{1}{2} f(t_{n-1}, y_{n-1}) \right)$

Adam-Bashforth 3:

$ y_{n+1} = y_n + h \left( \frac{23}{12} f(t_n, y_n) - \frac{16}{12} f(t_{n-1}, y_{n-1}) + \frac{5}{12} f(t_{n-2}, y_{n-2}) \right) $

Adam-Bashforth 4:

$ y_{n+1} = y_n + h \left( \frac{55}{24} f(t_n, y_n) - \frac{59}{24} f(t_{n-1}, y_{n-1}) + \frac{37}{24} f(t_{n-2}, y_{n-2}) - \frac{9}{24} f(t_{n-3}, y_{n-3}) \right)$

Adam-Moulton: 

$y_{n+1} = \alpha_0 y_n + h \left( \beta_0 f(t_{n+1}, y_{n+1}) + \sum_{i=1}^{k} \beta_i f(t_{n+1-i}, y_{n+1-i}) \right)$

Backward Euler:

$y_{n+1} = y_n + h f(t_{n+1}, y_{n+1})$

BDF:

$\sum_{i=0}^{k} \alpha_i y_{n-i} = h f(t_{n}, y_{n})$ -->




