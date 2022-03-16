#include "lab02.hpp"

double f(double x) {
    return (5/x + x*x);
}

double df(double x) {
    return (2*x - 5/(x*x));
}

double ddf(double x) {
    return (2 + 10/(x*x*x));
}

int main() {
    double a = 0.5, b = 2, min;
    cout << fixed << setprecision(3);
    cout << " " << setw(55) << setfill('-') << "" << endl << setfill(' ');
    cout << "|" << setw(56) << "|" <<  endl;
    cout << '|' << setw(21) << "Вариант 23:" << setw(42) << '|' << endl;
    cout << "|" << setw(56) << "|" <<  endl;
    cout << "|" << setw(56) << "|" <<  endl;

    cout << '|' << setw(42) << "Метод средней точки:";
    min = midpoint_method(df, a, b);
    cout << setw(10) << min << setw(10) << f(min) << setw(11) << '|' << endl;

    cout << '|' << setw(34) << "Метод хорд:";
    min = secant_method(df, a, b);
    cout << setw(10) << min << setw(10) << f(min) << setw(11) << '|' << endl;

    cout << '|' << setw(41) << "Метод касательных:";
    min = newton_raphson_method(df, ddf, a, b);
    cout << setw(10) << min << setw(10) << f(min) << setw(11) << '|' << endl;

    cout << "|" << setw(56) << "|" <<  endl;
    cout << " " << setw(55) << setfill('-') << "" << endl << setfill(' ');
    return 0;
}
