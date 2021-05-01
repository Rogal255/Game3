#pragma once

#include <SFML/Graphics.hpp>

class Player
{

public:
	Player();
	~Player();

	// Public methods
	void update();
	void render(sf::RenderTarget* t_pTarget);
};

