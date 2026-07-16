#include <cmath>
#include <iostream>
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

    ret_contract.gamma = normaldensityfunction(d1)/(s*sigma*std::sqrt(T));
    ret_contract.vega  = s * std::sqrt(T) * normaldensityfunction(d1);

    ret_contract.theta = -(s * sigma * normaldensityfunction(d1)) / (2.0 * std::sqrt(T))
                        - r * k * std::exp(-r * T) * normalcumfunction(iscall ? d2 : -d2);

    ret_contract.rho   = iscall
                         ?  k * T * std::exp(-r * T) * normalcumfunction(d2)
                         : -k * T * std::exp(-r * T) * normalcumfunction(-d2);

    return ret_contract;
}

// implied vol 
double OptionEU::implied_vol_newton_raphson(double x0, double tolerance, int max_iteration ){

    double sigma_old = this->sigma;
    double sigma_new(x0);

    for (int i(0); i<max_iteration; ++i){

        //Sigma adjustment
        this->sigma = sigma_new;

        //Re computation of option metrics
        this->price();

        // calcul of f
        double f = this->ret_contract.premium - market_price;

        // calcul of df
        double df = this->ret_contract.vega;

        // update of ret
        if (std::abs(df)<1e-12){
            break;
        }

        //update of sigma
        double ratio = f/df;
        sigma_new = this->sigma - ratio;

        // vol validation
        if (std::abs(ratio) < tolerance){
            break;
        }

    }
    // setting back initial vol
    this->sigma = sigma_old;
    this->ret_contract.iv = sigma_new;

    return sigma_new;
}

//graphique
void OptionEU::affiche(){
    std::cout << " ======= Option Metrics : ======= " << std::endl;
    std::cout << "Premium : " << ret_contract.premium << std::endl;
    std::cout << "Delta   : " << ret_contract.delta   << std::endl;
    std::cout << "Gamma   : " << ret_contract.gamma   << std::endl;
    std::cout << "Vega    : " << ret_contract.vega    << std::endl;
    std::cout << "Theta   : " << ret_contract.theta   << std::endl;
    std::cout << "Rho     : " << ret_contract.rho     << std::endl;
    std::cout << " ================================ " << std::endl;
}

