#include "lab01.hpp"

int generate_fib(vector<int> &fib, int i, double ref_value) {
    if (fib[i-1] > ref_value)
        return i-1;

    int new_fib = fib[i-1] + fib[i-2];
    fib.push_back(new_fib);

    return generate_fib(fib, i+1, ref_value);
}

double fibonacci_method(double (*f)(double), double a, double b) {
    double delta = 0.0001;
    vector<int> fib(2);
    fib[0] = fib[1] = 1;
    int n = generate_fib(fib, 2, (b-a)/eps);

    double x1 = a + ((double)fib[n-2]/fib[n])*(b-a), f_x1 = f(x1);
    double x2 = a + ((double)fib[n-1]/fib[n])*(b-a), f_x2 = f(x2);

    for (int k = 1; k < n-1; k++) {
        if (f_x1 > f_x2) {
            a = x1, x1 = x2, f_x1 = f_x2;
            x2 = a + ((double)fib[n-k-1]/fib[n-k])*(b-a);
            if (k != n - 2) f_x2 = f(x2);
        } else {
            b = x2, x2 = x1, f_x2 = f_x1;
            x1 = a + ((double)fib[n-k-2]/fib[n-k])*(b-a);
            if (k != n - 2) f_x1 = f(x1);
        }
    }
    x2 = x1 + delta;
    if (f(x1) > f(x2)) a = x1; else b = x2;

    return (a + b) / 2;
}
