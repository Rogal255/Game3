#include "Enemy.hpp"

Enemy::Enemy(float t_PosX, float t_PosY)
{
	this->m_Shape.setRadius(static_cast<float>(rand()%50 + 50));
	this->m_Shape.setPointCount(rand() % 5 + 3);
	this->m_Shape.setPosition(t_PosX, t_PosY);
}

const sf::FloatRect Enemy::getBounds()
{
	return m_Shape.getGlobalBounds();
}

void Enemy::update()
{
	this->m_Shape.move(0.f, this->m_Speed);
}

void Enemy::render(sf::RenderTarget * t_pTarget)
{
	t_pTarget->draw(this->m_Shape);
}
