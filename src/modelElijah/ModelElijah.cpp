#include "ModelElijah.h"

void ModelElijah::initialize() {

	modelBasePosition = glm::vec3(0.0f, 0.5f, 7.0f);

	// initialize entire model to a wall or none (no unit cube)
	for (int r = 0; r < ROWS; r++) {
		for (int c = 0; c < COLUMNS; c++) {
			for (int p = 0; p < PLANES; p++)
				if (p == 0) {
					modelData[r][c][p] = WALL;
				}
				else {
					modelData[r][c][p] = NONE;
				}
		}
	}

	// reset unitCubes in the model to their respective colors
	for (int r = 1; r < 8; r++) {
		modelData[r][3][PLANES - 1] = BLUE;
		modelData[r][3][0] = NONE;
	}

	for (int c = 1; c < 6; c++) {

		modelData[2][c][PLANES - 1] = RED;
		modelData[2][c][0] = NONE;

		if (c != 3) {
			modelData[6][c][PLANES - 1] = RED;
			modelData[6][c][0] = NONE;
		}

		if (c == 2 || c == 4) {
			modelData[4][c][PLANES - 1] = RED;
			modelData[4][c][0] = NONE;
		}
	}

}

// draw method works by rendering each unit cube in the model
void ModelElijah::draw(Camera inCam, glm::vec3* dirLight, glm::mat4 projection, glm::mat4 view, glm::mat4 model) {

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
				glm::mat4 modelPosition = glm::translate(model , modelBasePosition + glm::vec3(xTranslation, yTranslation, 0.0f));
				// apply any rotation to the model

				model = glm::rotate(modelPosition, orientation, glm::vec3(0.0f, 1.0f, 0.0f));
				
				// wall cubes are offset from a different base position then the object cubes
				if (modelData[r][c][p] == WALL) {

					// shader colors the wall unit cube grey
					baseShader.setVec3("dirLight.ambient", dirLight[LIGHT_AMBIENT]);

					// translation vector to move unit cube from base position
					glm::vec3 translation = glm::vec3(x, y, z);

					// TODO: make base position a variable (currently it's a constant)
					model = glm::translate(model,translation + glm::vec3(-COLUMNS / 2, 0.0f, 0.0f));
				}
				else {
					// translation vector to move unit cube from base position
					glm::vec3 translation = glm::vec3(x, y, z);

					// translation vector to move unit cube from base position
					model = glm::translate(model,translation + glm::vec3(-COLUMNS/2, 0.0f, 0.0f));

					// if-else statement colors the object cubes either red or blue
					if (modelData[r][c][p] == RED) {
						baseShader.setVec3("dirLight.ambient", glm::vec3(0.0f, 1.0f, 0.0f));
					}
					else {
						baseShader.setVec3("dirLight.ambient", glm::vec3(0.5f, 0.0f, 0.5f));
					}
				}
				

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