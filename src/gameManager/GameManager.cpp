#include "GameManager.h"

void GameManager::initialize(int inNumModels, ModelBase** inModels) {
	nrModels = inNumModels;
	models = inModels;

	currentModel = 0;
	activeModel = models[currentModel];
	activeModel->randomOrientation();
	startOn = false;
	score = 0;
	endState = false;

	startTime = 0;
	deltaTime = 0;
}

void GameManager::start() {
	
	if (startOn) {
		return;
	}

	startOn = true;
	startTime = glfwGetTime();
	activeModel->turnMovementOn();
}

void GameManager::draw(Shader* inShader) {
	
	deltaTime = glfwGetTime() - startTime;

	if (!endState) {
		if (activeModel->objectAtWall()) {
			if (activeModel->passOrientation()) {
				activeModel->successState();
				score += deltaTime >= 10 ? 1 : (10 - (int)deltaTime);
			}
			else {
				activeModel->failState();
			}
			endState = true;
		}
	}
	else {
		if (activeModel->endFinished()) {
			std::cout << score << std::endl;
			nextModel();
			endState = false;
		}
	}

	activeModel->draw(inShader);
}

void GameManager::nextModel() {
	startTime = glfwGetTime();

	// loop array when at the end
	currentModel = currentModel == 4 ? 0 : currentModel + 1;

	// set next active model
	activeModel = models[currentModel];
	activeModel->resetPOS();
	activeModel->randomOrientation();
	activeModel->speed = 0.03f;
	activeModel->turnMovementOn();
	startTime = glfwGetTime();
}

void GameManager::speedUp() {
	activeModel->speed = 0.5f;
}

