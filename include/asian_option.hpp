#pragma once
#include "option.hpp"
#include "solver.hpp"

class OptionAsian : public Option {
protected:
    bool floating_strike;

public:
    OptionAsian(double s, double k, double r, double T, double sigma,
                bool iscall = true, double market_price = 0.0, bool floating_strike = false);

    double payoff(const std::vector<double>& spot) const override;
    void   premium() override;
    void   greeks()  override;
};
