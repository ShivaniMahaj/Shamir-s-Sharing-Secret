#include "Share.hpp"

void Share::setShare(int x, int y) {
    this->x = x;
    this->y = y;
}

std::pair<int, int> Share::getShare() const {
    return { x, y };
}
