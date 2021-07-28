#include "ModelThomas.h"

void ModelThomas::initialize() {

	modelBasePosition = glm::vec3(5.0f, 0.5f, -5.0f);

	resetModel();
	generateOriginalObject();

	colorPalette = new glm::vec3[NUM_COLORS];
	initializeColorPalette();

}

void ModelThomas::initializeColorPalette() {

	colorPalette[YELLOW] = glm::vec3(1.0f, 1.0f, 0.0f);
	colorPalette[ORANGE] = glm::vec3(1.0f, 0.5f, 0.0f);

}

void ModelThomas::resetModel() {
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

void ModelThomas::generateOriginalObject() {

	resetModel();

	for (int r = 2; r < 8; r++) {
		object.modelData[r][1][PLANES - 3] = YELLOW;
		wall.modelData[r][1][0] = NONE;
	}

	for (int c = 1; c < 6; c++) {
		object.modelData[1][c][PLANES - 3] = YELLOW;
		wall.modelData[1][c][0] = NONE;
	}

	for (int r = 2; r < 8; r++) {
		object.modelData[r][1][PLANES - 2] = YELLOW;
		wall.modelData[r][1][0] = NONE;
	}

	for (int c = 1; c < 6; c++) {
		object.modelData[1][c][PLANES - 2] = YELLOW;
		wall.modelData[1][c][0] = NONE;
	}

	modelData[2][2][0] = NONE;
	for (int p = 2; p < 6; p++) {
		object.modelData[2][2][p] = ORANGE;
	}

	modelData[5][2][0] = NONE;
	for (int p = 2; p < 6; p++) {
		object.modelData[5][2][p] = ORANGE;
	}

	for (int r = 2; r < 6; r++) {
		object.modelData[r][1][PLANES - 1] = ORANGE;
	}
}

void ModelThomas::generateRandomModel() {

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
				object.modelData[1][c][p] =  rand() % NUM_COLORS;
			}
	}

	wall.modelData[2][2][0] = NONE;
	modelData[5][2][0] = NONE;

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
