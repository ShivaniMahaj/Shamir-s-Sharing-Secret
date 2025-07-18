#include "SecretReconstruction.hpp"
#include <iostream>

SecretReconstruction::SecretReconstruction(int threshold) : threshold(threshold), reconstructedSecret(0) {
}

void SecretReconstruction::requestShare(Participant& participant) {
    Share share = participant.provideShare(0);
    receiveShare(share);
}

void SecretReconstruction::receiveShare(Share& share) {
    shares.push_back(share);
}

int SecretReconstruction::lagrangeInterpolation(std::vector<Share>& shares) {
    int secret = 0;
    int n = shares.size();

    for (int i = 0; i < n; ++i) {
        int xi = shares[i].getShare().first;
        int yi = shares[i].getShare().second;

        int numerator = 1;
        int denominator = 1;

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

int SecretReconstruction::reconstructSecret() {
    int reconstructedSecret = lagrangeInterpolation(shares);
    return reconstructedSecret;
}

//bool SecretReconstruction::validateReconstructedSecret(int secret) {
//    return reconstructedSecret == secret;
//}

int SecretReconstruction::getReconstructedSecret() const {
    //return reconstructedSecret;
}
