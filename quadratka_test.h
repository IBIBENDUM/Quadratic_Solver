#ifndef QUADRATKA_TEST_H
#define QUADRATKA_TEST_H

static int compare_complex_doubles(double _Complex a, double _Complex b);

static void swap_complex(double _Complex *a, double _Complex *b);

int count_lines(FILE *file_ptr);

bool read_reference_values(struct test_values_data *test_values, FILE *file_ptr);

void test_all_equations(const char *filename);

int test_one_equation(int num_of_test, double a, double b, double c, double _Complex x1_ref, double _Complex x2_ref, int num_of_roots_ref);

#endif
