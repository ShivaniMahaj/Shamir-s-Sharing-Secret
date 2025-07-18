#ifndef SHARE_HPP
#define SHARE_HPP

#include <utility>

class Share {
private:
    int x;
    int y;

public:
    void setShare(int x, int y);
    std::pair<int, int> getShare() const;
};

#endif SHARE_HPP


