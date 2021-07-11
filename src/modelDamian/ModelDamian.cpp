#include "ModelDamian.h"

ModelDamian::ModelDamian() {
	unitCube = UnitCube();
	damiansShader = Shader("res/shaders/modelDamian.vert", "res/shaders/modelDamian.frag");
	
	// initialize entire model to a wall
	for (int r = 0; r < ROWS; r++) {
		for (int c = 0; c < COLUMNS; c++) {
			modelData[r][c] = WALL;
		}
	}

	// reset unitCubes in the model to their color
	for (int r = 1; r < 8; r++) {
		modelData[r][3] = BLUE;
	}

	for (int c = 1; c < 6; c++) {
		
		modelData[2][c] = RED;

		if (c != 3) {
			modelData[6][c] = RED;
		}
		
		if (c == 2 || c == 4) {
			modelData[4][c] = RED;
		}
	}

}

// draw method works by rendering each unit cube in the model
void ModelDamian::draw(Camera inCam, glm::vec3* dirLight, glm::mat4 projection, glm::mat4 view, glm::mat4 model) {

	// activate the shader
	damiansShader.use();

	// pass the camera position to the fragment shader.  This determines what is "shadowed" and what isn't relative to the camera.
	damiansShader.setVec3("viewPos", inCam.Position);

	// pass the color/lighting values to the fragment shader (at this point in time outside of some shadowing on the faces of the unit cube not directly facing the light this pretty much colors the unit cubes.
	damiansShader.setVec3("dirLight.direction", dirLight[LIGHT_DIRECTION]);
	damiansShader.setVec3("dirLight.ambient", dirLight[LIGHT_AMBIENT]);
	damiansShader.setVec3("dirLight.diffuse", dirLight[LIGHT_DIFFUSE]);
	damiansShader.setVec3("dirLight.specular", dirLight[LIGHT_SPECULAR]);

	// pass transformation matrices to the vertex shader.  The model matrix is passed at the end after all the world transformations are applied to the unit cube.
	damiansShader.setMat4("projection", projection);
	damiansShader.setMat4("view", view);

	// world transformation: glm::translate moves the model around the world
	for (int r = 0; r < ROWS; r++) {
		for (int c = 0; c < COLUMNS; c++) {
			float x = (float)c;
			float y = (float)r;
			
			model = glm::mat4(1.0f);

			// wall cubes are offset from a different base position then the object cubes
			if (modelData[r][c] == WALL) {
				damiansShader.setVec3("dirLight.ambient", dirLight[LIGHT_AMBIENT]);

				// TODO: make base position a variable (currently it's a constant)
				model = glm::translate(model, glm::vec3(x + 0.5, y + 0.5f, -2.0f));
			}
			else {
				
				model = glm::translate(model, glm::vec3(x + 0.5, y + 0.5f, 2.0f));

				if (modelData[r][c] == RED) {
					damiansShader.setVec3("dirLight.ambient", glm::vec3(1.0f, 0.0f, 0.0f));
				}
				else {
					damiansShader.setVec3("dirLight.ambient", glm::vec3(0.0f, 0.0f, 1.0f));
				}
			}

			// pass the model matrix to the vertex shader
			damiansShader.setMat4("model", model);

			// render the cube
			glBindVertexArray(unitCube.getVAO());
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
	}
}