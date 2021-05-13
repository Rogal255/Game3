#include "Player.hpp"

Player::Player()
{
}

void Player::setTexture(sf::Texture& t_Texture)
{
	this->m_Sprite.setTexture(t_Texture);
	this->m_Sprite.setPosition(300.f, 300.f);
	this->m_Sprite.setScale(0.15f, 0.15f);
}

void Player::move(const float t_DirX, const float t_DirY)
{
	this->m_Sprite.move(this->m_Speed * t_DirX, this->m_Speed * t_DirY);
}

const sf::Vector2f Player::getGunPosition() const
{
	sf::Vector2f position{ m_Sprite.getPosition() };
	position.x += m_Sprite.getGlobalBounds().width / 2.f - 5.f;
	return position;
}

const sf::FloatRect Player::getBounds() const
{
	return this->m_Sprite.getGlobalBounds();
}

void Player::update()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		this->move(0.f, -1.f);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		this->move(0.f, 1.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		this->move(-1.f, 0.f);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		this->move(1.f, 0.f);
	}
}

void Player::render(sf::RenderTarget* t_pTarget)
{
	t_pTarget->draw(this->m_Sprite);
}
