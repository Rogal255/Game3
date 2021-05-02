#include "Game.hpp"

Game::Game()
{
	// Setting up window
	//this->m_Window.setFramerateLimit(144);
	this->m_Window.setVerticalSyncEnabled(false);

	// Setting up textures
	sf::Texture texture;
	m_Textures.emplace("Player", texture);
	m_Textures.emplace("Bullet", texture);
	m_Textures["Player"].loadFromFile("./Textures/ship.png");
	m_Textures["Bullet"].loadFromFile("./Textures/bullet.png");
	player.setTexture(m_Textures["Player"]);
}

Game::~Game()
{
}

void Game::updateBullets()
{
	// Fire bullets
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && m_GunCooldown.getElapsedTime().asMilliseconds() > 500)
	{
		m_GunCooldown.restart();
		sf::Vector2f shipGunPosition = player.getGunPosition();
		m_Bullets.emplace_back(m_Textures["Bullet"], 0.f, -1.f, 10.f, shipGunPosition.x, shipGunPosition.y);
	}

	for (size_t i{ 0 }; i < m_Bullets.size(); i++)
	{
		if (m_Bullets[i].getBounds().top < 0)
		{
			m_Bullets.erase(m_Bullets.cbegin() + i);
		}
	}

	// Update bullets
	for (auto& bullet : this->m_Bullets)
	{
		bullet.update();
	}
}

void Game::renderBullets()
{
	for (auto& bullet : m_Bullets)
	{
		bullet.render(&m_Window);
	}
}

void Game::handleEvents()
{
	while (this->m_Window.pollEvent(this->m_Event))
	{
		switch (this->m_Event.type)
		{
		case sf::Event::Closed:
			this->m_Window.close();
			break;
		case sf::Event::KeyPressed:
			if (this->m_Event.key.code == sf::Keyboard::Escape)
			{
				this->m_Window.close();
			}
			break;
		}
	}
}

void Game::update()
{
	this->handleEvents();
	this->player.update();
	this->updateBullets();
}

void Game::render()
{
	this->m_Window.clear();
	player.render(&m_Window);
	renderBullets();
	this->m_Window.display();
}

void Game::run()
{
	while (this->m_Window.isOpen())
	{
		this->update();
		this->render();
	}
}
