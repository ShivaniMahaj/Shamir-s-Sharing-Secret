#ifndef SECRETRECONSTRUCTION_HPP
#define SECRETRECONSTRUCTION_HPP

#include <vector>
#include "Share.hpp"
#include "Participant.hpp"

class SecretReconstruction {
private:
    std::vector<Share> shares;
    int threshold;
    //int reconstructedSecret;

public:
    SecretReconstruction(int threshold);
    void requestShare(Participant& participant);
    void receiveShare(Share& share);
    int lagrangeInterpolation(std::vector<Share>& shares);
    int reconstructSecret();
    bool validateReconstructedSecret(int secret);
    int getReconstructedSecret() const;
};

#endif SECRETRECONSTRUCTION_HPP


