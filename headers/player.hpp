#ifndef PLAYER_HPP
#define PLAYER_HPP
#include "observe.hpp"
#include "character.hpp"

class player: public character, public observe {
private:
    int lives = 3;
    int score = 0;
    int time = 0;
    double frame = 0;
public:
    player() = default;
    player(std::pair<int, int> pos, observable* map): character(pos) {};
    int get_lives();
    void set_lives(int lives);
    int get_scores();
    void set_scores(int score);
    void update(std::pair<int, int> pos, p_map& mp) {}
    int get_time();
    void set_time(int t);
    double get_frame();
    void set_frame(double f);
};

#endif