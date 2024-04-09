#include "character.hpp"
#include "goasts.hpp"
#include "player.hpp"
#include "observe.hpp"
#include <random>
#include <algorithm>

void character::set_pos(std::pair<int, int> pos) {
    character::pos = pos;
}

std::pair<int, int> character::get_pos() {
    return character::pos;
}

void character::set_route(int route) {
    character::route = route;
}

int character::get_route() {
    return character::route;
}

void player::set_lives(int lives) {
    player::lives = lives;
}

int player::get_lives() {
    return player::lives;
}

void player::set_scores(int score) {
    player::score = score;
}

int player::get_scores() {
    return player::score;
}

void player::set_time(int t) {
    time = t;
}

int player::get_time() {
    return time;
}

void player::set_frame(double f) {
    frame = f;
}

double player::get_frame() {
    return frame;
}

char goast::get_under_goast() const {
    return under_goast;
}

void goast::set_under_goast(char c) {
    under_goast = c;
}

void goast::update(std::pair<int, int> pl_pos, p_map& mp) {
    ++time;
    if (time == 2) { // в два раза медленее пакмана
        time = 0;
        return;
    }
    std::pair<int, int> g_new_pos = mp.get_move(pos, pl_pos);
    if (mp.get_symbol(g_new_pos) == evil) {
        return;
    }
    if (mp.get_symbol(g_new_pos) == pacman) {
        eatPlayer = true;
        return;
    }
    under_goast = mp.change_map_nps(pos, g_new_pos, under_goast);
    pos = g_new_pos;
}

bool goast::get_eatPlayer() {
    return eatPlayer;
}

void goast::reset_eatPlayer() {
    eatPlayer = false;
}