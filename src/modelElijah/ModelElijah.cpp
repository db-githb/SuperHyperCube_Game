#include "ModelElijah.h"

     ModelElijah::ModelElijah()
	{
		transform.position = glm::vec3(-5.0f, 0.5f, 7.0f);
	}

void ModelElijah::initialize() {

	modelBasePosition = glm::vec3(-5.0f, 0.5f, 7.0f);

	// initialize entire model to a wall or none (no unit cube)
	for (int x = 0; x < sizeX; x++) 
	{
		for (int y = 0; y < sizeY; y++) 
		{
			for (int z = 0; z < sizeZ; z++)
			{
				if (z == 0)
				{
					modelData[x][y][z] = WALL;
				}
				else
				{
					modelData[x][y][z] = NONE;
				}
			}
		}
	}

	for (int y = 1; y < sizeY - 1; y++)
	{
		for (int x = 1; x < sizeX - 1; x++)
		{
			for (int z = 2; z < sizeZ; z++)
			{
				if (y == 1 || y == sizeY - 2)
					modelData[x][y][z] = BLUE;
				if (y == 2 || y == sizeY - 3 && (x >=2 && x <= sizeX - 2))
					modelData[x][y][z] = BLUE;
				/*if (y == 3 || y == sizeY - 4)
					modelData[x][y][z] = BLUE;*/

			}
		}
			
		
	}

	// reset unitCubes in the model to their respective colors
	/*for (int y = 1; y < 8; y++) {
		modelData[3][y][sizeZ - 1] = BLUE;
		modelData[3][y][0] = NONE;
	}

	for (int x = 1; x < 6; x++) {

		modelData[x][2][sizeZ - 1] = RED;
		modelData[x][2][0] = NONE;

		if (x != 3) {
			modelData[x][7][sizeZ - 1] = RED;
			modelData[x][7][0] = NONE;
		}

		if (x == 2 || x == 4) {
			modelData[x][3][sizeZ - 1] = RED;
			modelData[x][3][0] = NONE;
		}
	}*/

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
	for (int c = 0; c < sizeX; c++)
	{
		for (int r = 0; r < sizeY; r++)
		{
			for (int p = 0; p < sizeZ; p++) 
			{

				if (modelData[c][r][p] == NONE) 
				{
					continue;
				}

				// scale position of each unitCube
				float x = (float)c * scaleFactor;
				float y = (float)r * scaleFactor;
				float z = (float)p * scaleFactor;

				// ensure that the model matrix passed is an identity matri;

				// translation vector to move unit cube from base position
				glm::vec3 translation = glm::vec3(x, y, z);
				transform.matrix = glm::translate(glm::mat4(1.0f) , (transform.position +  glm::vec3(xTranslation*scaleFactor, yTranslation*scaleFactor, 0.0f)));
				//modelPosition = glm::scale(modelPosition, glm::vec3(1.0f) * scaleFactor);

				// apply any rotation to the model
				model = glm::rotate(transform.matrix, orientation, glm::vec3(0.0f, 1.0f, 0.0f));
				
				if (modelData[c][r][p] == WALL) 
					baseShader.setVec3("dirLight.ambient", dirLight[LIGHT_AMBIENT]); // shader colors the wall unit cube grey
				else 
				{
					// if-else statement colors the object cubes either red or blue
					if (modelData[c][r][p] == RED) 
					{
						baseShader.setVec3("dirLight.ambient", glm::vec3(0.0f, 1.0f, 0.0f));
					}
					else 
					{
						baseShader.setVec3("dirLight.ambient", glm::vec3(0.5f, 0.0f, 0.5f));
					}
				}

				// translation vector to move unit cube from base position
				model = glm::translate(model, translation + glm::vec3(scaleFactor*(-COLUMNS / 2), 0.0f, scaleFactor * (-PLANES / 2)));
				

				// scale the size of each cube
				model = glm::scale(model, glm::vec3(1.0f) * scaleFactor);
				
				// pass the model matrix to the vertex shader
				baseShader.setMat4("model", model);

				// render the cube
				glBindVertexArray(unitCube.getVAO());
				glDrawArrays(renderMode, 0, 36);

				glBindVertexArray(unitCube.getVAO());
				baseShader.setMat4("model", transform.matrix);
				baseShader.setVec3("dirLight.ambient", glm::vec3(1.0f, 1.0f, 1.0f));
				glDrawArrays(renderMode, 0, 36);

			}

		}
	}
}