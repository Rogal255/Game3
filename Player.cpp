#include "Player.hpp"

void Player::initTexture()
{
	// Load texture here
}

void Player::initSprite()
{
	this->m_Sprite.setTexture(this->m_Texture);
}

Player::Player()
{
	this->initTexture();
	this->initSprite();
}

Player::~Player()
{
}

void Player::update()
{
}

void Player::render(sf::RenderTarget* t_pTarget)
{
	t_pTarget->draw(this->m_Sprite);
}
