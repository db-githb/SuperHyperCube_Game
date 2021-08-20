#include "GameManager.h"
#include <string> 

void GameManager::initialize(Shader* inBaseShader, Shader* inTextShader, SoundManager* inSoundManager, glm::vec2 windowSize){
	nrModels = 5;
	models = new ModelBase * [nrModels]{
		new ModelRichard(*inBaseShader),
		new ModelDamian(*inBaseShader),
		new ModelThomas(*inBaseShader),
		new ModelMichael(*inBaseShader),
		new ModelElijah(*inBaseShader),
	};

	shuffle();
	currentModel = 0;
	activeModel = models[currentModel];
	activeModel->randomOrientation();
	startOn = false;
	score = 0;
	endState = false;

	startTime = 0;
	deltaTime = 0;

	soundManager = inSoundManager;

	textGenerator = new TextGenerator();
	textGenerator->setup();
	textShader = inTextShader;
	windowWidth = windowSize.x;
	windowHeight = windowSize.y;
}

void GameManager::start() {
	
	if (startOn) {
		return;
	}

	startOn = true;
	soundManager->setPaused(false);
	startTime = glfwGetTime();
	activeModel->turnMovementOn();
}

void GameManager::draw(Shader* inShader) {

	textShader->use();
	if (startOn) {
		deltaTime = glfwGetTime() - startTime;
		int displayTime = 10 - (int)deltaTime;
		if (displayTime < 0) displayTime = 0;
		textGenerator->renderText(*textShader, "Score: " + std::to_string(score), windowWidth - 240, windowHeight - 50, 0.75f, glm::vec3(0.5, 0.8f, 0.2f));
		textGenerator->renderText(*textShader, "Time: " + std::to_string(displayTime), windowWidth - 240, windowHeight - 100, 0.75f, glm::vec3(0.5, 0.8f, 0.2f));
	}
	else {
		textGenerator->renderText(*textShader, "Press Spacebar to Start", windowWidth/2-255, (windowHeight/2)+(windowHeight* 0.09765625f), 1.0f, glm::vec3(0.5, 0.8f, 0.2f));
	}
	

	if (!endState) {
		if (activeModel->objectAtWall()) {
			if (activeModel->passOrientation()) {
				activeModel->successState();
				soundManager->playSuccessSound();
				score += deltaTime >= 10 ? 1 : (10 - (int)deltaTime);
			}
			else {
				activeModel->failState();
				soundManager->playErrorSound();
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
	startTime = glfwGetTime();

	currentModel += 1;
	// loop and shuffle array when at the end
	if (currentModel == nrModels) {
		shuffle();
		currentModel = 0;
	}

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

void GameManager::setWindowSize(float width, float height) {
	windowWidth = width;
	windowHeight = height;
}

double GameManager::getStartTime() {
	return startTime;
}
double GameManager::getDeltaTime() {
	return deltaTime;
}

void GameManager::shuffle() {
	for (int i = nrModels - 1; i > 0; i--) {
		int j = rand() % (i + 1);
		ModelBase* temp = models[i];
		models[i] = models[j];
		models[j] = temp;
	}
}