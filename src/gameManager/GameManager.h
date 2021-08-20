#pragma once
#include "../modelBase/ModelBase.h"
#include "../modelDamian/modelDamian.h"
#include "../modelElijah/modelElijah.h"
#include "../modelThomas/modelThomas.h"
#include "../modelMichael/modelMichael.h"
#include "../modelRichard/modelRichard.h"
#include "../shader/Shader.h"
#include "../soundManager/SoundManager.h"
#include "../textGenerator/TextGenerator.h"

class GameManager {

public:
	ModelBase* activeModel;
	void initialize(Shader* inBaseShader, Shader* inTextShader, SoundManager* inSoundManager, glm::vec2 windowSize);
	void start();
	void draw(Shader* inShader);
	void speedUp();
	void nextModel();
	void setWindowSize(float width, float height);
	double getStartTime();
	double getDeltaTime();

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

	void shuffle();
};