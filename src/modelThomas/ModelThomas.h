#pragma once
#include "../modelBase/ModelBase.h"

#define ROWS 9
#define COLUMNS 7
#define PLANES 6

#define NONE -2
#define WALL -1

#define YELLOW 0
#define ORANGE 1
#define NUM_COLORS 2

class ModelThomas : public ModelBase {

public:
	void initialize();
	void generateRandomModel();
	void generateOriginalObject();
	void initializeColorPalette();

private:
	int modelData[ROWS][COLUMNS][PLANES];
	void resetModel();
	glm::vec3* colorPalette;
};