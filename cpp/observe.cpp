#include "observe.hpp"
#include "goasts.hpp"
#include <algorithm>
#include <deque>

void p_map::bfs(int start, std::vector<int> &dist, std::vector<std::pair<int, int>> &move_g) {
    std::deque<int> d;
    d.push_back(start);
    dist[start] = 0;
    int dx[4] = {-1, 1, 0, 0};
    int dy[4] = {0, 0, -1, 1};
    while (!d.empty()) {
        auto t = d.front();
        d.pop_front();
        for (size_t i = 0; i < 4; ++i) {
            int x = t % sheme_map.width;
            int y = t / sheme_map.width;
            int new_x = (x + dx[i] + sheme_map.width) % sheme_map.width;
            int new_y = (y + dy[i] + sheme_map.length) % sheme_map.length;
            int new_t = new_y * sheme_map.width + new_x;
            if (sheme_map.sheme[new_t / sheme_map.width][new_t % sheme_map.width] == brick) {
                continue;
            }
            if (dist[t] + 1 < dist[new_t]) {
                dist[new_t] = dist[t] + 1;
                d.push_back(new_t);
                move_g[new_t] = {t / sheme_map.width, t % sheme_map.width};
            }
        }
    }
}
void p_map::precalc_move_goast() {
    std::vector<std::vector<int>> dist;
    move.resize(sheme_map.length * sheme_map.width);
    dist.resize(sheme_map.length * sheme_map.width);
    for (size_t i = 0; i < sheme_map.length * sheme_map.width; ++i) {
        move[i].assign(sheme_map.length * sheme_map.width, {0, 0});
        dist[i].assign(sheme_map.length * sheme_map.width, INF);
        if (sheme_map.sheme[i / sheme_map.width][i % sheme_map.width] == brick) {
            continue;
        }
        bfs(i, dist[i], move[i]);
    }
}

std::pair<int, int> p_map::get_move(std::pair<int, int> pos_goast, std::pair<int, int> pos_player) const {
    return move[pos_player.first * sheme_map.width + pos_player.second][pos_goast.first * sheme_map.width + pos_goast.second];
}

void p_map::addObserver(observe* p) {
    p_map::observers.insert(p);
}

void p_map::removeObserver(observe* p) {
    p_map::observers.erase(p);
}

void p_map::notify(std::pair<int, int> pos) {
    for (auto o : p_map::observers) {
        o->update(pos, *this);
    }
}

void p_map::change_map_player(std::pair<int, int> start, std::pair<int, int> finish) {
    std::swap(sheme_map.sheme[start.first][start.second], sheme_map.sheme[finish.first][finish.second]);
    p_map::notify(finish);
}

char p_map::change_map_nps(std::pair<int, int> start, std::pair<int, int> finish, char c) {
    char ans = sheme_map.sheme[finish.first][finish.second];
    sheme_map.sheme[finish.first][finish.second] = sheme_map.sheme[start.first][start.second];
    sheme_map.sheme[start.first][start.second] = c;
    return ans;
}

void p_map::set_symbol(std::pair<int, int> pos, char s) {
    p_map::sheme_map.sheme[pos.first][pos.second] = s;
}

char p_map::get_symbol(std::pair<int, int> pos) const {
    return p_map::sheme_map.sheme[pos.first][pos.second];
}

size_t p_map::get_width() const {
    return sheme_map.width;
}

size_t p_map::get_length() const {
    return sheme_map.length;
}