#include "Dealer.hpp"
#include <cstdlib>

Dealer::Dealer() : secret(0) {}

int Dealer::generateSecret(int secretInput) {
    secret = secretInput;
    return secret;
}

Polynomial Dealer::choosePolynomial(int thresholdNumber) {
    std::vector<int> coeffs(thresholdNumber);
    coeffs[0] = secret;
    for (int i = 1; i < thresholdNumber; ++i) {
        coeffs[i] = rand() % 100;
    }
    polynomial.setCoefficients(coeffs);
    return polynomial;
}

std::vector<Share> Dealer::calculateShares(int numberOfShares, int thresholdNumber) {
    std::vector<Share> shares;
    for (int i = 1; i <= numberOfShares; ++i) {
        int x = i;
        int y = polynomial.evaluate(x);
        Share share;
        share.setShare(x, y);
        shares.push_back(share);
    }
    return shares;
}

void Dealer::sendShare(Participant& participant, Share& share) {
    participant.receiveShare(share);
}

bool Dealer::verifySecret(int reconstructedSecret) {
    return reconstructedSecret == secret;
}
