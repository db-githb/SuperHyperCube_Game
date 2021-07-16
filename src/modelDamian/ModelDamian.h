#pragma once
#include "../modelBase/ModelBase.h"

#define ROWS 9
#define COLUMNS 7
#define PLANES 7

#define NONE -2
#define WALL -1

#define RED 0
#define BLUE 1
#define VIOLET 2
#define NUM_COLORS 3


class ModelDamian : public ModelBase {

public:
	void initialize();
	void draw(Camera inCam, glm::vec3* dirLight, glm::mat4 projection, glm::mat4 view, glm::mat4 model);
	int* generateRandomModel(int rows, int columns, int planes);
	void generateOriginalObject();
	void intializeColorPalette();
	bool boundaryCollision();

private:
	int modelData[ROWS][COLUMNS][PLANES];
	void resetModel();
	glm::vec3* colorPalette;
};