#pragma once
#include "solver.hpp"

// Structure qui regroupe les résultats de pricing
struct Contract {
    double premium;
    double delta;
    double gamma;
    double theta;
    double rho;
    double vega;
    double iv;
};

// Classe option européenne Black-Scholes
class OptionEU {
private:
    double s;
    double k;
    double r;
    double T;
    double sigma;
    bool iscall;
    double market_price;

    Contract ret_contract;

public:
    OptionEU(double s, double k, double r, double T, double sigma, bool iscall = true, double market_price = 0.0);

    Contract price();
};
