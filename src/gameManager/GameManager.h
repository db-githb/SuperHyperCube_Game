#pragma once
#include "../modelBase/ModelBase.h"
#include "../shader/Shader.h"
#include "../soundManager/SoundManager.h"
#include "../textGenerator/TextGenerator.h"

class GameManager {

public:
	ModelBase* activeModel;
	void initialize(int inNumModels, ModelBase** inModels, SoundManager* inSoundManager, Shader* inTextShader, glm::vec2 windowSize);
	void start();
	void draw(Shader* inShader);
	void speedUp();
	void nextModel();
	void setWindowSize(float width, float height);

private:

	int score;
	int nrModels;
	bool startOn;
	ModelBase** models;

	int currentModel;
	double startTime;
	double deltaTime;

	SoundManager* soundManager;
	TextGenerator* textGenerator;
	Shader* textShader;
	bool endState;

	float windowWidth;
	float windowHeight;
};