#ifndef QUAD_SOLVER_H
#define QUAD_SOLVER_H

// операция:    получения значений коэффициентов
// постусловия: a,b,c получают введенные значения
int read_coefs(double *a, double *b, double *c); // TODO: name read?

// операция:    вычисление дискриминанта
// постусловия: функция возвращает значение дискриминанта
double calculate_discriminant(const double a, const double b, const double c);

// операция:    Calculate roots
// постусловия: x1 and x2 gets roots values,
//              function returns 1 if coeffs are incorrect,
//              0 if coeffs are correct
bool solve_quadratic_equation(const double a, const double b, const double c, double _Complex *x1, double _Complex *x2, int *NumberOfRoots);

// операция:    вычисление значения корня линейного уравнения
// постусловия: x1 получает значение корня
void solve_linear_equation(const double b, const double c, double _Complex *x1);

// операция:    вывод значений на экран
void print_roots(const double _Complex x1, const double _Complex x2, int n);

void skip_line(void);

#endif
