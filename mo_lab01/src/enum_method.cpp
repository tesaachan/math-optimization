#include "lab01.hpp"

double enum_method(double (*f)(double), double a, double b) {
    int n = round_up((b - a)/eps);
    double dx = (b - a)/n;
    double k = a;

    for (double i = 1; i <= n; i += 1) {
        double x_i = a + i*dx;
        if (f(x_i) < f(k)) k = x_i;
    }

    return k;
}
