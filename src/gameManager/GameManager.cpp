#include "GameManager.h"

void GameManager::initialize(int inNumModels, ModelBase** inModels) {
	nrModels = inNumModels;
	models = inModels;

	currentModel = 0;
	activeModel = models[currentModel];
	startOn = false;
	score = 0;
}

void GameManager::start() {
	startOn = true;
	activeModel->turnMovementOn();
}

void GameManager::draw(Shader* inShader) {
	
	if (activeModel->objectAtWall()) {
		if (activeModel->passOrientation()) {
			std::cout << "success!" << std::endl;
			score += 1;
			nextModel();
		}
		else {
			std::cout << "failure :(" << std::endl;
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
	activeModel->speed = 0.08f;
}