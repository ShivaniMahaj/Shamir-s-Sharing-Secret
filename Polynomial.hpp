#ifndef POLYNOMIAL_HPP
#define POLYNOMIAL_HPP

#include <vector>

class Polynomial {
private:
    std::vector<int> coefficients;

public:
    int evaluate(int x);
    void setCoefficients(const std::vector<int>& coefficients);
};

#endif POLYNOMIAL_HPP

