#pragma once
#include "../modelBase/ModelBase.h"

class ModelMichael : public ModelBase {

public:
	ModelMichael(Shader& inShader);
	void generateOriginalObject();
	void generateRandomModel();
	void resetUnitCubes();
	void resetModel();

	void generateCube(int rowStart, int rowEnd, int columnStart, int columnEnd, int planeStart, int planeEnd, int color);
};

