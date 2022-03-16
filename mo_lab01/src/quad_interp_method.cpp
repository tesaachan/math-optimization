#include "lab01.hpp"

struct point {
    double val;
    double f;
};

double quad_interp_method(double (*f)(double), double x, double dx) {
    double eps1, eps2 = eps1 = (eps)*(1e-1);
    point x1 = {x, f(x)};
    point x2 = {x + dx, f(x + dx)};
    point x3, xm, xn;

    x3.val = (x1.f > x2.f) ? x + 2*dx : x - dx;
    x3.f = f(x3.val);

    while (true) {
        xm.f = min_of_three(x1.f, x2.f, x3.f);
        xm.val = (xm.f == x1.f) ? x1.val : (xm.f == x2.f) ? x2.val : x3.val;

        double a1 = (x2.f - x1.f)/(x2.val - x1.val);
        double a2 = (1/(x3.val - x2.val)) *
            (((x3.f - x1.f)/(x3.val - x1.val)) - ((x2.f - x1.f)/(x2.val - x1.val)));

        xn.val = (x1.val + x2.val)/2 - a1/(2*a2);
        xn.f = f(xn.val);

        if (fabs(xm.f - xn.f) <= eps1 && fabs(xm.val - xn.val) <= eps2) break;

        x2 = (xn.val < xm.val) ? xn : xm;
        x1.val = x2.val - dx, x1.f = f(x1.val);
        x3.val = x2.val + dx, x3.f = f(x3.val);
    }
    return (xm.val + xn.val)/2;
}
