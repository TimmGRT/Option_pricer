#include <iostream>
#include "analytical.hpp"

int main() {

    // Exemple: call européen, S=100, K=100, r=5%, T=1an, sigma=20%
    OptionEUBS opt(100.0, 100.0, 0.05, 1.0, 0.20, true);
    opt.affiche();

    // Calcul de l'iv pour le dernier call pricé à 10.450
    OptionEUBS option_2(100.0, 100.0, 0.05, 1.0, 0.20, true, 10.4506);
    option_2.affiche();


    // Calcul de l'iv pour le dernier call pricé à 11
    OptionEUBS option_3(100.0, 100.0, 0.05, 1.0, 0.20, true, 11.0);
    option_3.affiche();

    // Test pricer pour OptionMC
    OptionEUMC opt_MC(100.0, 100.0, 0.05, 1.0, 0.20, true);
    opt_MC.affiche();
}
