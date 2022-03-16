#include "lab02.hpp"

double newton_raphson_method(func df, func ddf, double a, double b) {
    double xn = (a + b)/2, df_xn = df(xn), ddf_xn;

    while (fabs(df_xn) > eps) {
        ddf_xn = ddf(xn);
        if (ddf_xn <= 0)
            throw runtime_error("wrong value f''(xn) <= 0");

        xn = xn - df_xn/ddf_xn;
        df_xn = df(xn);
    }
    return xn;
}
