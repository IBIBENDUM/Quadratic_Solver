#ifndef QUAD_SOLVER_H
#define QUAD_SOLVER_H

/// Calculate discriminant
///
/// Formula: *D = b*b-4*a*c*
/// @param a, b, c Coefficients of the square equation
/// @return Return discriminant value
double calculate_discriminant(const double a, const double b, const double c);

/// Calculate roots of the square equation
///
/// @param a, b, c Coefficients of quadratic equation (*ax^2 + bx + c = 0*)
/// @param x1, x2 Roots of quadratic equation (*x - x1*)(*x - x2*) = *0*
/// @param NumberOfRoots Number of quadratic equation roots
/// @return Return false if coefficients are incorrect
/// @attention If equation is linear, x1 gets root value, x2 doesn't change
/// @warning If a, b, c are infinite or NaN it will display error
/// @see solve_linear_equation()
bool solve_quadratic_equation(const double a, const double b, const double c, double _Complex *x1, double _Complex *x2, int *NumberOfRoots);

/// Calculate root of linear equation
///
/// Solve an equation of form *ax + b = 0*@n
/// *x = -b / a*
/// @param b, c Coefficients of linear equation
/// @param x1 Root of linear equation
/// @see solve_quadratic_equation()
void solve_linear_equation(const double b, const double c, double _Complex *x1);

/// Display roots on the display
///
/// If the equation have only one root it will display only one root@n
/// If roots are complex it will display like complex value
/// ### Output examples
/// ~~~~~~~~~~~~~~~~~~~~~~~~.cpp
/// X принадлежит R // Output when X is any number
/// Нет корней // Output when equation have no roots
/// x = 3.00 // Output when equation have 1 root
/// x1 = 3.00, x2 = 4.00 // Output when equation have 2 real roots
/// x1 = -1.00+1.41i, x2 = -1.00-1.41i // Output when equation have 2 complex roots
/// ~~~~~~~~~~~~~~~~~~~~~~~~
///@param x1, x2 Roots of equation
///@param NumberOfRoots Number of roots
void print_roots(const double _Complex x1, const double _Complex x2, const int NumberOfRoots);

#endif
