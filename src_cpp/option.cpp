#include "option.hpp"
#include <iostream>
#include <cmath>

void Option::price() {
    premium();
    greeks();
}

void Option::greeks_finite_diff(double dS, double dsigma, double dT, double dr) {

    // Delta et Gamma: variation of S
    s += dS;  premium();  double V_up   = ret_contract.premium;
    s -= 2.0 * dS;  premium();  double V_down = ret_contract.premium;
    s += dS;

    ret_contract.delta = (V_up - V_down) / (2.0 * dS);

    premium();
    ret_contract.gamma = (V_up - 2.0 * ret_contract.premium + V_down) / (dS * dS);

    // Vega: variation of sigma
    sigma += dsigma;  premium();  double V_sig_up   = ret_contract.premium;
    sigma -= 2.0 * dsigma;  premium();  double V_sig_down = ret_contract.premium;
    sigma += dsigma;

    ret_contract.vega = (V_sig_up - V_sig_down) / (2.0 * dsigma);

    // Theta: variation of time
    premium();  double V_center = ret_contract.premium;
    T -= dT;  premium();  double V_T_down = ret_contract.premium;
    T += dT;

    ret_contract.theta = (V_T_down - V_center) / dT;

    // Rho: variation of rates
    r += dr;  premium();  double V_r_up   = ret_contract.premium;
    r -= 2.0 * dr;  premium();  double V_r_down = ret_contract.premium;
    r += dr;

    ret_contract.rho = (V_r_up - V_r_down) / (2.0 * dr);

    premium();
}

void Option::affiche() const {
    std::cout << " ======= Option Metrics : ======= " << std::endl;
    std::cout << "Premium : " << ret_contract.premium << std::endl;
    std::cout << "Delta   : " << ret_contract.delta   << std::endl;
    std::cout << "Gamma   : " << ret_contract.gamma   << std::endl;
    std::cout << "Vega    : " << ret_contract.vega    << std::endl;
    std::cout << "Theta   : " << ret_contract.theta   << std::endl;
    std::cout << "Rho     : " << ret_contract.rho     << std::endl;
    std::cout << " ================================ " << std::endl;
    std::cout << " Implied vol : " << ret_contract.iv << std::endl;
    std::cout << " ================================ " << std::endl;
}
