#include "observe.hpp"
#include "player.hpp"
#include "goasts.hpp"
#include "factory.hpp"
#include "levels.hpp"
#include <SFML/Graphics.hpp>


enum characters_id
{
    _player,
    _goast
};

enum route
{
    Right = 1,
    Left = 2,
    Up = 3,
    Down = 4
};

const std::pair<int, int> CENTER = {100, 210};
const int TIME_UPDATE = 10;
const int MAX_FRAME = 4;
const double UPDATE_FRAME = 0.2;

class Game {
private:
    const int ts = 25; // размер квадрата
    p_map game_map;
    Level level;
    int coins_cnt = 0;
    characterFactory Factory;
    std::vector<goast*> evils;
    player* Player1;
    sf::Texture texture;
    sf::Sprite plat;
    sf::Texture textureWin;
    sf::Sprite youwin;
    sf::Texture textureLose;
    sf::Sprite youlose;
public:
    Game(Level level);
    void start(sf::RenderWindow& window);
    void moveUp();
    void moveDown();
    void moveRight();
    void moveLeft();
    void update();
    void draw_map(sf::RenderWindow& window);
    bool check_lose();
    void restart_level_after_die();
};