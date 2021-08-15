#pragma once
#include "../modelBase/ModelBase.h"
#include "../shader/Shader.h"

class GameManager {

public:
	int score;
	int nrModels;
	bool startOn;
	ModelBase** models;
	ModelBase* activeModel;
	void initialize(int inNumModels, ModelBase** inModels);
	void start();
	void draw(Shader* inShader);
	void speedUp();

	void nextModel();
	int currentModel;
};