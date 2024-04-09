#ifndef GOASTS_HPP
#define GOASTS_HPP

#include "character.hpp"
#include "observe.hpp"

class goast: public character, public observe {
private:
    int time = 0;
    char under_goast = empty;
    bool eatPlayer = false;
public:
    goast(std::pair<int, int> pos, observable* map): character(pos) {
        map->addObserver(this);
    }
    void update(std::pair<int, int> pl_pos, p_map& mp);
    char get_under_goast() const;
    void set_under_goast(char c);
    bool get_eatPlayer();
    void reset_eatPlayer();
};

#endif