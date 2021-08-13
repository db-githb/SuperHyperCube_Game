#pragma once
#include "../../modelBase/Model.h"

class ModelMichael : public Model {

public:
	ModelMichael(Shader& inShader);
	void generateOriginalObject();
	void generateRandomModel();
	void resetUnitCubes();
	void resetModel();

	void generateCube(int rowStart, int rowEnd, int columnStart, int columnEnd, int planeStart, int planeEnd, int color);

	void positionModel(float x, float y, float z);
};

