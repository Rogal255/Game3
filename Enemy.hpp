#pragma once

#include <SFML/Graphics.hpp>

class Game;

class Enemy
{
	sf::Sprite m_Sprite;
	int m_Type{ 0 };
	int m_HpMax{ 10 };
	int m_Hp{ m_HpMax };
	int m_Damage{ 1 };
	uint16_t m_Points{ 5 };
	float m_Speed{ 1.f };
	float m_Rotation{ 0.f };

public:
	Enemy(float t_PosX, float t_PosY, sf::Texture& t_Texture);
	const sf::FloatRect getBounds() const;
	const uint16_t& getPoints();
	void update();
	void render(sf::RenderTarget* t_pTarget);
};

