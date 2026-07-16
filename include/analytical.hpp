#pragma once
#include "solver.hpp"
#include "option.hpp"

class OptionEUBS : public Option{

    public:
        //constructeur
        OptionEUBS(double s, double k, double r, double T, double sigma, bool iscall = true, double market_price = 0.0);
        // greeks et premium
        Contract price() override;
        // payoff
        double payoff(const std::vector<double>& spot) const override;
        //implied vol
        double implied_vol_newton_raphson(double x0 = 0.20, double tolerance = 1e-6, int max_iteration = 100);

};

class OptionEUMC : public Option{

    public:
        //constructeur
        OptionEUMC(double s, double k, double r, double T, double sigma, bool iscall = true, double market_price = 0.0);
        //greeks et premium
        Contract price() override;
        // payoff
        double payoff(const std::vector<double>& spot) const override;

};

