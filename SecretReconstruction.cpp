#include "SecretReconstruction.hpp"


SecretReconstruction::SecretReconstruction(int threshold) : threshold(threshold) {
}


double SecretReconstruction::lagrangeInterpolation(const  std::vector<Share>& shares) {
    double  secret = 0.0;
    int n = shares.size();

    for (int i = 0; i < n; ++i) {
        int xi = shares[i].getShare().first;
        int yi = shares[i].getShare().second;

        double numerator = 1.0;
        double denominator = 1.0;

        for (int j = 0; j < n; ++j) {
            if (i != j) {
                int xj = shares[j].getShare().first;
                numerator *= (0.0 - xj); 
                denominator *= (xi - xj);
            }
        }

        secret += yi * (numerator / denominator);
    }

    return secret;
}


int SecretReconstruction::reconstructSecret(const std::vector<Share>& shares) {
    double reconstructedSecret = lagrangeInterpolation(shares);
    return static_cast<int>(std::round(reconstructedSecret));
}
