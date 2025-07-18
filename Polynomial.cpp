#include "Polynomial.hpp"
#include <cmath>

int Polynomial::evaluate(int x) {
    int result = 0;
    for (int i = 0; i < coefficients.size(); ++i) {
        result += coefficients[i] * std::pow(x, i);
    }
    return result;
}

void Polynomial::setCoefficients(const std::vector<int>& coefficients) {
    this->coefficients = coefficients;
}

