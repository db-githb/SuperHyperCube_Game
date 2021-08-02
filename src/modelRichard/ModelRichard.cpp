#include "ModelRichard.h"

#define ROWS 9
#define COLUMNS 9
#define PLANES 6

ModelRichard::ModelRichard(Shader& inShader) : ModelBase(inShader) {

	allocateShaderData();

	modelBasePosition = glm::vec3(0.0f, 0.5f, 0.0f);

	rows = 9;
	columns = 9;
	planes = 7;

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

	resetObject();

	for (int r = 0; r < rows; r++) {
		for (int c = 0; c < columns; c++) {

			// 5% chance of empty slot across all planes
			if (wall.modelData[r][c][0] == NONE && (rand() % 100 > 5)) {
				int start = rand() % (planes - 1);
				int end = rand() % (planes - start) + start;
				for (int p = start; p < end; p++) {
					object.modelData[r][c][p] = (rand() % (NUM_COLORS - 1)) + 1;
				}

			}
		}
	}
}

