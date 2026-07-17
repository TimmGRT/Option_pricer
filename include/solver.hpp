#pragma once
#include <random>
#include "option.hpp"

double normalcumfunction(double x);
double normaldensityfunction(double x);
double gaussian_noise(std::mt19937& generator);

// seed=42 par défaut → résultats reproductibles
// seed fixe garanti que V(S+dS) et V(S-dS) sont comparables pour les diff. finies
double MonteCarloPricer(const Option& option, int num_it, int num_step, unsigned int seed = 42);
