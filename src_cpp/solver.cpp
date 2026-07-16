#include <cmath>
#include <random>
#include "solver.hpp"

// Fonction de répartition de la loi normale N(x)
double normalcumfunction(double x) {
    return 0.5 * (1.0 + std::erf(x / std::sqrt(2.0)));
}

double normaldensityfunction(double x){
    return (1.0 / std::sqrt(2.0 * M_PI)) * std::exp(-x * x / 2.0);
}

double gaussian_noise(double mu, double stddev){
    static std::mt19937 generator(42);
    static std::normal_distribution<double> distribution(mu, stddev);
    return distribution(generator);
}

double MonteCarloPricer(const Option& option, int num_it, int num_step) {
    double S0 = option.get_s();
    double r = option.get_r();
    double T = option.get_T();
    double sigma = option.get_sigma();

    double dt = T / num_step;
    double drift = (r - 1.0 / 2.0 * sigma * sigma) * dt;
    double vol_sqrt_dt = sigma * std::sqrt(dt);

    double payoff(0.0);

    for (int i(0); i < num_it; ++i) {

        double S = S0;

        std::vector<double> random_spot_vector;
        random_spot_vector.reserve(num_step + 1);
        random_spot_vector.push_back(S0);

        for (int t(1); t <= num_step; ++t) {
            double z = gaussian_noise(0.0, 1.0); 
            S = S * std::exp(drift + vol_sqrt_dt * z);
            random_spot_vector.push_back(S);
        }

        payoff += option.payoff(random_spot_vector);
    }

    double avg_payoff = payoff / num_it;

    return avg_payoff * std::exp(-r * T); 
}


