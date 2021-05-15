#pragma once

#include <SFML/Graphics.hpp>

class Player
{
	sf::Sprite m_Sprite;
	float m_Speed{ 5.f };

public:
	Player();

	// Public methods
	void setTexture(sf::Texture& t_Texture);
	void move(const float t_DirX, const float t_DirY);
	const sf::Vector2f getGunPosition() const;
	const sf::FloatRect getBounds() const;
	void update(sf::RenderTarget* t_pTarget);
	void render(sf::RenderTarget* t_pTarget);
};
