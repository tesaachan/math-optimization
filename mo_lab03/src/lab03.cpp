#include <stdio.h>
#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

double func(vector<double> x) {
    return 100*pow((x[1] - pow(x[0], 2)), 2) + pow((1 - x[0]), 2);
}

vector<double> grad_func(vector<double> x) {
    return {400*(pow(x[0], 3) - x[0]*x[1]) - 2*(1 - x[0]), 200*(x[1] - pow(x[0], 2))};
}

double func2(vector<double> x) {
    return 3*pow(x[0], 4) + x[0]*x[1] + pow(x[1], 4) - 7*x[0] - 8*x[1] + 1;
}

vector<double> grad_func2(vector<double> x) {
    return {12*pow(x[0], 3) - x[1] - 7, -x[0] + 4*pow(x[1], 3) - 8};
}

vector<vector<double>> hessian_func2(vector<double> x) {
    vector<vector<double>> hessian (2, vector<double>(2));
    hessian[0][0] = 36*pow(x[0], 2);
    hessian[0][1] = -1;
    hessian[1][0] = -1;
    hessian[1][1] = 12*pow(x[1], 2);
    return hessian;
}

class Minimization {
private:
    double (*f)(vector<double>);
    vector<double> (*grad_f)(vector<double>);
    vector<vector<double>> (*hessian_f)(vector<double>);
    vector<vector<double>> hessian;
    vector<vector<double>> trans_hessian;
    vector<vector<double>> inverse_hessian;
    vector<double> d;
    vector<double> xprev;
    vector<double> xi;
    vector<double> grad;
    size_t iterations;
    double gamma;
    
    double norm(vector<double> grad_f) {
        double sum = 0;
        double p = grad_f.size();
        for (size_t i = 0; i < p; i++)
            sum += pow(fabs(grad_f[i]), p);
        return pow(sum, 1/p);
    }

    vector<double> diff(vector<double> &a, vector<double> &b) {
        vector<double> c (a.size());
        for (size_t i = 0; i < a.size(); i++)
            c[i] = a[i] - b[i];
        return c;
    }

    double g(vector<double> x, double alpha) {
        vector<double> grad = grad_f(x);
        return f({x[0] - alpha * grad[0], x[1] - alpha * grad[1]});
    }

    double dichot_method(vector<double> x, double a0, double b0, double eps) {
        int k;
        double lk, mk;
        double delta = 0.5*eps;
        double xn;
        double ak = a0, bk = b0;

        while ((bk - ak) >= eps) {
            lk = (ak + bk - delta) / 2;
            mk = (ak + bk + delta) / 2;
            if (g(x, lk) <= g(x, mk))
                bk = mk;
            else
                ak = lk;
        }
        xn = (ak + bk) / 2;
        return xn;
    }

    double t(vector<double> x, vector<double> d, double alpha) {
        return f({x[0] - alpha * d[0], x[1] - alpha * d[1]});
    }

    double newton_dichot_method(vector<double> x, vector<double> d, double a0, double b0, double eps) {
        int k;
        double to_l, to_r;
        double delta = 0.5*eps;
        double xn;
        double a = a0, b = b0;

        while ((b - a) >= eps) {
            to_l = (a + b - delta) / 2;
            to_r = (a + b + delta) / 2;
            if (t(x, d, to_l) <= t(x, d, to_r))
                b = to_r;
            else
                a = to_l;
        }
        xn = (a + b) / 2;
        return xn;
    }

    double new_gamma(vector<double> x) {
        return dichot_method(x, -1000, 1000, 0.001);
    }

    double get_det(vector<vector<double>> matrix) {
        return matrix[0][0]*matrix[1][1] - matrix[0][1]*matrix[1][0];
    }

    vector<vector<double>> trans_hessian_f(vector<vector<double>> hess) {
        vector<vector<double>> trans_hessian (2, vector<double>(2));
        for (size_t i = 0; i < 2; i++)
            for (size_t j = 0; j < 2; j++)
                trans_hessian[i][j] = hess[j][i];
        return trans_hessian;
    }

    vector<vector<double>> inverse_hessian_f(vector<vector<double>> hess) {
        vector<vector<double>> inverse_hessian (2, vector<double>(2));
        double det = get_det(hess);
        double coef = 1 / det;
        for (size_t i = 0; i < 2; i++)
            for (size_t j = 0; j < 2; j++)
                inverse_hessian[i][j] = coef * hess[i][j];
        return inverse_hessian;
    }

    vector<double> multiply(vector<vector<double>> a, vector<double> b) {
        vector<double> multiplied;
        multiplied.push_back(a[0][0]*b[0] + a[0][1]*b[1]);
        multiplied.push_back(a[1][0]*b[0] + a[1][1]*b[1]);
        return multiplied;
    }

public:
    Minimization(double (*f)(vector<double>), vector<double> (*grad_f)(vector<double>)) {
        this->f = f;
        this->grad_f = grad_f;
        this->iterations = 0;
    }

    Minimization(double (*f)(vector<double>), vector<double> (*grad_f)(vector<double>), 
        vector<vector<double>> (*hessian_f)(vector<double>)) {
        this->f = f;
        this->grad_f = grad_f;
        this->hessian_f = hessian_f;
        this->iterations = 0;
    }

    size_t get_iterations() {
        return this->iterations;
    }
    
    vector<double> gradient_method(int type, vector<double> x0, double eps1, double eps2, size_t lim) {
        this->iterations = 0;
        xi = x0;

        for (size_t i = 0; i < lim; i++) {
            this->iterations++;
        
            grad = grad_f(xi);
            if (norm(grad) < eps1)
                return xi;

            gamma = 0.002;
            xprev = xi;
            for (size_t j = 0; j < xi.size(); j++)
                xi[j] = xi[j] - (gamma * grad[j]);

            while (f(xi) - f(xprev) >= 0) {
                gamma = (type == 2) ? new_gamma(xi) : gamma / 2;
                xprev = xi;
                grad = grad_f(xprev);
                for (size_t j = 0; j < xi.size(); j++)
                    xi[j] = xprev[j] - (gamma * grad[j]);
            }
            if (norm(diff(xi, xprev)) <= eps2 && fabs(f(xi) - f(xprev)) <= eps2)
                return xi;
        }
        return xi;
    }

    vector<double> newton_regstep(vector<double> x0, double eps1, double eps2, size_t lim) {
        this->iterations = 0;
        xi = x0;
    
        gamma = 1;
        for (size_t i = 0; i < lim; i++) {
            this->iterations++;
        
            xprev = xi;
            grad = grad_f(xi);
            if (norm(grad) < eps1)
                return xi;

            hessian = hessian_f(xi);
            trans_hessian = trans_hessian_f(hessian);
            inverse_hessian = inverse_hessian_f(trans_hessian);
            double det_hes = get_det(inverse_hessian);
            if (det_hes > 0) {
                d = multiply(inverse_hessian, grad);
                d[0] = -d[0];
                d[1] = -d[1];
            } else
                for (size_t j = 0; j < xi.size(); j++)
                    d[j] = -grad[j];
    
            for (size_t j = 0; j < xi.size(); j++)
                xi[j] = xi[j] + gamma * d[j];

            if (norm(diff(xi, xprev)) <= eps2 && fabs(f(xi) - f(xprev)) <= eps2)
                return xi;
            gamma = gamma * 0.78;
        }
        return xi;
    }    
};

int main() {
    vector<double> answer;
    Minimization lab03z01 = Minimization(func, grad_func);
    Minimization lab03z02 = Minimization(func2, grad_func2, hessian_func2);

    answer = lab03z01.gradient_method(1, {0.5, 0.5}, 0.00001, 0.00001, 1e4);
    printf("Value: %13.3f\nPoints:", func(answer));
	for (size_t i = 0; i < answer.size(); i++) {
        int a = (i == 0) ? 13 : 5;
        printf("%*.3f ", a, answer[i]);
    }
    printf("\nIterations: %7.4zu\n", lab03z01.get_iterations());
    printf("\n");

    answer = lab03z01.gradient_method(2, {0.5, 0.5}, 0.00001, 0.00001, 1e4);
    printf("Value: %13.3f\nPoints:", func(answer));
	for (size_t i = 0; i < answer.size(); i++) {
        int a = (i == 0) ? 13 : 5;
        printf("%*.3f ", a, answer[i]);
    }
    printf("\nIterations: %7.4zu\n", lab03z01.get_iterations());
    printf("\n");

    answer = lab03z02.newton_regstep({1.1, 1.7}, 0.0001, 0.0001, 1e4);
    printf("Value: %14.3f\nPoints:", func2(answer));
	for (size_t i = 0; i < answer.size(); i++) {
        int a = (i == 0) ? 13 : 5;
        printf("%*.3f ", a, answer[i]);
    }
    printf("\nIterations: %7.4zu\n", lab03z02.get_iterations());
    printf("\n");
    return 0;
}
