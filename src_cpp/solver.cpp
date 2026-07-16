#include <cmath>
#include <functional>
#include "solver.hpp"

// Fonction de répartition de la loi normale N(x)
double normalcumfunction(double x) {
    return 0.5 * (1.0 + std::erf(x / std::sqrt(2.0)));
}

double normaldensityfunction(double x){
    return (1.0 / std::sqrt(2.0 * M_PI)) * std::exp(-x * x / 2.0);
}
