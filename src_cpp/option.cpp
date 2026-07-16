#include "option.hpp"
#include <iostream>

// ============================================
// Option EU pricing
// ============================================

void Option::affiche()const{
    std::cout << " ======= Option Metrics : ======= " << std::endl;
    std::cout << "Premium : " << (ret_contract.premium < 1e-10 ? 0.0 : ret_contract.premium) << std::endl;
    std::cout << "Delta   : " << (ret_contract.delta < 1e-10 ? 0.0 : ret_contract.delta) << std::endl;
    std::cout << "Gamma   : " << (ret_contract.gamma < 1e-10 ? 0.0 : ret_contract.gamma)   << std::endl;
    std::cout << "Vega    : " << (ret_contract.vega < 1e-10 ? 0.0 : ret_contract.vega) << std::endl;
    std::cout << "Theta   : " << (ret_contract.theta < 1e-10 ? 0.0 : ret_contract.theta)   << std::endl;
    std::cout << "Rho     : " << (ret_contract.rho < 1e-10 ? 0.0 : ret_contract.rho) << std::endl;
    std::cout << " ================================ " << std::endl;
    std::cout << " Implied vol : " << (ret_contract.iv < 1e-10 ? 0.0 : ret_contract.iv) << std::endl;
    std::cout << " ================================ " << std::endl;
}