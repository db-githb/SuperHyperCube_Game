#pragma once

#include "../Objects/Level.h"

class GameManager
{
public:
	GameManager();
	void Reset();
	void AddLevel(Level* level);
	void LockPosition();
	void AddPoints(int p);
	Level* NextLevel();
	void GameOver();
	void Update();

	
	Level* currentLevel;
	int currentLevelIndex = 0;
	
	int points = 0;
	float gameStartTime = 0;
	float levelStartTime = 0;
	float levelTimeLimit = 10.0f;
	float timeUntilNextLevel = 0;
	
	

private:
	std::vector<Level*> levels;
	
};

