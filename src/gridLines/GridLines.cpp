#include "GridLines.h"

GridLines::GridLines() {
	UnitCube unitCube= UnitCube();
	gridLinesShader =  Shader("res/shaders/cubeShader.vert", "res/shaders/cubeShader.frag");
}

void GridLines::draw(Camera camera, glm::mat4 projection, glm::mat4 view, glm::mat4 model) {
	
	gridLinesShader.use();
	gridLinesShader.setMat4("projection", projection);
	gridLinesShader.setMat4("view", view);

	for (double z = -50; z < 51; z++) {
		model = glm::mat4(1.0f);
		if ((int)z % 5 == 0) {
			gridLinesShader.setVec3("Color", glm::vec3(.5, 0, .5));
		}
		else {
			gridLinesShader.setVec3("Color", glm::vec3(0.0, 0.5, 0.0));
		}
		model = glm::translate(model, glm::vec3(0.0, 0.0, z));
		model = glm::scale(model, glm::vec3(100.0, 0.0, 0.0));
		gridLinesShader.setMat4("model", model);
		glBindVertexArray(unitCube.getVAO());
		glDrawArrays(GL_LINES, 0, 36);
	}

	// lines perpendicular to z-axis
	for (double x = -50; x < 51; x++) {
		model = glm::mat4(1.0f);
		if ((int)x % 5 == 0) {
			gridLinesShader.setVec3("Color", glm::vec3(.5, 0, .5));
		}
		else {
			gridLinesShader.setVec3("Color", glm::vec3(0.0, 0.5, 0.0));
		}

		model = glm::translate(model, glm::vec3(x, 0.0, 0.0));
		model = glm::scale(model, glm::vec3(0.0, 0.0, 100.0));
		gridLinesShader.setMat4("model", model);
		glBindVertexArray(unitCube.getVAO());
		glDrawArrays(GL_LINES, 0, 36);
	}
}