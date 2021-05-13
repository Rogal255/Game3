#include "Game.hpp"

Game::Game()
{
	// Setting up window
	this->m_Window.setFramerateLimit(144);
	this->m_Window.setVerticalSyncEnabled(false);

	// Setting up textures
	sf::Texture texture;
	m_Textures.emplace("Player", texture);
	m_Textures.emplace("Bullet", texture);
	m_Textures["Player"].loadFromFile("./Textures/ship.png");
	m_Textures["Bullet"].loadFromFile("./Textures/bullet.png");
	player.setTexture(m_Textures["Player"]);

	// GUI
	if (this->m_Font.loadFromFile("./fonts/font.ttf"))
	{
		std::cout << "Error loading font\n";
	}
	this->m_PointText.setFont(m_Font);
	this->m_PointText.setCharacterSize(20);
	this->m_PointText.setFillColor(sf::Color::White);
	this->m_PointText.setPosition(10.f, 10.f);
	this->m_PointText.setString("Points: 0");
}

Game::~Game()
{
}

void Game::updateBullets()
{
	// Fire bullets
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && this->m_GunCooldown.getElapsedTime().asMilliseconds() > 500)
	{
		m_GunCooldown.restart();
		sf::Vector2f shipGunPosition = player.getGunPosition();
		m_Bullets.emplace_back(this->m_Textures["Bullet"], 0.f, -1.f, 10.f, shipGunPosition.x, shipGunPosition.y);
	}

	// Delete out of screen bullets
	for (size_t i{ 0 }; i < this->m_Bullets.size(); ++i)
	{
		if (this->m_Bullets[i].getBounds().top + this->m_Bullets[i].getBounds().height < 0.f)
		{
			this->m_Bullets.erase(this->m_Bullets.begin() + i);
			--i;
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

void Game::updateEnemies()
{
	// Creating enemies
	if (this->m_EnemySpawnClock.getElapsedTime().asMilliseconds() > m_EnemySpawnCooldown)
	{
		this->m_EnemySpawnCooldown = rand() % 1500 + 500;
		this->m_EnemySpawnClock.restart();
		this->m_Enemies.emplace_back(static_cast<float>(rand() % m_Window.getSize().x), -200.f);
	}

	// Delete enemies
	for (size_t i{ 0 }; i < m_Enemies.size(); ++i)
	{	
		// Deleting out of screen enemies
		if (this->m_Enemies[i].getBounds().top > this->m_Window.getSize().y)
		{
			this->m_Enemies.erase(this->m_Enemies.begin() + i);
			--i;
			continue;
		}

		// Deleting hit enemies and bullets
		for (size_t j{ 0 }; j < m_Bullets.size(); ++j)
		{
			if (this->m_Enemies[i].getBounds().intersects(m_Bullets[j].getBounds()))
			{
				this->m_Enemies.erase(this->m_Enemies.begin() + i);
				this->m_Bullets.erase(this->m_Bullets.begin() + j);
				--i;
				break;
			}
		}
	}

	// Update enemies
	for (auto& enemy : m_Enemies)
	{
		enemy.update();
	}
}

void Game::renderEnemies()
{
	for (auto& enemy : m_Enemies)
	{
		enemy.render(&m_Window);
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

void Game::updateGUI()
{
}

void Game::renderGUI()
{
	this->m_Window.draw(m_PointText);
}

void Game::update()
{
	this->handleEvents();
	this->player.update();
	this->updateBullets();
	this->updateEnemies();
	this->updateGUI();
}

void Game::render()
{
	this->m_Window.clear();
	this->player.render(&m_Window);
	this->renderBullets();
	this->renderEnemies();
	this->renderGUI();
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
