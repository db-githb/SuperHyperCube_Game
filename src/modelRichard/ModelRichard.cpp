#include "ModelRichard.h"

#define COLUMNS 9

ModelRichard::ModelRichard(Shader& inShader) : ModelBase(inShader) {

	allocateShaderData();

	modelBasePosition = glm::vec3(0.0f, 0.5f, 0.0f);

	rows = 9;
	columns = 9;
	planes = 7;

	colorPalette = new glm::vec3[NUM_COLORS];
	setColorPalette();

	allocateWallData();
	allocateObjectData();
}


void ModelRichard::allocateObjectData() {

	ModelBase::allocateObjectData();

	int wallArray[ROWS][COLUMNS + 2] = { {-1, -1, -1, -1, -1, -1, -1, -1, -1},
										 {-1, -1, -2, -2, -1, -1, -2, -2, -1},
										 {-1, -2, -2, -2, -2, -2, -2, -2, -1},
										 {-1, -2, -2, -2, -2, -2, -2, -2, -1},
										 {-1, -2, -2, -2, -2, -2, -2, -2, -1},
										 {-1, -2, -2, -2, -2, -2, -2, -2, -1},
										 {-1, -2, -2, -2, -2, -2, -2, -1, -1},
										 {-1, -2, -2, -2, -2, -2, -2, -1, -1},
										 {-1, -1, -1, -1, -1, -1, -1, -1, -1} };
	for (int r = 0; r < ROWS; r++) {
		for (int c = 0; c < COLUMNS; c++) {
			int colorIndex = wallArray[r][c];
			if (colorIndex == NONE) {
				wall.modelData[8 - r][c][0] = colorIndex;
			}
		}
	}

	int modelLayer1[ROWS][COLUMNS + 2] = { {-2, -2, -2, -2, -2, -2, -2, -2, -2},
										   {-2, -2, 10, 10, -2, -2, 10, 10, -2},
										   {-2, 10, 10, 10, 10, 10, 10, 10, -2},
										   {-2, 10, 10, 12,  9,  10, 12, 9, -2},
										   {-2, 10, 10, 10, 10, 10, 10, 10, -2},
										   {-2,  2, 10, 11, 11, 11, 11, 11, -2},
										   {-2,  2, 10, 10, 10, 10, 10, -2, -2},
										   {-2,  2,  2,  2,  2,  2,  2, -2, -2},
										   {-2, -2, -2, -2, -2, -2, -2, -2, -2} };
	for (int r = 0; r < ROWS; r++) {
		for (int c = 0; c < COLUMNS; c++) {
			int colorIndex = modelLayer1[r][c];
			object.modelData[8 - r][c][3] = colorIndex;
		}
	}

	int modelLayer2[ROWS][COLUMNS + 2] = { {-2, -2, -2, -2, -2, -2, -2, -2, -2},
										   {-2, -2, -2, -2, -2, -2, -2, -2, -2},
										   {-2, -2, 10, 10, 10, 10, 10, 10, -2},
										   {-2, -2, 10, 12,  9, 10, 12, 10, -2},
										   {-2, -2, 10, 10, 10, 10, 10, 10, -2},
										   {-2, -2, -2, 11, 11, 11, 11, 11, -2},
										   {-2, -2, -2, -2, -2, -2, -2, -2, -2},
										   {-2, -2, -2, -2, -2, -2, -2, -2, -2},
										   {-2, -2, -2, -2, -2, -2, -2, -2, -2} };
	for (int r = 0; r < ROWS; r++) {
		for (int c = 0; c < COLUMNS; c++) {
			int colorIndex = modelLayer2[r][c];
			object.modelData[8 - r][c][4] = colorIndex;
		}
	}

	int modelLayer3[ROWS][COLUMNS + 2] = { {-2, -2, -2, -2, -2, -2, -2, -2, -2},
										   {-2, -2, -2, -2, -2, -2, -2, -2, -2},
										   {-2, -2, -2, -2, -2, -2, -2, -2, -2},
										   {-2, -2, -2, 12,  9, -2, 12,  9, -2},
										   {-2, -2, -2, -2, -2, -2, -2, -2, -2},
										   {-2, -2, -2, -2, -2, -2, -2, -2, -2},
										   {-2, -2, -2, -2, -2, -2, -2, -2, -2},
										   {-2, -2, -2, -2, -2, -2, -2, -2, -2},
										   {-2, -2, -2, -2, -2, -2, -2, -2, -2} };
	for (int r = 0; r < ROWS; r++) {
		for (int c = 0; c < COLUMNS; c++) {
			int colorIndex = modelLayer3[r][c];
			object.modelData[8 - r][c][5] = colorIndex;
		}
	}
}


void ModelRichard::resetModel() {
	// initialize wall and empty space
	for (int r = 0; r < ROWS; r++) {
		for (int c = 0; c < COLUMNS; c++) {
			for (int p = 0; p < PLANES; p++) {
				if (p == 0) {
					wall.modelData[r][c][p] = WALL;
				}
				else {
					object.modelData[r][c][p] = NONE;
				}
			}
		}
	}
}



void ModelRichard::generateOriginalObject() {
	resetModel();
}

void ModelRichard::generateRandomModel() {

	resetModel();

	for (int r = 2; r < 8; r++) {

		wall.modelData[r][1][0] = NONE;

		if ((rand() % 10 == 0)) {
			continue;
		}

		for (int p = 2; p < PLANES; p++)
			if ((rand() % 2 == 1)) {
				object.modelData[r][1][p] = rand() % NUM_COLORS;
			}
	}

	for (int c = 1; c < 6; c++) {
		wall.modelData[1][c][0] = NONE;

		if ((rand() % 10 == 0)) {
			continue;
		}

		for (int p = 2; p < PLANES; p++)
			if ((rand() % 2 == 1)) {
				object.modelData[1][c][p] = rand() % NUM_COLORS;
			}
	}

	wall.modelData[2][2][0] = NONE;
	wall.modelData[5][2][0] = NONE;

	for (int p = 2; p < PLANES; p++) {
		if ((rand() % 10 == 0)) {
			continue;
		}

		if ((rand() % 2 == 1)) {
			wall.modelData[2][2][p] = rand() % NUM_COLORS;
		}
	}


	for (int p = 2; p < PLANES; p++) {
		if ((rand() % 10 == 0)) {
			continue;
		}

		if ((rand() % 2 == 1)) {
			object.modelData[5][2][p] = rand() % NUM_COLORS;
		}
	}
}

