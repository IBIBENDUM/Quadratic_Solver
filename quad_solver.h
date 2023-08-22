#ifndef QUAD_SOLVER_H
#define QUAD_SOLVER_H


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
//              функция возвращает количество корней
int quadratic_solver(const double a, const double b, const double c, double _Complex *x1,double _Complex *x2);

// операция:    вычисление значения корня линейного уравнения
// постусловия: x1 получает значение корня
void linear_solver(const double b, const double c, double _Complex *x1);

// операция:    вывод значений на экран
void print_roots(const double _Complex x1, const double _Complex x2, int n);

#endif
