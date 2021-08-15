#include "GameManager.h"

void GameManager::initialize(int inNumModels, ModelBase** inModels) {
	nrModels = inNumModels;
	models = inModels;

	activeModel = models[0];
	startOn = false;
	score = 0;
}

void GameManager::start() {
	startOn = true;
	activeModel->turnContinuousOn();
}

void GameManager::draw(Shader* inShader) {
	if (activeModel->objectAtWall()) {
		if (activeModel->passOrientation()) {
			std::cout << "success!" << std::endl;
		}
		else {
			std::cout << "failure :(" << std::endl;
		}
		activeModel->stopMovement();
	}

	activeModel->draw(inShader);
}