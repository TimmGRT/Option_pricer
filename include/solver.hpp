#pragma once
#include "option.hpp"

double normalcumfunction(double x);
double normaldensityfunction(double x);
double gaussian_noise(double mu, double stddev);

double MonteCarloPricer(const Option& option, int num_it, int num_step);
