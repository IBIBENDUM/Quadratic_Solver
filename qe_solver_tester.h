#ifndef QE_SOLVER_TESTER_H
#define QE_SOLVER_TESTER_H

const int MAX_LINE_LEN = 256;

struct test_values_data {
    double a;
    double b;
    double c;
    double _Complex x1_ref;
    double _Complex x2_ref;
    int num_of_roots_ref;
};

enum value_id { a, b, c, x1_real, x1_imag, x2_real, x2_imag };


/// Read values for test from file
///
/// @param *test_values Values for test
/// @param *file_ptr File pointer
bool read_reference_values(struct test_values_data *test_values_ptr, FILE *file_ptr);

/// Test quad_solver by file with values
/// @param *filename Filename
/// @attention Print count of succeeded and failed tests
/// @see test_one_equation()
void test_all_equations(const char *filename);

/// @param num_of_test Number of test
/// Test quad_solver by input values
/// @param a, b, c Coefficients of quadratic equation
/// @param x1_ref, x2_ref Reference roots of quadratic equation
/// @param num_of_roots Number of roots of quadratic equation
bool test_one_equation(const int num_of_test, struct test_values_data *tv_ptr);

/// Print expected values
/// ### Example output
/// ~~~~~~~~~~~~~~~~~~~.cpp
/// EXPECTED: x1 = 0.50-0.87i, x2 = 0.50+0.87i, num_of_roots_ref = 2
/// ~~~~~~~~~~~~~~~~~~~
/// @param x1_ref, x2_ref Reference roots of quadratic equation
/// @param num_of_roots_ref Reference number of roots
void print_expected_values(const _Complex double x1_ref, const _Complex double x2_ref, const int num_of_roots_ref);

/// Print expected values
/// ### Example output
/// ~~~~~~~~~~~~~~~~~~~.cpp
/// TEST �%d FAILED: x1 = NaN, num_of_roots = 1
/// TEST �%d FAILED: x1 = 0.50-0.87i, x2 = 0.50+0.87i, num_of_roots = 2
/// ~~~~~~~~~~~~~~~~~~~
/// @param x1_ref, x2_ref Reference roots of quadratic equation
/// @param num_of_roots_ref Reference number of roots
void print_failed_values(const int num_of_test, const _Complex double x1, const _Complex double x2, const int num_of_roots);

#endif
