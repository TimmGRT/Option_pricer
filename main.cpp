#include <iostream>
#include "european_option.hpp"
#include "asian_option.hpp"


int main() {

    // ---- Black-Scholes analytique ----
    OptionEUBS opt(100.0, 100.0, 0.05, 1.0, 0.20, true);
    opt.affiche();

    // IV : market price == premium → doit retrouver sigma=0.20
    OptionEUBS option_2(100.0, 100.0, 0.05, 1.0, 0.20, true, 10.4506);
    option_2.affiche();

    // IV : market price légèrement au-dessus → sigma implicite > 0.20
    OptionEUBS option_3(100.0, 100.0, 0.05, 1.0, 0.20, true, 11.0);
    option_3.affiche();

    // ---- Monte Carlo + grecs par différences finies ----
    OptionEUMC opt_MC(100.0, 100.0, 0.05, 1.0, 0.20, true);
    opt_MC.affiche();

    // Option asiatique
    OptionAsian opt_as(100.0, 100.0, 0.05, 1.0, 0.20, true, false);
    opt_as.affiche();
    
}
