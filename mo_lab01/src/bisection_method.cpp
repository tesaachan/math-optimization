#include "lab01.hpp"

double bisection_method(double (*f)(double), double a, double b) {
    if (fabs(b - a) <= eps)
        return (f(a) < f(b)) ? a : b;

    double xm = (a + b) / 2, f_xm = f(xm);
    double l = b - a;

    double x1 = a + l/4, f_x1 = f(x1);
    double x2 = b - l/4, f_x2 = f(x2);

    if (f_x1 < f_xm) b = xm, xm = x1;
    else if (f_x2 < f_xm) a = xm, xm = x2;
    else a = x1, b = x2;

    return bisection_method(f, a, b);
}
