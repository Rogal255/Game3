#include "Bullet.hpp"

Bullet::Bullet(sf::Texture& t_Texture, float t_DirX, float t_DirY, float t_Speed, float t_PosX, float t_PosY) : m_Speed{t_Speed}
{
	this->m_Direction.x = t_DirX;
	this->m_Direction.y = t_DirY;
	this->m_Sprite.setTexture(t_Texture);
	this->m_Sprite.setPosition(t_PosX, t_PosY);
	this->m_Sprite.setScale(0.1f, 0.1f);
}

const sf::FloatRect Bullet::getBounds()
{
	return this->m_Sprite.getGlobalBounds();
}

void Bullet::update()
{
	this->m_Sprite.move(this->m_Speed * this->m_Direction);
}

void Bullet::render(sf::RenderTarget* t_pTarget)
{
	t_pTarget->draw(this->m_Sprite);
}
