#include <iostream>
#include <SFML/Graphics.hpp>
#include <time.h>
#include "levels.hpp"
#include "game.cpp"

const int ts = 25;

int main() {
    Level l;
    srand(time(0));
    sf::RenderWindow window(sf::VideoMode(l.width * ts, l.length * ts), "PACMAN!");
    window.setFramerateLimit(60);

    Game g(l);
    g.start(window);
    return 0;
}