#ifndef QE_SOLVER_INTERACTIVE_H
#define QE_SOLVER_INTERACTIVE_H

/// Ask user if he want to continue
/// ### Output example
/// ~~~~~~~~~~~~~~~~~~~~~~~~.cpp
/// Do you want to continue? (Y for continue, something else for exit)
/// ~~~~~~~~~~~~~~~~~~~~~~~~
///@return Return true if 'Y', false otherwise
bool ask_if_continue();

/// Ask user for coefficients value
///
/// @param a_ptr, b_ptr, c_ptr Pointers of coefficients
/// @return Function return true if input correct, false if incorrect
/// @see read_coefs()
bool ask_coefs(double *a_ptr, double *b_ptr, double *c_ptr);

/// Read coefficient from standard input
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
