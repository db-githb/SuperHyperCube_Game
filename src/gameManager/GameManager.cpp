#include "GameManager.h"

void GameManager::initialize(int inNumModels, ModelBase** inModels) {
	nrModels = inNumModels;
	models = inModels;

	currentModel = 0;
	activeModel = models[currentModel];
	startOn = false;
	score = 0;

	endState = false;
}

void GameManager::start() {
	startOn = true;
	activeModel->turnMovementOn();
	startTime = glfwGetTime();
	std::cout << "start time: " << startTime << std::endl;
}

void GameManager::draw(Shader* inShader) {
	
	if (!endState) {
		if (activeModel->objectAtWall()) {
			if (activeModel->passOrientation()) {
				activeModel->successState();
				double endTime = glfwGetTime();
				std::cout << "delta time: " << endTime - startTime << std::endl;
				score += 1;
			}
			else {
				activeModel->failState();
			}
			endState = true;
		}
	}
	else {
		if (activeModel->endFinished()) {
			nextModel();
			endState = false;
		}
	}

	activeModel->draw(inShader);
}

void GameManager::nextModel() {
	activeModel->resetPOS();
	currentModel = currentModel == 4 ? 0 : currentModel + 1;
	activeModel = models[currentModel];
	activeModel->speed = 0.03f;
	activeModel->turnMovementOn();
}

void GameManager::speedUp() {
	activeModel->speed = 0.5f;
}

