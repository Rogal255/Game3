#pragma once

#include <SFML/Graphics.hpp>

class Game
{
	sf::RenderWindow m_Window{ sf::VideoMode(800, 600), "Game 3", sf::Style::Close | sf::Style::Titlebar };
	sf::Event m_Event;

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

