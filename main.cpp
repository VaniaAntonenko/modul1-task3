#include <iostream>
#include <cmath>
#include <vector>
#include <chrono>

using namespace std;

double f(double x){return x*x;}

double rho(double x){return x;}

double trap(double a, double b, int n) {
    double h = (b-a)/n;
    double fa2r = f(a)*f(a)*rho(a);
    double fb2r = f(b)*f(b)*rho(b);
    double sum = 0.5 * (fa2r + fb2r);
    for (int i = 1; i < n; ++i) {
        double fx = f(a + i * h);
        sum += fx*fx*rho(a+i*h);
    }
    return sum*h;
}

double integr(double a, double b, double epsilon) {
    int n = 10; // Початкова кількість розбиттів
    double i_n = trap(a, b, n);
    while (true) {
        n *= 2;
        double i_2n = trap(a, b, n);
        double error = abs(i_2n - i_n) / 3.0;
        if (error < epsilon) {
            return i_2n;
        }
        i_n = i_2n;
    }
}

int main() {
    double a,b,eps;
    cout << "Введіть границі інтегрування a та b" << endl;
    cin >> a;
    cin >> b;
    cout << "Введіть точність інтегрування eps" << endl;
    cin >> eps;
    auto start = chrono::high_resolution_clock::now();

    // пункт a
    double mas = integr(a,b, eps)*M_PI;
    cout << "Маса: " << mas << endl;
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, std::milli> duration = end - start;
    cout << "Час виконання блоку а: " << duration.count() << " мс" << endl;

    //пункт b
    cout << "Введіть кількість w_i" << endl;
    int n;
    cin >> n;
    vector<double> ws;
    double wi;
    for (int i = 0; i<n; i++) {
        cout << "Введіть w_i" << endl;
        cin >> wi;
        ws.push_back(wi);
    }
    start = chrono::high_resolution_clock::now();
    double maszal = mas;
    double a1 = a;
    for (int i = 0; i<ws.size(); i++) {
        wi = ws[i];
        double masi = wi * maszal;
        double right = b;
        double left = a1;
        while (true) {
            double bm = (right+left)/2.0;
            double masintegr = M_PI*integr(a1, bm, eps);
            if (masintegr > masi) {
                right = bm;
            }else if (masintegr < masi){
                left = bm;
            }
            if ((right - left) < 1e-5 || fabs(masi - masintegr) < 1e-4) {
                cout << "x = " << bm << endl;
                a1 = bm;
                maszal -= masi;
                break;
            }
        }
    }
    end = chrono::high_resolution_clock::now();
    duration = end - start;
    cout << "Час виконання блоку b: " << duration.count() << " мс" << endl;
    return 0;
}