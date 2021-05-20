#include "Bullet.hpp"

Bullet::Bullet(sf::Texture& t_Texture, float t_DirX, float t_DirY, float t_Speed, float t_PosX, float t_PosY) : m_Speed{t_Speed}
{
	this->m_Direction.x = t_DirX;
	this->m_Direction.y = t_DirY;
	this->m_Sprite.setTexture(t_Texture);
	m_Frames[0] = sf::IntRect(0, 0, 13, 76);
	m_Frames[1] = sf::IntRect(23, 0, 13, 76);
	m_Frames[2] = sf::IntRect(46, 0, 13, 76);
	this->m_Sprite.setTextureRect(m_Frames[0]);
	this->m_Sprite.setPosition(t_PosX, t_PosY);
}

const sf::FloatRect Bullet::getBounds()
{
	return this->m_Sprite.getGlobalBounds();
}

void Bullet::update()
{
	if (this->m_AnimationClock.getElapsedTime().asMilliseconds() > 100)
	{
		this->m_AnimationClock.restart();

		switch (this->m_CurrentFrame)
		{
		case 0:
			this->m_Sprite.setTextureRect(m_Frames[1]);
			this->m_CurrentFrame = 1;
			this->m_CurrentAnimationDirection = forward;
			break;
		case 1:
			if (this->m_CurrentAnimationDirection == forward)
			{
				this->m_Sprite.setTextureRect(m_Frames[2]);
				this->m_CurrentFrame = 2;
			}
			else
			{
				this->m_Sprite.setTextureRect(m_Frames[0]);
				this->m_CurrentFrame = 0;
			}
			break;
		case 2:
			this->m_Sprite.setTextureRect(m_Frames[1]);
			this->m_CurrentFrame = 1;
			this->m_CurrentAnimationDirection = backward;
			break;
		}
	}

	this->m_Sprite.move(this->m_Speed * this->m_Direction);
}

void Bullet::render(sf::RenderTarget* t_pTarget)
{
	t_pTarget->draw(this->m_Sprite);
}
