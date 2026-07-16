#pragma once
#include <functional>

double normalcumfunction(double x);
double Newtonraphson(const std::function<double(double)>& f, const std::function<double(double)>& df, double x0, double tolerance, int n_max_it);
