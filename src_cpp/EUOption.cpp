#include <cmath>
#include "EUOption.hpp"

// ============================================
// OptionEUBS — Black-Scholes analytique
// ============================================

OptionEUBS::OptionEUBS(double s, double k, double r, double T, double sigma,
                       bool iscall, double market_price)
    : Option(s, k, r, T, sigma, iscall, market_price)
{
    price();
    if (market_price != 0.0) {
        ret_contract.iv = implied_vol_newton_raphson();
    }
}

double OptionEUBS::payoff(const std::vector<double>& spot) const {
    double s_final = spot.back();
    return iscall ? std::max(s_final - k, 0.0)
                  : std::max(k - s_final, 0.0);
}

void OptionEUBS::premium() {
    double d1 = (std::log(s / k) + (r + sigma * sigma / 2.0) * T) / (sigma * std::sqrt(T));
    double d2 = d1 - sigma * std::sqrt(T);

    if (iscall) {
        ret_contract.premium = s * normalcumfunction(d1) - k * std::exp(-r * T) * normalcumfunction(d2);
    } else {
        ret_contract.premium = k * std::exp(-r * T) * normalcumfunction(-d2) - s * normalcumfunction(-d1);
    }
}

void OptionEUBS::greeks() {
    double d1 = (std::log(s / k) + (r + sigma * sigma / 2.0) * T) / (sigma * std::sqrt(T));
    double d2 = d1 - sigma * std::sqrt(T);

    ret_contract.delta = iscall ? normalcumfunction(d1)
                                : normalcumfunction(d1) - 1.0;

    ret_contract.gamma = normaldensityfunction(d1) / (s * sigma * std::sqrt(T));

    ret_contract.vega  = s * std::sqrt(T) * normaldensityfunction(d1);

    ret_contract.theta = -(s * sigma * normaldensityfunction(d1)) / (2.0 * std::sqrt(T))
                         - r * k * std::exp(-r * T) * normalcumfunction(iscall ? d2 : -d2);

    ret_contract.rho   = iscall
                         ?  k * T * std::exp(-r * T) * normalcumfunction(d2)
                         : -k * T * std::exp(-r * T) * normalcumfunction(-d2);
}

double OptionEUBS::implied_vol_newton_raphson(double x0, double tolerance, int max_iteration) {
    double sigma_old = sigma;
    double sigma_new = x0;

    for (int i = 0; i < max_iteration; ++i) {
        sigma = sigma_new;
        premium();
        greeks();

        double f  = ret_contract.premium - market_price;
        double df = ret_contract.vega;

        if (std::abs(df) < 1e-12) break;

        double ratio = f / df;
        sigma_new = sigma - ratio;

        if (std::abs(ratio) < tolerance) break;
    }

    sigma = sigma_old;
    price(); // remet ret_contract dans l'état initial avec la vraie vol
    return sigma_new;
}

// ============================================
// OptionEUMC — Monte Carlo
// ============================================

OptionEUMC::OptionEUMC(double s, double k, double r, double T, double sigma,
                       bool iscall, double market_price)
    : Option(s, k, r, T, sigma, iscall, market_price)
{
    price();
}

double OptionEUMC::payoff(const std::vector<double>& spot) const {
    double s_final = spot.back();
    return iscall ? std::max(s_final - k, 0.0)
                  : std::max(k - s_final, 0.0);
}

void OptionEUMC::premium() {
    ret_contract.premium = MonteCarloPricer(*this, 100000, 1);
}

void OptionEUMC::greeks() {
    // Perturbations plus larges pour compenser le bruit du MC
    greeks_finite_diff(1.0, 0.01, 1.0 / 52.0, 0.001);
}




