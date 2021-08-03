#pragma once
#include "../modelBase/ModelBase.h"


#define COLUMNS 9
#define ROWS 7
#define PLANES 7

class ModelElijah : public ModelBase {



public:
	ModelElijah(Shader &inShader);

	void generateRandomModel();

	void generateOriginalObject();

private:
	int modelData[9][7][7];
	glm::mat4 positionMat;
};