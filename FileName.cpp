#include <iostream>
#include <cmath>

double calculateKp(double sigma_B, double np) {
    return std::pow(sigma_B / 75.0, np);
}

double calculateVn(double Cv, double D, double T, double S0, double qv, double mv, double yv, double kv) {
    return (Cv * std::pow(D, qv)) / (std::pow(T, mv) * std::pow(S0, yv)) * kv;
}

double calculateKv(double sigma_B, double nv) {
    return std::pow(75.0 / sigma_B, nv);
}

double calculateN(double vn, double D) {
    const double M_PI = 3.14;
    return (1000.0 * vn) / (M_PI * D);
}

double calculateCuttingPower(double M, double n) {
    return (M * n) / 975.0;
}

int main() {
    std::locale::global(std::locale("uk_UA.UTF-8"));
    std::wcout.imbue(std::locale());
    double sigma_B = 250.0;
    double D = 24.0; 
    double S0[] = { 0.056, 0.1, 0.18, 0.32 };
    double T = 15.0;
    double Cp = 68.0;
    double np = 0.75;
    double Cv[] = { 8.7, 9.5 }; // Cv for cast iron and steel
    double qv = 0.4;
    double mv = 0.2;
    double yv = 0.5;
    double Kv = 1.0;
    double nv = 0.9;

    for (int i = 0; i < 2; ++i) {
        double KpResult = calculateKp(sigma_B, np);
        std::cout << "K_p for " << (i == 0 ? "cast iron" : "steel") << ": " << KpResult << std::endl;

        double vn = calculateVn(Cv[i], D, T, S0[i], qv, mv, yv, Kv);
        std::cout << "v_n for " << (i == 0 ? "cast iron" : "steel") << ": " << vn << " m/min" << std::endl;

        double KvResult = calculateKv(sigma_B, nv);
        std::cout << "K_v for " << (i == 0 ? "cast iron" : "steel") << ": " << KvResult << std::endl;

        double n = calculateN(vn, D);
        std::cout << "n for " << (i == 0 ? "cast iron" : "steel") << ": " << n << " rpm" << std::endl;

        double M = 9.81 * Cp * std::pow(D, 2.0) * S0[i] * KpResult;
        double cuttingPower = calculateCuttingPower(M, n);
        std::cout << "N_riz for " << (i == 0 ? "cast iron" : "steel") << ": " << cuttingPower << " kW" << std::endl;

        std::cout << std::endl;
    }

    return 0;
}
