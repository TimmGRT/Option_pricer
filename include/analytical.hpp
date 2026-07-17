#pragma once
#include "option.hpp"
#include "solver.hpp"

// ============================================
// EU Option Black Scholes
// ============================================
class OptionEUBS : public Option {
public:
    OptionEUBS(double s, double k, double r, double T, double sigma,
               bool iscall = true, double market_price = 0.0);

    double payoff(const std::vector<double>& spot) const override;
    void   premium() override;
    void   greeks()  override;

    double implied_vol_newton_raphson(double x0 = 0.20,
                                      double tolerance = 1e-6,
                                      int max_iteration = 100);
};

// ============================================
// EU Option Monte Carlo
// ============================================
class OptionEUMC : public Option {
public:
    OptionEUMC(double s, double k, double r, double T, double sigma,
               bool iscall = true, double market_price = 0.0);

    double payoff(const std::vector<double>& spot) const override;
    void   premium() override;
    void   greeks()  override;
};
