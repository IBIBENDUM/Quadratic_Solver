#ifndef QUADRATKA_TEST_H
#define QUADRATKA_TEST_H

bool read_reference_values(struct test_values_data *test_values, FILE *file_ptr);

void test_all_equations(const char *filename);

int test_one_equation(int num_of_test, double a, double b, double c, double _Complex x1_ref, double _Complex x2_ref, int num_of_roots_ref);

void print_expected_values(_Complex double x1_ref, _Complex double x2_ref, int num_of_roots_ref);

void print_failed_values(int num_of_test, _Complex double x1, _Complex double x2, int num_of_roots);

#endif
