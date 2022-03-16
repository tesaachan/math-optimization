#include "lab02.hpp"

double loop(func df, double a, double b, double df_a, double df_b) {
    if (df_a * df_b >= 0) {
        if (df_a > 0 && df_b > 0) return a;
        if (df_a < 0 && df_b < 0) return b;
        return (df_a == 0) ? a : b;
    }

    double xn = a - (df_a/(df_a - df_b))*(a - b),
    df_xn = df(xn);

    if (fabs(df_xn) <= eps) return xn;
    else if (df_xn > 0) return loop(df, a, xn, df_a, df_xn);
    else return loop(df, xn, b, df_xn, df_b);
}

double secant_method(func df, double a, double b) {
    return loop(df, a, b, df(a), df(b));
}
