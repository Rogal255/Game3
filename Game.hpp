#pragma once

#include "Player.hpp"
#include "Bullet.hpp"
#include <map>

class Game
{
	sf::ContextSettings m_Settings{ 0U, 0U, 16U, 1U, 1U, 0U, false };
	sf::RenderWindow m_Window{ sf::VideoMode(1200, 900), "Game 3", sf::Style::Close | sf::Style::Titlebar, m_Settings };
	sf::Event m_Event;
	sf::Clock m_GunCooldown;

	// Resources
	Player player;
	std::vector<Bullet> m_Bullets;
	std::map<std::string, sf::Texture> m_Textures;

	// Private methods
	void updateBullets();
	void renderBullets();
	void handleEvents();
	void update();
	void render();

public:
	Game();
	~Game();

	// Public methods
	void run();
};
