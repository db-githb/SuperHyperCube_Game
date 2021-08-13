#include "ModelThomas.h"

ModelThomas::ModelThomas(Shader& inShader) : Model(inShader) {

	modelBasePosition = glm::vec3(15.0f, 0.5f, -15.0f);

	rows = 9;
	columns = 7;
	planes = 7;

	colorPalette = new glm::vec3[NUM_COLORS];
	setColorPalette();

	allocateWallData();
	allocateObjectData();

}


void ModelThomas::allocateObjectData() {

	Model::allocateObjectData();

	for (int r = 2; r < 8; r++) {
		data.cubePositions[r][1][planes - 3] = YELLOW;
		data.cubePositions[r][1][0] = NONE;
	}

	for (int c = 1; c < 6; c++) {
		data.cubePositions[1][c][planes - 3] = YELLOW;
		data.cubePositions[1][c][0] = NONE;
	}

	for (int r = 2; r < 8; r++) {
		data.cubePositions[r][1][planes - 2] = YELLOW;
		data.cubePositions[r][1][0] = NONE;
	}

	for (int c = 1; c < 6; c++) {
		data.cubePositions[1][c][planes - 2] = YELLOW;
		data.cubePositions[1][c][0] = NONE;
	}

	data.cubePositions[2][2][0] = NONE;
	for (int p = 2; p < 6; p++) {
		data.cubePositions[2][2][p] = ORANGE;
	}

	data.cubePositions[5][2][0] = NONE;
	for (int p = 2; p < 6; p++) {
		data.cubePositions[5][2][p] = ORANGE;
	}

	for (int r = 2; r < 6; r++) {
		data.cubePositions[r][1][planes - 1] = ORANGE;
	}

}


void ModelThomas::resetModel() {
	// initialize wall and empty space
	for (int r = 0; r < rows; r++) {
		for (int c = 0; c < columns; c++) {
			for (int p = 0; p < planes; p++) {
				if (p == 0) {
					data.cubePositions[r][c][p] = WALL;
				}
				else {
					data.cubePositions[r][c][p] = NONE;
				}
			}
		}
	}
}



void ModelThomas::generateOriginalObject() {

	resetModel();

	for (int r = 2; r < 8; r++) {
		data.cubePositions[r][1][planes - 3] = YELLOW;
		data.cubePositions[r][1][0] = NONE;
	}

	for (int c = 1; c < 6; c++) {
		data.cubePositions[1][c][planes - 3] = YELLOW;
		data.cubePositions[1][c][0] = NONE;
	}

	for (int r = 2; r < 8; r++) {
		data.cubePositions[r][1][planes - 2] = YELLOW;
		data.cubePositions[r][1][0] = NONE;
	}

	for (int c = 1; c < 6; c++) {
		data.cubePositions[1][c][planes - 2] = YELLOW;
		data.cubePositions[1][c][0] = NONE;
	}

	data.cubePositions[2][2][0] = NONE;
	for (int p = 2; p < 6; p++) {
		data.cubePositions[2][2][p] = ORANGE;
	}

	data.cubePositions[5][2][0] = NONE;
	for (int p = 2; p < 6; p++) {
		data.cubePositions[5][2][p] = ORANGE;
	}

	for (int r = 2; r < 6; r++) {
		data.cubePositions[r][1][planes - 1] = ORANGE;
	}
}

void ModelThomas::generateRandomModel() {

	resetModel();

	for (int r = 2; r < 8; r++) {
		
		data.cubePositions[r][1][0] = NONE;

		if ((rand() % 10 == 0)) {
			continue;
		}

		for (int p = 2; p < planes; p++)
			if ((rand() % 2 == 1)) {
				data.cubePositions[r][1][p] = rand() % NUM_COLORS;
			}
	}

	for (int c = 1; c < 6; c++) {
		data.cubePositions[1][c][0] = NONE;

		if ((rand() % 10 == 0)) {
			continue;
		}

		for (int p = 2; p < planes; p++)
			if ((rand() % 2 == 1)) {
				data.cubePositions[1][c][p] =  rand() % NUM_COLORS;
			}
	}

	data.cubePositions[2][2][0] = NONE;
	data.cubePositions[5][2][0] = NONE;

	for (int p = 2; p < planes; p++) {
		if ((rand() % 10 == 0)) {
			continue;
		}

		if ((rand() % 2 == 1)) {
			data.cubePositions[2][2][p] = rand() % NUM_COLORS;
		}
	}

	
	for (int p = 2; p < planes; p++) {
		if ((rand() % 10 == 0)) {
			continue;
		}

		if ((rand() % 2 == 1)) {
			data.cubePositions[5][2][p] = rand() % NUM_COLORS;
		}
	}


}

