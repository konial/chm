#include <iostream>
#include <cmath>
#include <fstream>
#include <iomanip>

using namespace std;

double F(double x, double y){
    return -2 * y - 2 * x * x - 2 * x;
}

double F1(double x, double u, double v) {
    return sqrt(x * x + 1.1 * u * u) + v;
}

double F2(double x, double u, double v) {
    return cos(2.1 * v) + u;
}

int main() {
    double a = 0, b = 10, h = 0.1;
    int n = ceil((b - a) / h);
    double X[n];
    double K1[n];
    double K2[n];
    double K3[n];
    double K4[n];
    double M1[n];
    double M2[n];
    double M3[n];
    double M4[n];
    double Y[n];
    double Y1[n];
    double Y2[n];
    // вычисление для одного уравнения
    ofstream out ("answer.txt");
    X[0] = a; Y[0] = -2;
    out << setprecision(10) << fixed << "(" << X[0] << ", " << Y[0] << "),";
    for(int i = 1; i <= n; ++i){
        X[i] = a + i * h;
        K1[i] = F(X[i - 1], Y[i - 1]);
        K2[i] = F(X[i - 1] + h / 2.0, Y[i - 1] + h * K1[i] / 2.0);
        K3[i] = F(X[i - 1] + h / 2.0, Y[i - 1] + h * K2[i] / 2.0);
        K4[i] = F(X[i - 1] + h, Y[i - 1] + h * K3[i]);
        Y[i] = Y[i - 1] + h * (K1[i] + 2 * K2[i] + 2 * K3[i] + K4[i]) / 6;
        // вывод результатов
        out << setprecision(10) << fixed << "(" << X[i] << ", " << Y[i] << ")";
        if(i != n) out << ",";
    }
    out << endl;

    X[0] = a; Y1[0] = 0.5, Y2[0] = 4;
    // вычисление для системы

    for(int i = 1; i <= n; ++i){
        X[i] = a + i * h;
        K1[i] = F1(X[i - 1], Y1[i - 1], Y2[i - 1]);
        M1[i] = F2(X[i - 1], Y1[i - 1], Y2[i - 1]);
        K2[i] = F1(X[i - 1] + h / 2.0, Y1[i - 1] + h * K1[i] / 2.0, Y2[i - 1] + h * M1[i] / 2.0);
        M2[i] = F2(X[i - 1] + h / 2.0, Y1[i - 1] + h * K1[i] / 2.0, Y2[i - 1] + h * M1[i] / 2.0);
        K3[i] = F1(X[i - 1] + h / 2.0, Y1[i - 1] + h * K2[i] / 2.0, Y2[i - 1] + h * M2[i] / 2.0);
        M3[i] = F2(X[i - 1] + h / 2.0, Y1[i - 1] + h * K2[i] / 2.0, Y2[i - 1] + h * M2[i] / 2.0);
        K4[i] = F1(X[i - 1] + h, Y1[i - 1] + h * K3[i], Y2[i - 1] + h * M3[i]);
        M4[i] = F2(X[i - 1] + h, Y1[i - 1] + h * K3[i], Y2[i - 1] + h * M3[i]);
        Y1[i] = Y1[i - 1] + h * (K1[i] + 2 * K2[i] + 2 * K3[i] + K4[i]) / 6;
        Y2[i] = Y2[i - 1] + h * (M1[i] + 2 * M2[i] + 2 * M3[i] + M4[i]) / 6;
    }
    // вывод результатов
    out << endl;
    for(int i = 0; i <= n; ++i) {
        out << setprecision(10) << fixed << "(" << X[i] << ", " << Y1[i] << ")";
        if(i != n) out << ",";
    }
    out << endl << endl;
    for(int i = 0; i <= n; ++i) {
        out << setprecision(10) << fixed << "(" << X[i] << ", " << Y2[i] << ")";
        if(i != n) out << ",";
    }
    out << endl;
    out.close();
    return 0;
}
