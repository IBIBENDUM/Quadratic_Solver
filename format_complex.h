#ifndef FORMAT_COMPLEX_H
#define FORMAT_COMPLEX_H

const int COMPLEX_STR_LEN = 16;

/// Write complex number to string
/// @warning Apply free() after using
char* complex_number_to_str(char *complex_string, _Complex double a);

// Write value to _Complex from real and imag parts
// @return Result complex double
_Complex double complex_from_parts(double real, double imag);

#endif
