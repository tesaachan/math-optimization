#include "lab01.hpp"

double bitwise_method(double (*f)(double), double a, double b) {
    double delta = (b-a) / 4,
    x0 = a, f_x0 = f(x0),
    x1, f_x1;

    while (true) {
        do {
            x1 = x0 + delta, f_x1 = f(x1);
            if (f_x0 <= f_x1) break;
            x0 = x1, f_x0 = f_x1;
        } while (a < x0 && x0 < b);

        if (fabs(delta) <= eps) return x0;
        
        x0 = x1, f_x0 = f_x1, delta = -delta / 4;
    }
}
