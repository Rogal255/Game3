#pragma once

#include <SFML/Graphics.hpp>
#include <array>

class Bullet
{
	sf::Sprite m_Sprite;
	sf::Vector2f m_Direction;
	float m_Speed;
	sf::Clock m_AnimationClock;
	std::array<sf::IntRect, 3> m_Frames;
	sf::IntRect m_FirstFrame{ 0, 0, 13, 76 };
	uint8_t m_CurrentFrame{ 0 };
	enum m_AnimationDirectionEnum{ forward, backward };
	uint8_t m_CurrentAnimationDirection{ forward };

public:
	Bullet(sf::Texture& t_Texture, float t_DirX, float t_DirY, float t_Speed, float t_PosX, float t_PosY);

	const sf::FloatRect getBounds();
	void update();
	void render(sf::RenderTarget* t_pTarget);
};
