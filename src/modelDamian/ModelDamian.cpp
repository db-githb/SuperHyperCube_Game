#include "ModelDamian.h"

ModelDamian::ModelDamian() {
	unitCube = UnitCube();
	damiansShader = Shader("res/shaders/modelDamian.vert", "res/shaders/modelDamian.frag");

	for (int r = 0; r < ROWS; r++) {
		for (int c = 0; c < COLUMNS; c++) {
			modelData[r][c] = WALL;
		}
	}

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

void ModelDamian::draw(Camera inCam, glm::vec3* dirLight, glm::mat4 projection, glm::mat4 view, glm::mat4 model) {

	damiansShader.use();

	damiansShader.setVec3("viewPos", inCam.Position);

	damiansShader.setVec3("dirLight.direction", dirLight[LIGHT_DIRECTION]);
	damiansShader.setVec3("dirLight.ambient", dirLight[LIGHT_AMBIENT]);
	damiansShader.setVec3("dirLight.diffuse", dirLight[LIGHT_DIFFUSE]);
	damiansShader.setVec3("dirLight.specular", dirLight[LIGHT_SPECULAR]);

	damiansShader.setMat4("projection", projection);
	damiansShader.setMat4("view", view);

	for (int r = 0; r < ROWS; r++) {
		for (int c = 0; c < COLUMNS; c++) {
			float x = (float)c;
			float y = (float)r;
			
			model = glm::mat4(1.0f);

			if (modelData[r][c] == WALL) {
				damiansShader.setVec3("dirLight.ambient", dirLight[LIGHT_AMBIENT]);
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

			damiansShader.setMat4("model", model);
			glBindVertexArray(unitCube.getVAO());
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
	}
}