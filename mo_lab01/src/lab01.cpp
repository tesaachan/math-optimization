#include "lab01.hpp"

double f(double x) {
    return pow(x-1, 2) / x;
}

int main() {
    double a = 0.5, b = 2, min;
    cout << fixed << setprecision(4);
    cout << " " << setw(55) << setfill('-') << "" << endl << setfill(' ');
    cout << "|" << setw(56) << "|" <<  endl;
    cout << '|' << setw(21) << "Вариант 23:" << setw(42) << '|' << endl;
    cout << "|" << setw(56) << "|" <<  endl;
    cout << "|" << setw(56) << "|" <<  endl;

    cout << '|' << setw(56) << "Метод равномерного поиска:";
    min = enum_method(f, a, b);
    cout << setw(10) << min << setw(10) << f(min) << setw(3) << '|' << endl;

    cout << '|' << setw(47) << "Метод дихотомии:";
    min = dichot_method(f, a, b);
    cout << setw(10) << min << setw(10) << f(min) << setw(3) << '|' << endl;

    cout << '|' << setw(62) << "Метод квадратичной интерполяции:";
    min = quad_interp_method(f, 1.3, 0.00001);
    cout << setw(10) << min << setw(10) << f(min) << setw(3) << '|' << endl;

    cout << "|" << setw(56) << "|" <<  endl;
    cout << " " << setw(55) << setfill('-') << "" << endl << setfill(' ');
    cout << "|" << setw(56) << "|" <<  endl;
    cout << '|' << setw(22) << "Остальные:" << setw(43) << '|' << endl;
    cout << "|" << setw(56) << "|" <<  endl;
    cout << "|" << setw(56) << "|" <<  endl;

    cout << '|' << setw(56) << "Метод поразрядного поиска:";
    min = bitwise_method(f, a, b);
    cout << setw(10) << min << setw(10) << f(min) << setw(3) << '|' << endl;

    cout << '|' << setw(59) << "Метод деления отрезка пополам:";
    min = bisection_method(f, a, b);
    cout << setw(10) << min << setw(10) << f(min) << setw(3) << '|' << endl;

    cout << '|' << setw(53) << "Метод золотого сечения:";
    min = golden_section_method(f, a, b);
    cout << setw(10) << min << setw(10) << f(min) << setw(3) << '|' << endl;

    cout << '|' << setw(47) << "Метод Фибоначчи:";
    min = fibonacci_method(f, a, b);
    cout << setw(10) << min << setw(10) << f(min) << setw(3) << '|' << endl;

    cout << "|" << setw(56) << "|" <<  endl;
    cout << " " << setw(55) << setfill('-') << "" << endl;
    return 0;
}
