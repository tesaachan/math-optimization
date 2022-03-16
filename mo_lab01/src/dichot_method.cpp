#include "lab01.hpp"

#define delta ((eps/2)-(eps*(1e-1)))

double dichot_method(double (*f)(double), double a, double b) {
    if (b - a <= eps)
        return (a + b)/2;

    double x1 = (a + b)/2 - delta, x2 = (a + b)/2 + delta;
    double f_1 = f(x1), f_2 = f(x2);

    if (f_1 < f_2) b = x2; else a = x1;

    return dichot_method(f, a, b);
}
