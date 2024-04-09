#ifndef CHARACTER_HPP
#define CHARACTER_HPP
#include <utility>
#include "observe.hpp"

class character {
public:
    const int dx[4] = {0, 0, 1, -1};
    const int dy[4] = {1, -1, 0, 0};
protected:
    std::pair<int, int> pos;
    int route = 1; //состояние
public:
    character() = default;
    character(std::pair<int, int> pos): pos(pos) {};
    void set_pos(std::pair<int, int> pos);
    std::pair<int, int> get_pos();
    void set_route(int route);
    int get_route();
};

#endif