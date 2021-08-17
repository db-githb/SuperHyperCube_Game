#pragma once

#include "../Objects/Level.h"
#include "../Sound/SoundManager.h"

class GameManager : public ObjectNode
{
public:
	GameManager();
	void ResetGame();
	void ResetLevel();
	void AddLevel(Level* level);
	void AddPoints(int p);
	void QuickDrop();

	Level* NextLevel();
	void GameOver();
	void Update(float ms) override;
	void UpdateObjectPosition(float ms);
	bool IsObjectAtEnd();
	bool ValidateLevel();
	void Draw(Shader& inShader) override;

	void AddRotation90(glm::vec3 axis) override;
	
	Level* currentLevel;
	int currentLevelIndex = 0;
	
	int points = 0;
	float gameStartTime = 0;
	float levelStartTime = 0;
	float levelTimeLimit = 10.0f;
	float timeUntilNextLevel = 0;
	
	

private:
	SoundManager* soundManager;
	std::vector<Level*> levels;
	glm::vec3 modelTargetPosition;
	float lastUpdateTime = 0;
};

