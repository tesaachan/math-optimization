#ifndef LAB_03_HPP
#define LAB_03_HPP

#include <stdio.h>
#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

class Minimization {
private:
    double (*f)(vector<double>);
    size_t iterations;
    double gamma;
    vector<double> (*grad_f)(vector<double>);
    vector<vector<double>> (*hessian_f)(vector<double>);
    vector<vector<double>> hessian;
    vector<vector<double>> trans_hessian;
    vector<vector<double>> inverse_hessian;
    vector<double> d;
    vector<double> xprev;
    vector<double> xi;
    vector<double> grad;
    
    double norm(vector<double> grad_f);
    double g(vector<double> x, double alpha);
    double dichot_method(vector<double> x, double a0, double b0, double eps);
    double t(vector<double> x, vector<double> d, double alpha);
    double newton_dichot_method(vector<double> x, vector<double> d, double a0, double b0, double eps);
    double new_gamma(vector<double> x);
    double get_det(vector<vector<double>> matrix);
    vector<vector<double>> trans_hessian_f(vector<vector<double>> hess);
    vector<vector<double>> inverse_hessian_f(vector<vector<double>> hess);
    vector<double> diff(vector<double> &a, vector<double> &b);
    vector<double> multiply(vector<vector<double>> a, vector<double> b);

public:
    Minimization(double (*f)(vector<double>), vector<double> (*grad_f)(vector<double>));
    Minimization(double (*f)(vector<double>), vector<double> (*grad_f)(vector<double>), vector<vector<double>> (*hessian_f)(vector<double>));
    vector<double> gradient_method(int type, vector<double> x0, double eps1, double eps2, size_t lim);
    vector<double> newton_regstep(vector<double> x0, double eps1, double eps2, size_t lim);
    size_t get_iterations();
};

#endif