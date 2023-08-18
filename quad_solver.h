#ifndef QUAD_SOLVER_H
#define QUAD_SOLVER_H

union root
{
    double real_n;
    double _Complex complex_n;
};

// операция:    получения значений коэффициентов
// постусловия: a,b,c получают введенные значения
int get_coefs(double * a, double * b, double * c);

// операция:    вычисление дискриминанта
// постусловия: функция возвращает значение дискриминанта
double discr_solver(const double a, const double b, const double c);

// операция:    проверка коэффициентов на корректность
// постусловия: функция возвращает true, если коэффициенты
//              прошли проверку, и false в противном случае
bool validate_coefs(const double a,const double b, const double c, const int count);

// операция:    вычисление значения корней
// постусловия: x1 и x2 получают значения корней,
//              функция возвращает true, если корни комплексные,
//              и false в противном случае
bool quadratic_solver(const double a, const double b, const double d,union root *x1,union root *x2);

// операция:    вывод значений на экран
void print_roots(const union root x1,const union root x2, const bool is_complex);

#endif
