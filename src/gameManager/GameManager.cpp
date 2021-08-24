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
	gameOn = false;
	score = 0;
	endState = false;

	startTime = 0;
	deltaTime = 0;

	pauseOn = true;
	pauseEndTime = glfwGetTime();
	

	soundManager = inSoundManager;

	textGenerator = new TextGenerator();
	textGenerator->setup();
	textShader = inTextShader;
	windowWidth = windowSize.x;
	windowHeight = windowSize.y;

	scoreTimeApart = false;
}

void GameManager::toggleGame() {
	
	if (gameOn) {
		gameOn = false;
		pauseStartTime = glfwGetTime();
	}
	else {
		gameOn = true;
		pauseEndTime = glfwGetTime();
		deltaPause = pauseEndTime - pauseStartTime;
		startTime += deltaPause;
	}

	soundManager->setPaused(false);
	activeModel->toggleMovement();
}

void GameManager::draw(Shader* inShader) {

	textShader->use();
	if (gameOn) {
		deltaTime = glfwGetTime() - startTime;
		displayTime = 10 - (int)deltaTime;
		if (displayTime < 0) displayTime = 0;

		if (scoreTimeApart) {
			textGenerator->renderText(*textShader, "Score: " + std::to_string(score), 80, windowHeight - 50, 0.75f, glm::vec3(0.5, 0.8f, 0.2f));
			textGenerator->renderText(*textShader, "Time: " + std::to_string(displayTime), windowWidth - 220, windowHeight - 50, 0.75f, glm::vec3(0.5, 0.8f, 0.2f));
		}
		else {
			textGenerator->renderText(*textShader, "Score: " + std::to_string(score), windowWidth - 240, windowHeight - 50, 0.75f, glm::vec3(0.5, 0.8f, 0.2f));
			textGenerator->renderText(*textShader, "Time: " + std::to_string(displayTime), windowWidth - 240, windowHeight - 100, 0.75f, glm::vec3(0.5, 0.8f, 0.2f));
		}
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
	activeModel->toggleMovement();
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