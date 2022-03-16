#ifndef LAB_01_HPP
#define LAB_01_HPP

#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
using namespace std;

#define eps 1e-3
#define round_up(x) ((int)((x) + 0.5))
#define min_of_three(x, y, z) (min(min((x), (y)), (z)))
typedef double(*func)(double);

double midpoint_method(func df, double a, double b);
double secant_method(func df, double a, double b);
double newton_raphson_method(func df, func ddf, double a, double b);

#endif
