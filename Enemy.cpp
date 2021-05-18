#include "Enemy.hpp"

Enemy::Enemy(float t_PosX, float t_PosY, sf::Texture& t_Texture)
{
	this->m_Sprite.setTexture(t_Texture);
	this->m_Sprite.setPosition(t_PosX, t_PosY);
	this->m_Sprite.setOrigin(this->m_Sprite.getLocalBounds().width / 2, this->m_Sprite.getLocalBounds().height / 2);
	this->m_Rotation = static_cast<float>(rand() % 20 / 10.f) - 1.f;
}

const sf::FloatRect Enemy::getBounds()
{
	return m_Sprite.getGlobalBounds();
}

const uint16_t & Enemy::getPoints()
{
	return this->m_Points;
}

void Enemy::update()
{
	this->m_Sprite.move(0.f, this->m_Speed);
	this->m_Sprite.rotate(m_Rotation);
}

void Enemy::render(sf::RenderTarget * t_pTarget)
{
	t_pTarget->draw(this->m_Sprite);
}
