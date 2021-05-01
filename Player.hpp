#pragma once

#include <SFML/Graphics.hpp>

class Player
{
	sf::Sprite m_Sprite;
	sf::Texture m_Texture;

	// Private methods
	void initTexture();
	void initSprite();

public:
	Player();
	~Player();

	// Public methods
	void update();
	void render(sf::RenderTarget* t_pTarget);
};

