#include <cmath>
#include <functional>
#include "solver.hpp"

// Fonction de répartition de la loi normale N(x)
double normalcumfunction(double x) {
    return 0.5 * (1.0 + std::erf(x / std::sqrt(2.0)));
}

// Solveur Newton-Raphson
double Newtonraphson(const std::function<double(double)>& f, const std::function<double(double)>& df, double x0, double tolerance, int n_max_it) {
    double x = x0;

    for (int i = 0; i < n_max_it; ++i) {
        double y  = f(x);
        double dy = df(x);

        if (std::abs(dy) == 0) {
            break;
        }

        double ratio = y / dy;
        x = x - ratio;

        if (std::abs(ratio) < tolerance) {
            return x;
        }
    }

    return x;
}
