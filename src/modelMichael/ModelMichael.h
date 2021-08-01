#pragma once
#include "../modelBase/ModelBase.h"

#define ROWS 9
#define COLUMNS 7
#define PLANES 7


#define WALL 0
#define BLUE 1
#define RED 2

class ModelMichael : public ModelBase {

public:
	ModelMichael(Shader& inShader);
	void generateOriginalObject();
	void generateRandomModel();
	void resetUnitCubes();
	void resetModel();

	void generateCube(int rowStart, int rowEnd, int columnStart, int columnEnd, int planeStart, int planeEnd, int color);

	void positionModel(float x, float y, float z);

private:
	int modelData[ROWS][COLUMNS][PLANES];

};

