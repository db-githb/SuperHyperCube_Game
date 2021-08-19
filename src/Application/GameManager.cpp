#include "GameManager.h"

void GameManager::ResetGame()
{
	currentLevelIndex = 0;
	points = 0;
	gameStartTime = glfwGetTime();
	soundManager = new SoundManager();
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
	if (currentLevel->object->GetPosition().z > -12.0f)
	{
		//UpdateObjectPosition(ms);
	}
	else
	{
		ValidateLevel();
		NextLevel();
	}
	if(glfwGetTime() - lastUpdateTime > 2)
	{
		std::cout << "\n ________________________________________________________________";
		lastUpdateTime = glfwGetTime();
		for(int i = 0; i <9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				for (int k = 0; k < 7; k++)
				{
					if (currentLevel->object->m_model->cubes[i][j][k] == NONE)
						continue;

					std::cout << "\n object z: " << currentLevel->object->m_model->cubePositions[i][j][k].z;
				}
			}
		}
		
		//std::cout << "\n wall z: " << currentLevel->wall->GetPosition().z;
	}
}

void GameManager::UpdateObjectPosition(float ms)
{
	
	float increment = (modelTargetPosition.z - currentLevel->object->GetPosition().z) * 0.1;
	currentLevel->object->AddPosition(glm::vec3(0,0,increment)* ms);
}

bool GameManager::IsObjectAtEnd()
{
	return false;
}

bool GameManager::ValidateLevel()
{
	bool result = currentLevel->validateOrientation();

	if(result == true)
	{
		soundManager->playSuccessSound();
		return true;
	}
	else
	{
		soundManager->playErrorSound();
		return false;
	}
}

void GameManager::Draw(Shader& inShader)
{
	currentLevel->Draw(inShader);
}

void GameManager::AddRotation90(glm::vec3 axis)
{
	soundManager->playRotateSound();
	currentLevel->object->AddRotation90(axis);
}


GameManager::GameManager()
{
	modelTargetPosition = glm::vec3(0, 0, -30);
	ResetGame();

}
