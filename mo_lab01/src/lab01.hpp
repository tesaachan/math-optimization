#ifndef LAB_01_HPP
#define LAB_01_HPP

#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
using namespace std;

#define eps 1e-4
#define round_up(x) ((int)((x) + 0.5))
#define min_of_three(x, y, z) (min(min((x), (y)), (z)))

double enum_method(double (*f)(double), double a, double b);
double bitwise_method(double (*f)(double), double a, double b);
double bisection_method(double (*f)(double), double a, double b);
double dichot_method(double (*f)(double), double a, double b);
double golden_section_method(double (*f)(double), double a, double b);
double fibonacci_method(double (*f)(double), double a, double b);
double quad_interp_method(double (*f)(double), double x1, double dx);

#endif
