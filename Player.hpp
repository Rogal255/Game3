#pragma once

#include <SFML/Graphics.hpp>

class Player
{
	sf::Sprite m_Sprite;
	sf::Texture m_Texture;
	float m_Speed{ 10.f };

	// Private methods

public:
	Player();

	// Public methods
	void move(const float t_DirX, const float t_DirY);
	void update();
	void render(sf::RenderTarget* t_pTarget);
};
