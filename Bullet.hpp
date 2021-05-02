#pragma once

#include<SFML/Graphics.hpp>

class Bullet
{
	sf::Sprite m_Sprite;
	sf::Vector2f m_Direction;
	float m_Speed;
public:
	Bullet(sf::Texture& t_Texture, float t_DirX, float t_DirY, float t_Speed, float t_PosX, float t_PosY);

	const sf::FloatRect getBounds();
	void update();
	void render(sf::RenderTarget* t_pTarget);
};
