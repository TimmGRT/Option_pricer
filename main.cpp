#include <iostream>
#include "analytical.hpp"

int main() {

    // Exemple: call européen, S=100, K=100, r=5%, T=1an, sigma=20%
    OptionEU opt(100.0, 100.0, 0.05, 1.0, 0.20, true);

    Contract result = opt.price();

    opt.affiche();

    // Calcul de l'iv pour le dernier call pricé à 10.450
    OptionEU option_2(100.0, 100.0, 0.05, 1.0, 0.20, true, 10.4506);

    option_2.affiche();

    std::cout << "Value of the implied vol for the same contract at Cm = 10.4506 : " << option_2.implied_vol_newton_raphson() << std::endl;


    // Calcul de l'iv pour le dernier call pricé à 11
    OptionEU option_3(100.0, 100.0, 0.05, 1.0, 0.20, true, 11.0);

    option_3.affiche();

    std::cout << "Value of the implied vol for the same contract at Cm = 11.0 : " << option_3.implied_vol_newton_raphson() << std::endl;

}
