#ifndef QUAD_SOLVER_INTERACTIVE_H
#define QUAD_SOLVER_INTERACTIVE_H

bool ask_for_continue(void);
bool ask_coefs(double *a, double *b, double *c);
void skip_line(void);
int read_coefs(double *a_ptr, double *b_ptr, double *c_ptr);
#endif
