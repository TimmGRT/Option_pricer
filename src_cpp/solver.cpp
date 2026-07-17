#include <cmath>
#include <random>
#include <vector>
#include "solver.hpp"

// Fonction de répartition N(x)
double normalcumfunction(double x) {
    return 0.5 * (1.0 + std::erf(x / std::sqrt(2.0)));
}

// Densité n(x)
double normaldensityfunction(double x) {
    return (1.0 / std::sqrt(2.0 * M_PI)) * std::exp(-x * x / 2.0);
}

// Bruit gaussien — générateur local, pas statique
double gaussian_noise(std::mt19937& generator) {
    std::normal_distribution<double> dist(0.0, 1.0);
    return dist(generator);
}

// Pricer Monte Carlo générique — seed fixe pour reproductibilité
// Chaque appel repart du même seed → comparaisons entre perturbations cohérentes
double MonteCarloPricer(const Option& option, int num_it, int num_step, unsigned int seed) {
    double S0          = option.get_s();
    double r           = option.get_r();
    double T           = option.get_T();
    double sigma       = option.get_sigma();
    double dt          = T / num_step;
    double drift       = (r - 0.5 * sigma * sigma) * dt;
    double vol_sqrt_dt = sigma * std::sqrt(dt);

    std::mt19937 generator(seed);  // repart toujours du même seed
    double total_payoff = 0.0;

    for (int i = 0; i < num_it; ++i) {
        double S = S0;
        std::vector<double> path;
        path.reserve(num_step + 1);
        path.push_back(S0);

        for (int t = 1; t <= num_step; ++t) {
            double z = gaussian_noise(generator);
            S = S * std::exp(drift + vol_sqrt_dt * z);
            path.push_back(S);
        }

        total_payoff += option.payoff(path);
    }

    return (total_payoff / num_it) * std::exp(-r * T);
}
