#include "GameManager.h"

void GameManager::ResetGame()
{
	currentLevelIndex = 0;
	points = 0;
	gameStartTime = glfwGetTime();
}

void GameManager::ResetLevel()
{
	currentLevel->resetLevel();
}

void GameManager::AddLevel(Level* level)
{
	level->AddPosition(glm::vec3(0, 5, 0));
	levels.push_back(level);
	if (currentLevel == nullptr)
		currentLevel = levels[currentLevelIndex];
}

void GameManager::QuickDrop()
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
	ResetLevel();
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

void GameManager::Update(float ms)
{
	if (currentLevel->object->GetPosition().z > -9.0f)
	{
		UpdateObjectPosition(ms);
	}
	else
		NextLevel();
}

void GameManager::UpdateObjectPosition(float ms)
{
	
	float increment = (modelTargetPosition.z - currentLevel->object->GetPosition().z) * 0.3;
	currentLevel->object->AddPosition(glm::vec3(0,0,increment)* ms);
}

bool GameManager::IsObjectAtEnd()
{
	return false;
}

bool GameManager::ValidateLevel()
{
	return currentLevel->validateOrientation();
}

void GameManager::Draw(Shader& inShader)
{
	
	currentLevel->Draw(inShader);
}

void GameManager::AddRotation90(glm::vec3 axis)
{
	currentLevel->object->AddRotation90(axis);
}


GameManager::GameManager()
{
	modelTargetPosition = glm::vec3(0, 0, -30);
	ResetGame();
}

