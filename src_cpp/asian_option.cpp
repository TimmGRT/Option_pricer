#include "asian_option.hpp"


OptionAsian::OptionAsian(double s, double k, double r, double T, double sigma,
                       bool iscall, double market_price, bool floating_strike)
    : Option(s, k, r, T, sigma, iscall, market_price), floating_strike(floating_strike)
{
    premium();   // pricing précis : 100000 simulations
    greeks();    // grecs rapides : greeks() réduit num_it_ à 10000 lui-même
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
    ret_contract.premium = MonteCarloPricer(*this, num_it_, num_step_);
}

void OptionAsian::greeks() {
    num_it_   = 2000;   // réduit pour les 9 appels des diff. finies
    num_step_ = 20;     // moins de pas aussi : on veut une dérivée, pas une précision absolue
    greeks_finite_diff(1.0, 0.01, 1.0 / 52.0, 0.001);
    num_it_   = 100000; // remet la précision normale
    num_step_ = 252;
}
