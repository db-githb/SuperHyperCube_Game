#include "ModelDamian.h"

void ModelDamian::initialize() {
	
	allocateShaderData();

	modelBasePosition = glm::vec3(-15.0f, 0.5f, 15.0f);

	//modelBasePosition = glm::vec3(0.0f, 0.5f, 0.0f);

	rows = 9;
	columns = 7;
	planes = 7;

	allocateWallData();
	allocateObjectData();
}

void ModelDamian::generateRandomModel() {

	resetObject();

	// reset unitCubes in the model to their respective colors
	for (int r = 1; r < 8; r++) {

		//puts hole in the wall
		wall.modelData[r][3][0] = NONE;

		// 10% chance of a blank discontinuity in the model (blank space? blank cartridge? i don't know how to describe this)
		if ((rand() % 10 == 0)) {
			continue;
		}

		// randomly generates blocks on z axis
		for (int z = 2; z < 7; z++) {

			if ((rand() % 2) == 1) {
				object.modelData[r][3][z] = rand()%NUM_COLORS;
			}
		}
	}

	for (int c = 1; c < 6; c++) {

		// puts hole in the wall
		wall.modelData[2][c][0] = NONE;
		wall.modelData[6][c][0] = NONE;
		wall.modelData[4][c][0] = NONE;

		// same as above 10% chance...
		if ((rand() % 10 == 0)) {
			continue;
		}

		// randomly generates blocks on z axis
		for (int z = 2; z < 7; z++) {
			
			if ((rand() % 2) == 1) {
				object.modelData[2][c][z] = rand()%NUM_COLORS;
			}
			

			if (c != 3) {

				if ((rand() % 2) == 1) {
					object.modelData[6][c][z] = rand() % NUM_COLORS;
				}
			}

			if (c == 2 || c == 4) {
				
				if ((rand() % 2) == 1) {
					object.modelData[4][c][z] = rand() % NUM_COLORS;
				}
			}
		}
	}
}

void ModelDamian::allocateObjectData() {

	ModelBase::allocateObjectData();

	// reset unitCubes in the model to their respective colors
	for (int r = 1; r < 8; r++) {
		object.modelData[r][3][planes - 3] = BLUE;
		wall.modelData[r][3][0] = NONE;
	}

	for (int c = 1; c < 6; c++) {

		object.modelData[2][c][planes - 3] = RED;
		wall.modelData[2][c][0] = NONE;

		if (c == 1) {
			object.modelData[6][1][planes - 5] = RED;
			object.modelData[6][1][planes - 4] = RED;

			object.modelData[2][1][planes - 1] = RED;
			object.modelData[2][1][planes - 2] = RED;
		}

		if (c == 5) {
			object.modelData[6][c][planes - 1] = RED;
			object.modelData[6][c][planes - 2] = RED;

			object.modelData[2][c][planes - 5] = RED;
			object.modelData[2][c][planes - 4] = RED;
		}

		if (c != 3) {
			object.modelData[6][c][planes - 3] = RED;
			wall.modelData[6][c][0] = NONE;
		}

		if (c == 2 || c == 4) {
			object.modelData[4][c][planes - 3] = RED;
			wall.modelData[4][c][0] = NONE;

			if (c == 2) {
				object.modelData[6][c][planes - 4] = RED;
				object.modelData[2][c][planes - 2] = RED;
			}

			if (c == 4) {
				object.modelData[6][c][planes - 2] = RED;
				object.modelData[2][c][planes - 4] = RED;
			}

		}
	}

	// bricks for testing
	/*
	modelData[0][0][0] = BLUE;
	modelData[0][6][6] = VIOLET;
	modelData[0][0][6] = VIOLET;
	*/
}

bool ModelDamian::boundaryCollision() {

	glm::vec3* localSpaceCorners = new glm::vec3[4];

	// subtracting 1 to try and align the center of rotation in the middle of the x-axis
	localSpaceCorners[0] = glm::vec3(((float)(columns - 1)*-0.5f)-0.5f, 0.0f, 0.0f);
	localSpaceCorners[1] = glm::vec3(((float)(columns - 1) *0.5f) - 0.5f, 0.0f, 0.0f);
	localSpaceCorners[2] = glm::vec3(((float)(columns - 1) *0.5)-0.5f, 0.0f, (float) planes - 0.5f);
	localSpaceCorners[3] = glm::vec3(((float)(columns - 1) *-0.5) - 0.5f, 0.0f, (float) planes - 0.5f);

	const glm::mat3 rotationMatrix = glm::mat3(
		glm::vec3(glm::cos(yRotation), 0.0f, -glm::sin(yRotation)),
		glm::vec3(0.0f, 1.0f, 0.0f),
		glm::vec3(glm::sin(yRotation), 0.0f, glm::cos(yRotation))
	);
	
	for (int i = 0; i < 4; i++) {

		// rotate corner vector
		localSpaceCorners[i] = rotationMatrix * localSpaceCorners[i];

		// scale corner vector
		localSpaceCorners[i] *= scaleFactor;

		// move corner vector to base position
		localSpaceCorners[i] = glm::vec3(
			localSpaceCorners[i].x + modelBasePosition.x,
			localSpaceCorners[i].y + modelBasePosition.y,
			localSpaceCorners[i].z + modelBasePosition.z
			);

		// apply any x or y translations to corner vector
		if (xTranslation < 0) {
			localSpaceCorners[i] = glm::vec3(localSpaceCorners[i].x + xTranslation - 0.05f, localSpaceCorners[i].y + yTranslation, localSpaceCorners[i].z);
		}
		else {
			localSpaceCorners[i] = glm::vec3(localSpaceCorners[i].x + xTranslation + 0.05f, localSpaceCorners[i].y + yTranslation, localSpaceCorners[i].z);
		}

		// check x boundary
		if(localSpaceCorners[i].x < -10.1f || localSpaceCorners[i].x > 10.1f) {
			return true;
		}

		// check y boundary (only applies to y translation, not scaling)
		if (localSpaceCorners[i].y <= 0) {
			return true;
		}

		//check z boundary
		if (localSpaceCorners[i].z <= -10.0f || localSpaceCorners[i].z >= 10.0f) {
			return true;
		}
	}
	return false;
}