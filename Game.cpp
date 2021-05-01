#include "Game.hpp"

Game::Game()
{
	this->m_Window.setFramerateLimit(144);
	this->m_Window.setVerticalSyncEnabled(false);
}

Game::~Game()
{
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
}

void Game::render()
{
	this->m_Window.clear();
	player.render(&m_Window);
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
