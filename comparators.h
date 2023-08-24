#ifndef COMPARATORS_H_
#define COMPARATORS_H_

// TODO: Rename header
const double PRECISION = 0.0000001;

int compare_with_zero(const double a);

int compare_complex_doubles(const double _Complex a, const double _Complex b);

int complex_isnan(_Complex double x);

void sort_complex_by_ascending(double _Complex *a, double _Complex *b);

int get_expected_args_amount(const char *format);


#endif
