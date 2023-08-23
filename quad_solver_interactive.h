#ifndef QUAD_SOLVER_INTERACTIVE_H
#define QUAD_SOLVER_INTERACTIVE_H

/// Ask user does he want to continue
/// ### Output example
/// ~~~~~~~~~~~~~~~~~~~~~~~~.cpp
/// Желаете продолжить? (Y для продолжения, что-то другое для выхода)
/// ~~~~~~~~~~~~~~~~~~~~~~~~
///@return Return true if 'Y', false if else
bool ask_for_continue();

/// Ask user for coefficients value
///
/// @param a_ptr, b_ptr, c_ptr Pointers of coefficients
/// @return Function return true if input correct, false if incorrect
/// @see read_coefs()
bool ask_coefs(double *a, double *b, double *c);

/// Skip characters until end of line
void skip_line();

/// Read coefficient from standart input
/// ### Input examples
/// ~~~~~~~~~~~~~~~~~~~~~~~~.cpp
/// 1 2 3 // correct
/// 1
/// 2
/// 3 // correct
/// 1, 2, 3 // incorrect
/// ~~~~~~~~~~~~~~~~~~~~~~~~
/// @param a_ptr,b_ptr,c_ptr Pointers on coefficients
/// @return Return number of correct read coefficients
/// @see ask_coeffs()
int read_coefs(double *a_ptr, double *b_ptr, double *c_ptr);
#endif
