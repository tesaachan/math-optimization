#include "lab02.hpp"

double midpoint_method(func df, double a, double b) {
    double xn = (a + b)/2, df_xn = df(xn);
    if (fabs(df_xn) <= eps) {
        return xn;
    }
    if (df_xn > 0) return midpoint_method(df, a, xn);
    else return midpoint_method(df, xn, b);
}
