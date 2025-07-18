#ifndef PARTICIPANT_HPP
#define PARTICIPANT_HPP

#include "Share.hpp"
#include <vector>
#include <stdexcept>

class Participant {
public:
    void receiveShare(const Share& share);  
    Share provideShare(int index) const;  
    std::vector<Share> provideAllShares() const;

private:
    std::vector<Share> shares;
};

#endif PARTICIPANT_HPP


