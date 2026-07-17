#pragma once
#include <vector>

// Regroupe tous les résultats de pricing
struct Contract {
    double premium = 0.0;
    double delta   = 0.0;
    double gamma   = 0.0;
    double theta   = 0.0;
    double rho     = 0.0;
    double vega    = 0.0;
    double iv      = 0.0;
};

class Option {
protected:
    double s;
    double k;
    double r;
    double T;
    double sigma;
    bool iscall;
    double market_price;

    Contract ret_contract;

public:
    Option(double s, double k, double r, double T, double sigma,
           bool iscall = true, double market_price = 0.0)
        : s(s), k(k), r(r), T(T), sigma(sigma),
          iscall(iscall), market_price(market_price) {}

    virtual ~Option() = default;

    // Getters
    double get_s() const { return s; }
    double get_k() const { return k; }
    double get_r() const { return r; }
    double get_T() const { return T; }
    double get_sigma() const { return sigma; }
    bool   get_iscall() const { return iscall; }

    // payoff in function of the spot
    virtual double payoff(const std::vector<double>& spot) const = 0;

    //computation of greeks and premium
    virtual void premium() = 0;
    virtual void greeks() = 0;
    void price();

    // Greeks calculation by finite diff
    void greeks_finite_diff(double dS = 0.01, double dsigma = 0.0001,
                            double dT = 1.0 / 365.0, double dr = 0.0001);

    // Display metrics
    void affiche() const;
};
