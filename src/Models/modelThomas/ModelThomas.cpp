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
					modelData[r][c][p] = WALL;
				}
				else {
					modelData[r][c][p] = NONE;
				}
			}
		}
	}
}

void ModelThomas::generateOriginalObject() {

	resetModel();

	for (int r = 2; r < 8; r++) {
		modelData[r][1][PLANES - 3] = YELLOW;
		modelData[r][1][0] = NONE;
	}

	for (int c = 1; c < 6; c++) {
		modelData[1][c][PLANES - 3] = YELLOW;
		modelData[1][c][0] = NONE;
	}

	for (int r = 2; r < 8; r++) {
		modelData[r][1][PLANES - 2] = YELLOW;
		modelData[r][1][0] = NONE;
	}

	for (int c = 1; c < 6; c++) {
		modelData[1][c][PLANES - 2] = YELLOW;
		modelData[1][c][0] = NONE;
	}

	modelData[2][2][0] = NONE;
	for (int p = 2; p < 6; p++) {
		modelData[2][2][p] = ORANGE;
	}

	modelData[5][2][0] = NONE;
	for (int p = 2; p < 6; p++) {
		modelData[5][2][p] = ORANGE;
	}

	for (int r = 2; r < 6; r++) {
		modelData[r][1][PLANES - 1] = ORANGE;
	}
}

void ModelThomas::generateRandomModel() {

	resetModel();

	for (int r = 2; r < 8; r++) {
		
		modelData[r][1][0] = NONE;

		if ((rand() % 10 == 0)) {
			continue;
		}

		for (int p = 2; p < PLANES; p++)
			if ((rand() % 2 == 1)) {
				modelData[r][1][p] = rand() % NUM_COLORS;
			}
	}

	for (int c = 1; c < 6; c++) {
		modelData[1][c][0] = NONE;

		if ((rand() % 10 == 0)) {
			continue;
		}

		for (int p = 2; p < PLANES; p++)
			if ((rand() % 2 == 1)) {
				modelData[1][c][p] =  rand() % NUM_COLORS;
			}
	}

	modelData[2][2][0] = NONE;
	modelData[5][2][0] = NONE;

	for (int p = 2; p < PLANES; p++) {
		if ((rand() % 10 == 0)) {
			continue;
		}

		if ((rand() % 2 == 1)) {
			modelData[2][2][p] = rand() % NUM_COLORS;
		}
	}

	
	for (int p = 2; p < PLANES; p++) {
		if ((rand() % 10 == 0)) {
			continue;
		}

		if ((rand() % 2 == 1)) {
			modelData[5][2][p] = rand() % NUM_COLORS;
		}
	}


}

void ModelThomas::draw(Camera inCam, glm::vec3* dirLight, glm::mat4 projection, glm::mat4 view, glm::mat4 model) {
	// activate the shader
	baseShader.use();

	// pass the camera position to the fragment shader.  This determines what is "shadowed" and what isn't relative to the camera.
	baseShader.setVec3("viewPos", inCam.Position);

	// pass the color/lighting values to the fragment shader (at this point in time outside of some shadowing on the faces of the unit cube not directly facing the light this pretty much colors the unit cubes.
	baseShader.setVec3("dirLight.direction", dirLight[LIGHT_DIRECTION]);
	baseShader.setVec3("dirLight.ambient", dirLight[LIGHT_AMBIENT]);
	baseShader.setVec3("dirLight.diffuse", dirLight[LIGHT_DIFFUSE]);
	baseShader.setVec3("dirLight.specular", dirLight[LIGHT_SPECULAR]);

	// pass transformation matrices to the vertex shader.  The model matrix is passed at the end after all the world transformations are applied to the unit cube.
	baseShader.setMat4("projection", projection);
	baseShader.setMat4("view", view);

	// world transformation: glm::translate moves the model around the world
	for (int r = 0; r < ROWS; r++) {
		for (int c = 0; c < COLUMNS; c++) {
			for (int p = 0; p < PLANES; p++) {

				if (modelData[r][c][p] == NONE) {
					continue;
				}

				// scale position of each unitCube
				float x = (float)c * scaleFactor;
				float y = (float)r * scaleFactor;
				float z = (float)p * scaleFactor;

				// ensure that the model matrix passed is an identity matrix
				model = glm::mat4(1.0f);

				// translation vector to move unit cube from base position
				glm::vec3 translation = glm::vec3(x, y, z);

				model = glm::translate(model, (modelBasePosition + glm::vec3(xTranslation * scaleFactor, yTranslation * scaleFactor, 0.0f)));

				// apply any rotation to the model
				model = glm::rotate(model, orientation, glm::vec3(0.0f, 1.0f, 0.0f));

				// wall cubes are offset from a different base position then the object cubes
				if (modelData[r][c][p] == WALL) {

					// shader colors the wall unit cube grey
					baseShader.setVec3("dirLight.ambient", dirLight[LIGHT_AMBIENT]);

				}
				else {
					// color value applied through enums
					baseShader.setVec3("dirLight.ambient", colorPalette[modelData[r][c][p]]);
					
				}

				model = glm::translate(model, translation+ glm::vec3(scaleFactor*(-COLUMNS*0.5),0.0f,scaleFactor*(-PLANES/2)));

				// scale the size of each cube
				model = glm::scale(model, glm::vec3(1.0f) * scaleFactor);

				// pass the model matrix to the vertex shader
				baseShader.setMat4("model", model);

				// render the cube
				glBindVertexArray(unitCube.getVAO());
				glDrawArrays(renderMode, 0, 36);

			}

		}
	}
}

