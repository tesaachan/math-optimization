#include "lab01.hpp"

double golden_section_method(double (*f)(double), double a, double b) {
    double tau = (sqrt(5)-1)/2;
    double x1 = b - (b - a)*tau;
    double x2 = a + (b - a)*tau;

    while (fabs(b - a) > eps) {
        if (f(x1) > f(x2)) {
            a = x1;
            x1 = x2;
            x2 = b + a - x1;
        } else {
            b = x2;
            x2 = x1;
            x1 = b + a - x2;
        }
    }
    return (f(a) < f(b)) ? a : b;
}
