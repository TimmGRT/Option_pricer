#include <iostream>
#include "analytical.hpp"

int main() {

    // Exemple: call européen, S=100, K=100, r=5%, T=1an, sigma=20%
    OptionEU opt(100.0, 100.0, 0.05, 1.0, 0.20, true);

    Contract result = opt.price();

    std::cout << "Premium : " << result.premium << std::endl;
    std::cout << "Delta   : " << result.delta   << std::endl;
    std::cout << "Gamma   : " << result.gamma   << std::endl;
    std::cout << "Vega    : " << result.vega    << std::endl;
    std::cout << "Theta   : " << result.theta   << std::endl;
    std::cout << "Rho     : " << result.rho     << std::endl;

    return 0;
}
