#pragma once

#include <SFML/Graphics.hpp>
#include <array>
#include <iterator>

class Enemy
{
	sf::Sprite m_SpriteEnemy;
	int m_Type{ 0 };
	int m_HpMax{ 10 };
	int m_Hp{ m_HpMax };
	int m_Damage{ 1 };
	uint16_t m_Points{ 5 };
	float m_Speed{ 1.f };
	float m_Rotation{ 0.f };

	bool m_Hit{ false };
	sf::Sprite m_SpriteExplosion;
	std::array<sf::IntRect, 10> m_Frames;
	uint8_t m_CurrentFrame{ 0 };
	sf::Clock m_AnimationClock;


public:
	bool m_IsDead{ false };

	Enemy(float t_PosX, float t_PosY, sf::Texture& t_TextureEnemy, sf::Texture& t_TextureExplosion);
	const sf::FloatRect getBounds() const;
	const uint16_t& getPoints();
	void hit();
	void update();
	void render(sf::RenderTarget* t_pTarget);
};

