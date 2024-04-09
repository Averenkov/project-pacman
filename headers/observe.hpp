#ifndef OBSERVE_HPP
#define OBSERVE_HPP

#include <set>
#include <vector>
#include <string>
#include <utility>
#include "levels.hpp"

class p_map;

const int INF = 1e9;

class observe {
public:
    virtual void update(std::pair<int, int> pos, p_map& mp) = 0;
};

class observable {
public:
    virtual void addObserver(observe* p) = 0;
    virtual void removeObserver(observe* p) = 0;
    virtual char get_symbol(std::pair<int, int> pos) const = 0;
    virtual void notify(std::pair<int, int> pos) = 0;
};

class p_map: public observable {
private:
    std::set<observe*> observers;
    Level sheme_map;
    std::vector<std::vector<std::pair<int, int>>> move;
    void bfs(int start, std::vector<int> &dist, std::vector<std::pair<int, int>> &move_g);
    void precalc_move_goast();
public:
    p_map() = delete;
    p_map(Level sheme_map): sheme_map(sheme_map) {
        precalc_move_goast();
    }
    void change_map_player(std::pair<int, int> start, std::pair<int, int> finish);
    char change_map_nps(std::pair<int, int> start, std::pair<int, int> finish, char c);
    void addObserver(observe* p);
    void removeObserver(observe* p);
    void notify(std::pair<int, int> pos);
    void set_symbol(std::pair<int, int> pos, char s);
    char get_symbol(std::pair<int, int> pos) const;
    size_t get_width() const;
    size_t get_length() const;
    std::pair<int, int> get_move(std::pair<int, int> pos_goast, std::pair<int, int> pos_player) const;
};

#endif