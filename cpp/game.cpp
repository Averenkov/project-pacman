#include "game.hpp"
#include "levels.hpp"
#include "factory.cpp"

Game::Game(Level level): level(level), game_map(level) {
    texture.loadFromFile("pictures/title.png");
    plat = sf::Sprite(texture);
    textureWin.loadFromFile("pictures/youwin.png");
    youwin = sf::Sprite(textureWin);
    youwin.setPosition(CENTER.first, CENTER.second);
    textureLose.loadFromFile("pictures/youlose.png");
   	youlose = sf::Sprite(textureLose);
    youlose.setPosition(CENTER.first, CENTER.second);
	Factory.add<player>(_player);
	Factory.add<goast>(_goast);
	for (size_t i = 0; i < level.length; ++i) {
		for (size_t j = 0; j < level.width; ++j) {
			if (level.sheme[i][j] == pacman) {
				Player1 = static_cast<player*>(Factory.create(_player, {i, j}, &game_map));
			} else if (level.sheme[i][j] == evil) {
				evils.push_back(static_cast<goast*>(Factory.create(_goast, {i, j}, &game_map)));
			} else if (level.sheme[i][j] == loot) {
				++coins_cnt;
			}
		}
	}
}

void Game::start(sf::RenderWindow& window) {
	std::cout << "Количество жизней: " << Player1->get_lives() << std::endl;
	bool win = false;
	while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed) {

                if (event.key.code == sf::Keyboard::Right)
                    this->moveRight();
                if (event.key.code == sf::Keyboard::Left)
                    this->moveLeft();
                if (event.key.code == sf::Keyboard::Up)
                    this->moveUp();
                if (event.key.code == sf::Keyboard::Down)
                    this->moveDown();
            }

        }
        if (Player1->get_lives() > 0 && Player1->get_scores() < coins_cnt) {
        	this->update();
    	}
    	this->draw_map(window);
    }
}

void Game::moveUp() {
	Player1->set_route(Up);
}
void Game::moveDown() {
	Player1->set_route(Down);
}
void Game::moveRight() {
	Player1->set_route(Right);
}
void Game::moveLeft() {
	Player1->set_route(Left);
}

void Game::update() {
	Player1->set_time(Player1->get_time() + 1);
	if (Player1->get_frame() >= MAX_FRAME) {
		Player1->set_frame(0);
	} else {
		Player1->set_frame(Player1->get_frame() + UPDATE_FRAME);
	}
	if (Player1->get_time() == TIME_UPDATE) {
		int route = Player1->get_route() - 1;
		std::pair<int, int> pos = Player1->get_pos();
		std::pair<int, int> new_pos = {pos.first - Player1->dx[route], pos.second + Player1->dy[route]};
		new_pos.first = (new_pos.first + game_map.get_length()) % game_map.get_length();
		new_pos.second = (new_pos.second + game_map.get_width()) % game_map.get_width();
		if (game_map.get_symbol(new_pos) == empty) {
			Player1->set_pos(new_pos);
		}
		if (game_map.get_symbol(new_pos) == loot) {
			Player1->set_pos(new_pos);	
			game_map.set_symbol(new_pos, empty);
			Player1->set_scores(Player1->get_scores() + 1);
		}
		game_map.change_map_player(pos, Player1->get_pos());
		Player1->set_time(0);
		if (this->check_lose()) {
			Player1->set_lives(Player1->get_lives() - 1);
			std::cout << "Количество жизней: " << Player1->get_lives() << std::endl;
			this->restart_level_after_die();
		}
	}
}

void Game::draw_map(sf::RenderWindow& window) {
	window.clear(sf::Color::Black);

    for (size_t i = 0; i < game_map.get_length(); i++) {
        for (size_t j = 0; j < game_map.get_width(); j++) {
            if (game_map.get_symbol({i, j}) == brick)
                plat.setTextureRect(sf::IntRect(0, 0, ts, ts));
            if (game_map.get_symbol({i, j}) == pacman)
                plat.setTextureRect(sf::IntRect(ts * int(Player1->get_frame()), ts * Player1->get_route(), ts, ts));
            if (game_map.get_symbol({i, j}) == loot)
                plat.setTextureRect(sf::IntRect(ts, 0, ts, ts));
            if (game_map.get_symbol({i, j}) == evil)
                plat.setTextureRect(sf::IntRect(ts * 5, ts * 1, ts, ts));
            if (game_map.get_symbol({i, j}) == empty)
                continue;

            plat.setPosition(j * ts, i * ts);
            window.draw(plat);
        }
    }
    if (Player1->get_scores() == coins_cnt) {
    	window.draw(youwin);
    }
    if (Player1->get_lives() == 0) {
    	window.draw(youlose);
    }
    window.display();
}

bool Game::check_lose() {
	for (auto goast : evils) {
		if (goast->get_eatPlayer()) {
			return true;
		}
	}
	return false;
}

void Game::restart_level_after_die() {
	size_t ind_ghost = 0;
	for (size_t i = 0; i < level.length; ++i) {
		for (size_t j = 0; j < level.width; ++j) {
			if (level.sheme[i][j] == pacman) {
				Player1->set_pos({i, j});
				Player1->set_route(1);
			} else if (level.sheme[i][j] == evil) {
				game_map.set_symbol(evils[ind_ghost]->get_pos(), evils[ind_ghost]->get_under_goast());
				evils[ind_ghost]->set_pos({i, j});
				evils[ind_ghost]->set_under_goast(empty);
				evils[ind_ghost++]->reset_eatPlayer();
			}
			if (level.sheme[i][j] == loot && game_map.get_symbol({i, j}) != loot) {
				game_map.set_symbol({i, j}, empty);
			} else {
				game_map.set_symbol({i, j}, level.sheme[i][j]);
			}
		}
	}
}