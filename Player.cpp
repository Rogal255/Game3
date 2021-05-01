#include "Player.hpp"

Player::Player()
{
	// init texture
	this->m_Texture.loadFromFile("./Textures/ship.png");

	//init sprite
	this->m_Sprite.setTexture(this->m_Texture);
	this->m_Sprite.setPosition(300.f, 300.f);
	this->m_Sprite.setScale(0.15f, 0.15f);
}

void Player::move(const float t_DirX, const float t_DirY)
{
	this->m_Sprite.move(this->m_Speed * t_DirX, this->m_Speed * t_DirY);
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
