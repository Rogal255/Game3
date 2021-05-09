#pragma once

#include <SFML/Graphics.hpp>

class Enemy
{
	sf::CircleShape m_Shape;
	int m_Type{ 0 };
	int m_HpMax{ 10 };
	int m_Hp{ m_HpMax };
	int m_Damage{ 1 };
	int m_Points{ 5 };
	float m_Speed{ 1.f };

public:
	Enemy(float t_PosX, float t_PosY);
	const sf::FloatRect getBounds();
	void update();
	void render(sf::RenderTarget* t_pTarget);
};

