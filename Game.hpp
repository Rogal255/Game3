#pragma once

#include "Player.hpp"

class Game
{
	sf::ContextSettings m_Settings{ 0U, 0U, 16U, 1U, 1U, 0U, false };
	sf::RenderWindow m_Window{ sf::VideoMode(1200, 900), "Game 3", sf::Style::Close | sf::Style::Titlebar, m_Settings};
	sf::Event m_Event;
	Player player;

	// Private methods
	void handleEvents();
	void update();
	void render();

public:
	Game();
	~Game();

	// Public methods
	void run();
};

