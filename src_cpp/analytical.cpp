#include <cmath>
#include "analytical.hpp"

// Constructeur
OptionEU::OptionEU(double s, double k, double r, double T, double sigma, bool iscall, double market_price)
    : s(s), k(k), r(r), T(T), sigma(sigma), iscall(iscall), market_price(market_price)
{}

// Calcul Black-Scholes
Contract OptionEU::price() {

    double d1 = (std::log(s / k) + (r + (sigma * sigma / 2.0)) * T) / (sigma * std::sqrt(T));
    double d2 = d1 - sigma * std::sqrt(T);

    if (iscall) {
        ret_contract.premium = s * normalcumfunction(d1) - k * std::exp(-r * T) * normalcumfunction(d2);
        ret_contract.delta   = normalcumfunction(d1);
    } else {
        ret_contract.premium = k * std::exp(-r * T) * normalcumfunction(-d2) - s * normalcumfunction(-d1);
        ret_contract.delta   = normalcumfunction(d1) - 1.0;
    }

    ret_contract.gamma = std::exp(-d1 * d1 / 2.0) / (s * sigma * std::sqrt(2.0 * M_PI * T));
    ret_contract.vega  = s * std::sqrt(T) * std::exp(-d1 * d1 / 2.0) / std::sqrt(2.0 * M_PI);
    ret_contract.theta = -(s * sigma * std::exp(-d1 * d1 / 2.0)) / (2.0 * std::sqrt(2.0 * M_PI * T))
                         - r * k * std::exp(-r * T) * normalcumfunction(iscall ? d2 : -d2);
    ret_contract.rho   = iscall
                         ?  k * T * std::exp(-r * T) * normalcumfunction(d2)
                         : -k * T * std::exp(-r * T) * normalcumfunction(-d2);


    ret_contract.iv = 0.0*market_price;

    return ret_contract;
}
