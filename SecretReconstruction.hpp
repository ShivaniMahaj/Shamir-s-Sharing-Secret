#ifndef SECRETRECONSTRUCTION_HPP
#define SECRETRECONSTRUCTION_HPP

#include <iostream>
#include <vector>
#include "Share.hpp"

class SecretReconstruction {
private:
    int threshold;

private:
    double lagrangeInterpolation(const  std::vector<Share>& shares);

public:
    SecretReconstruction(int threshold);
    int reconstructSecret(const std::vector<Share>& shares);
};

#endif SECRETRECONSTRUCTION_HPP


