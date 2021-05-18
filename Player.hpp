#pragma once

#include <SFML/Graphics.hpp>

class Player
{
	sf::Sprite m_Sprite;
	float m_Speed{ 5.f };
	int m_HpMax{ 10 };
	int m_Hp{ m_HpMax };

public:
	Player();

	// Public methods
	const int& getHp() const;
	const int& getHpMax() const;
	void takeDamage(const int t_Damage);
	void setTexture(sf::Texture& t_Texture);
	void move(const float t_DirX, const float t_DirY);
	const sf::Vector2f getGunPosition() const;
	const sf::FloatRect getBounds() const;
	void update(sf::RenderTarget* t_pTarget);
	void render(sf::RenderTarget* t_pTarget);
};
