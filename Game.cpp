#include "Game.hpp"

Game::Game()
{
	// Setting up window
	this->m_Window.setFramerateLimit(144);
	this->m_Window.setVerticalSyncEnabled(false);

	// Setting up textures
	sf::Texture texture;
	m_Textures.emplace("Player", texture);
	m_Textures.emplace("Asteroid", texture);
	m_Textures.emplace("Missle", texture);
	m_Textures.emplace("Background", texture);
	m_Textures["Player"].loadFromFile("./Textures/ship.png");
	m_Textures["Asteroid"].loadFromFile("./Textures/asteroid.png");
	m_Textures["Missle"].loadFromFile("./Textures/missle.png");
	m_Textures["Background"].loadFromFile("./Textures/background.jpg");
	m_Player.setTexture(m_Textures["Player"]);

	// GUI
	if (!this->m_Font.loadFromFile("./fonts/font.ttf"))
	{
		std::cout << "Error loading font\n";
	}
	this->m_PointText.setFont(m_Font);
	this->m_PointText.setCharacterSize(20);
	this->m_PointText.setFillColor(sf::Color::White);
	this->m_PointText.setPosition(10.f, 10.f);
	this->m_PointText.setString("Points: 0");
	this->m_PointText.setFillColor(sf::Color::White);
	this->m_GameOverText.setFont(m_Font);
	this->m_GameOverText.setCharacterSize(100);
	this->m_GameOverText.setString("GAME OVER");
	this->m_GameOverText.setPosition(
		(this->m_Window.getSize().x / 2.f - this->m_GameOverText.getGlobalBounds().width / 2.f),
		(this->m_Window.getSize().y / 2.f - this->m_GameOverText.getGlobalBounds().height / 2.f));
	this->m_PlayerHpBar.setSize(sf::Vector2f(30.f, 25.f));
	this->m_PlayerHpBar.setFillColor(sf::Color::Red);
	this->m_PlayerHpBar.setPosition(10.f, 40.f);
	this->m_PlayerHpBarBack = this->m_PlayerHpBar;
	this->m_PlayerHpBarBack.setFillColor(sf::Color(25, 25, 25, 200));

	// World
	this->m_WorldBackground.setTexture(this->m_Textures["Background"]);
}

Game::~Game()
{
}

void Game::renderWorld()
{
	this->m_Window.draw(this->m_WorldBackground);
}

void Game::updateBullets()
{
	// Fire bullets
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && this->m_GunCooldown.getElapsedTime().asMilliseconds() > 500)
	{
		m_GunCooldown.restart();
		sf::Vector2f shipGunPosition = m_Player.getGunPosition();
		m_Bullets.emplace_back(this->m_Textures["Missle"], 0.f, -1.f, 1.f, shipGunPosition.x, shipGunPosition.y);
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
		do {
			this->m_NewEnemyPosX = static_cast<float>(rand() % (m_Window.getSize().x - 200)) + 100.f;
		} while (this->m_NewEnemyPosX < this->m_LastEnemyPosX + 100.f && this->m_NewEnemyPosX > this->m_LastEnemyPosX - 100.f);
		this->m_Enemies.emplace_back(this->m_NewEnemyPosX, -200.f, m_Textures["Asteroid"]);
		this->m_LastEnemyPosX = this->m_NewEnemyPosX;
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

		// Detecting collisions with the player
		if (this->m_Player.getBounds().intersects(this->m_Enemies[i].getBounds()))
		{
			this->m_Player.takeDamage(1);
			if (this->m_Points == 65535)
			{
				this->m_Points = 0;
			}

			this->m_Enemies.erase(this->m_Enemies.begin() + i);
			--i;
			continue;
		}

		// Deleting hit enemies and bullets
		for (size_t j{ 0 }; j < m_Bullets.size(); ++j)
		{
			if (this->m_Enemies[i].getBounds().intersects(m_Bullets[j].getBounds()))
			{
				this->m_Points += this->m_Enemies[i].getPoints();
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
	for (auto& enemy : this->m_Enemies)
	{
		enemy.render(&this->m_Window);
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
	std::stringstream ss;
	ss << "Points: " << this->m_Points;
	this->m_PointText.setString(ss.str());
	this->m_PlayerHpBar.setSize(sf::Vector2f(300.f *
		(static_cast<float>(this->m_Player.getHp()) / (static_cast<float>(this->m_Player.getHpMax()))),
		this->m_PlayerHpBar.getSize().y));
}

void Game::renderGUI()
{
	this->m_Window.draw(m_PointText);
	this->m_Window.draw(m_PlayerHpBarBack);
	this->m_Window.draw(m_PlayerHpBar);
}

void Game::update()
{
	this->handleEvents();
	if (this->m_Player.getHp() > 0)
	{
		this->m_Player.update(&m_Window);
		this->updateBullets();
		this->updateEnemies();
		this->updateGUI();
	}
}

void Game::render()
{
	this->m_Window.clear();
	this->renderWorld();
	this->m_Player.render(&m_Window);
	this->renderBullets();
	this->renderEnemies();
	this->renderGUI();
	if (this->m_Player.getHp() == 0) {
		this->m_Window.draw(m_GameOverText);
	}
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
