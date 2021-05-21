#include "Enemy.hpp"
#include <iostream>

Enemy::Enemy(float t_PosX, float t_PosY, sf::Texture& t_TextureEnemy, sf::Texture& t_TextureExplosion)
{
	this->m_SpriteEnemy.setTexture(t_TextureEnemy);
	this->m_SpriteEnemy.setOrigin(this->m_SpriteEnemy.getLocalBounds().width / 2, this->m_SpriteEnemy.getLocalBounds().height / 2);
	this->m_SpriteEnemy.setPosition(t_PosX, t_PosY);
	this->m_Rotation = static_cast<float>(rand() % 20 / 10.f) - 1.f;

	// Explosion Animation Setup
	this->m_Frames.at(0) = sf::IntRect(0, 0, 128, 128);
	this->m_Frames.at(1) = sf::IntRect(138, 0, 128, 128);
	this->m_Frames.at(2) = sf::IntRect(276, 0, 128, 128);
	this->m_Frames.at(3) = sf::IntRect(414, 0, 128, 128);
	this->m_Frames.at(4) = sf::IntRect(552, 0, 128, 128);
	this->m_Frames.at(5) = sf::IntRect(690, 0, 128, 128);
	this->m_Frames.at(6) = sf::IntRect(828, 0, 128, 128);
	this->m_Frames.at(7) = sf::IntRect(966, 0, 128, 128);
	this->m_Frames.at(8) = sf::IntRect(1104, 0, 128, 128);
	this->m_Frames.at(9) = sf::IntRect(1242, 0, 128, 128);
	this->m_ItAnimation = m_Frames.begin();
	this->m_SpriteExplosion.setTexture(t_TextureExplosion);
	this->m_SpriteExplosion.setTextureRect(*this->m_ItAnimation);
}

const sf::FloatRect Enemy::getBounds() const
{
	if (!m_Hit)
	{
		sf::FloatRect globalBounds = m_SpriteEnemy.getGlobalBounds();
		return sf::FloatRect(globalBounds.left + 23.f, globalBounds.top, globalBounds.width - 46.f, globalBounds.height - 23.f);
	}

	return sf::FloatRect(0.f, 0.f, 0.f, 0.f);
}

const uint16_t & Enemy::getPoints()
{
	return this->m_Points;
}

void Enemy::hit()
{
	this->m_Hit = true;
	this->m_SpriteExplosion.setPosition(this->m_SpriteEnemy.getPosition());
}

void Enemy::update()
{
	if (!m_Hit)
	{
		this->m_SpriteEnemy.move(0.f, this->m_Speed);
		this->m_SpriteEnemy.rotate(m_Rotation);
	}
	else
	{
		if (this->m_ItAnimation == this->m_Frames.begin() + 10)
		{
			this->m_IsDead = true;
			std::cout << "dead\n";
		}
		else if (this->m_AnimationClock.getElapsedTime().asMilliseconds() > 100)
		{
			this->m_AnimationClock.restart();
			this->m_SpriteExplosion.setTextureRect(*this->m_ItAnimation++);
			std::cout << m_ItAnimation->left << " != " << m_Frames.end()->left << "\n";
		}
	}
}

void Enemy::render(sf::RenderTarget * t_pTarget)
{
	if (!m_Hit)
	{
		t_pTarget->draw(this->m_SpriteEnemy);
	}
	else
	{
		t_pTarget->draw(this->m_SpriteExplosion);
	}
}
