#include "GameManager.h"

void GameManager::initialize(int inNumModels, ModelBase* inModels) {
	nrModels = inNumModels;
	models = inModels;

	activeModel = &models[0];
	startOn = false;
	score = 0;
}

void GameManager::start() {
	startOn = true;
	activeModel->turnContinuousOn();
}

void GameManager::draw(Shader* inShader) {
	activeModel->draw(inShader);
}