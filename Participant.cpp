#include "Participant.hpp"

void Participant::receiveShare(const Share& share) {
    shares.push_back(share);  
}

Share Participant::provideShare(int index) const {
    if (index < 0 || static_cast<size_t>(index) >= shares.size()) { 
        throw std::out_of_range("Invalid share index.");
    }
    return shares[index];
}

std::vector<Share> Participant::provideAllShares() const {
    return shares; 
}


