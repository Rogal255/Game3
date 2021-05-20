#pragma once

#include "Player.hpp"
#include "Bullet.hpp"
#include "Enemy.hpp"
#include <map>
#include <iostream>
#include <sstream>

class Game
{
	sf::ContextSettings m_Settings{ 0U, 0U, 16U, 1U, 1U, 0U, false };
	sf::RenderWindow m_Window{ sf::VideoMode(1200, 900), "Game 3", sf::Style::Close | sf::Style::Titlebar, m_Settings };
	sf::Event m_Event;
	sf::Clock m_GunCooldown;
	sf::Clock m_EnemySpawnClock;
	uint16_t m_EnemySpawnCooldown{ 0 };
	float m_LastEnemyPosX{ 0.f };
	float m_NewEnemyPosX{ 0.f };

	// Resources
	std::map<std::string, sf::Texture> m_Textures;
	Player m_Player;
	std::vector<Bullet> m_Bullets;
	std::vector<Enemy> m_Enemies;

	// GUI
	sf::Font m_Font;
	sf::Text m_PointText;
	uint16_t m_Points{ 0 };
	sf::RectangleShape m_PlayerHpBar;
	sf::RectangleShape m_PlayerHpBarBack;
	sf::Text m_GameOverText;

	// World
	sf::Sprite m_WorldBackground;

	// Private methods
	void renderWorld();
	void updateBullets();
	void renderBullets();
	void updateEnemies();
	void renderEnemies();
	void handleEvents();
	void updateGUI();
	void renderGUI();
	void update();
	void render();

public:
	Game();
	~Game();

	// Public methods
	void run();
};
