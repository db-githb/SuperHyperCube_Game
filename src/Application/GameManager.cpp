#include "GameManager.h"

void GameManager::Reset()
{
	currentLevelIndex = 0;
	points = 0;
	gameStartTime = glfwGetTime();
}

void GameManager::AddLevel(Level* level)
{
	levels.push_back(level);
}

void GameManager::LockPosition()
{
	// Validate the current object orientation in the level
		//If it is correct, AddPoints();
		// else -> do nothing
	//Load next level -> NextLevel();
}

void GameManager::AddPoints(int p)
{
	points += p;
}

Level* GameManager::NextLevel()
{
	currentLevelIndex = (currentLevelIndex + 1)%levels.size();
	currentLevel = levels[currentLevelIndex];

	levelStartTime = glfwGetTime();
	
	return currentLevel;
}

void GameManager::GameOver()
{
	std::cout << "GameOver!";
	return;
}

void GameManager::Update()
{
	
}

GameManager::GameManager()
{
	Reset();
}

