#include "ModelKayla.h"

void ModelKayla::initialize() {

	positionModel(9.0f, 0.5f, 5.5f);
	generateOriginalObject();
}

// draw method works by rendering each unit cube in the model
void ModelKayla::draw(Camera inCam, glm::vec3* dirLight, glm::mat4 projection, glm::mat4 view, glm::mat4 model) {

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

	// put this in base class or leave 

	const glm::mat3 rotationMatrix = glm::mat3(
		glm::vec3(glm::cos(orientation), 0.0f, -glm::sin(orientation)),
		glm::vec3(0.0f, 1.0f, 0.0f),
		glm::vec3(glm::sin(orientation), 0.0f, glm::cos(orientation))
	);

	// world transformation: glm::translate moves the model around the world
	for (int r = 0; r < ROWS; r++) {
		for (int c = 0; c < COLUMNS; c++) {
			for (int p = 0; p < PLANES; p++) {

				if (modelData[r][c][p] == NONE) {
					continue;
				}

				// scale position of each unitCube
				// positions of each cube are relative to the axis of rotation
				float x = ((float)c - (COLUMNS * 0.5f)) * scaleFactor;
				float y = (float)r * scaleFactor;
				float z = ((float)p - 0.5f) * scaleFactor;

				// translation vector to move unit cube from base position
				glm::vec3 translation = glm::vec3(x, y, z);

				// apply a rotation to the translation vector so that the position of the unit cube is synchronized with the orientation of the cube
				translation = rotationMatrix * translation;


				// ensure that the model matrix passed is an identity matrix
				model = glm::mat4(1.0f);

				// apply any x or y translations
				model = glm::translate(model, glm::vec3(xTranslation, yTranslation, 0.0f));

				// wall cubes are offset from a different base position then the object cubes
				if (modelData[r][c][p] == WALL) {

					// shader colors the wall unit cube grey
					baseShader.setVec3("dirLight.ambient", dirLight[LIGHT_AMBIENT]);

					// TODO: make base position a variable (currently it's a constant)
					model = glm::translate(model, modelBasePosition + translation);

				}
				else {

					// translation vector to move unit cube from base position
					model = glm::translate(model, modelBasePosition + translation);

					// if-else statement colors the object cubes either red or blue
					if (modelData[r][c][p] == RED) {
						baseShader.setVec3("dirLight.ambient", glm::vec3(0.0f, 3.0f, 1.0f));
					}
					else {
						baseShader.setVec3("dirLight.ambient", glm::vec3(1.0f, 0.0f, 1.0f));
					}
				}

				// scale the size of each cube
				model = glm::scale(model, glm::vec3(1.0f) * scaleFactor);

				// apply the unit cube so that the cube's orientation is aligned with the model's orientation
				model = glm::rotate(model, orientation, glm::vec3(0.0f, 1.0f, 0.0f));

				// pass the model matrix to the vertex shader
				baseShader.setMat4("model", model);

				// render the cube
				glBindVertexArray(unitCube.getVAO());
				glDrawArrays(renderMode, 0, 36);

			}
		}
	}
}

void ModelKayla::positionModel(float x, float y, float z)
{
	modelBasePosition = glm::vec3(x, y, z);
}

void ModelKayla::generateOriginalObject()
{
	// initialize entire model to a wall or none (no unit cube)
	resetModel();

	// reset unitCubes in the model to their respective colors
	resetUnitCubes();
}

int* ModelKayla::generateRandomModel(int x, int y, int z) 
{
	resetModel();
	//Generate a random number of cubes
	int numCubes = rand() % 25 + 3;
	for (int i = 0; i < numCubes; i++)
	{
		generateCube(rand() % 7 + 1, rand() % 7 + 1, rand() % 5 + 1, rand() % 5 + 1, rand() % 5 + 1, rand() % 5 + 1, rand() % 2 + 1);
	}

	return NULL;
}

void ModelKayla::resetModel()
{
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
}

void ModelKayla::generateCube(int rowStart, int rowEnd, int columnStart, int columnEnd, int planeStart, int planeEnd, int color)
{
	//Validating cube values
	if (!((rowStart > rowEnd) || (columnStart > columnEnd) || (planeStart > planeEnd))) {
		for (int c = columnStart; c < columnEnd+1; c++) {
			for (int r = rowStart; r < rowEnd+1; r++) {
				for (int p = planeStart; p < planeEnd+1; p++) {
					modelData[r][c][PLANES - p] = color;
				}
				//Make hole
				modelData[r][c][0] = NONE;
			}
		}
	}
}

void ModelKayla::resetUnitCubes()
{
	generateCube(5, 7, 1, 2, 3, 4, RED);
	generateCube(2, 2, 1, 5, 2, 2, BLUE);
	generateCube(3, 3, 4, 4, 2, 3, RED);
	generateCube(4, 5, 3, 3, 1, 1, BLUE);
}