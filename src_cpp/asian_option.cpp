#include "asian_option.hpp"


OptionAsian::OptionAsian(double s, double k, double r, double T, double sigma,
                       bool iscall, double market_price, bool floating_strike)
    : Option(s, k, r, T, sigma, iscall, market_price), floating_strike(floating_strike)
{
    price();
}

double OptionAsian::payoff(const std::vector<double>& spot) const {
    double somme(0.0);

    for (double price:spot){
        somme += price;
    }
    double moyenne = somme/static_cast<double>(spot.size());

    if (!floating_strike){
        return iscall ? std::max(moyenne - k, 0.0): std::max(k - moyenne, 0.0);
    }

    else{
        double due_date_price = spot.back();
        return iscall ? std::max(due_date_price-moyenne,0.0):std::max(moyenne-due_date_price, 0.0);
    }
}

void OptionAsian::premium() {
    ret_contract.premium = MonteCarloPricer(*this, 100000, 252); // trading days : 252
}

void OptionAsian::greeks() {
    // Perturbations plus larges pour compenser le bruit du MC
    greeks_finite_diff(1.0, 0.01, 1.0 / 52.0, 0.001);
}
