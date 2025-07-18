#ifndef DEALER_HPP
#define DEALER_HPP

#include <vector>
#include "Share.hpp"
#include "Polynomial.hpp"
#include "Participant.hpp"

class Dealer {
private:
    int secret = 0;
    std::vector<int> coefficients;
    Polynomial polynomial;

public:
    Dealer();
    int generateSecret(int secretInput);
    Polynomial choosePolynomial(int thresholdNumber);
    std::vector<Share> calculateShares(int numberOfShares, int thresholdNumber);
    void sendShare(Participant& participant, Share& share);
    bool verifySecret(int reconstructedSecret);
};

#endif DEALER_HPP


