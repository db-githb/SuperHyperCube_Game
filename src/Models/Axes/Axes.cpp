#include "Axes.h"

Axes::Axes() {
	unitLine = UnitLine();
	axesShader =  Shader("res/shaders/axisShader.vert", "res/shaders/axisShader.frag");
}

void Axes::draw(Camera camera, glm::mat4 projection, glm::mat4 view, glm::mat4 model) {
	
	axesShader.use();

	axesShader.setMat4("projection", projection);
	axesShader.setMat4("view", view);

	for (int i = 0; i < 3; i++) {

		switch (i) {
		case 0:
			axesShader.setInt("xAxis", 1);
			axesShader.setVec3("color", glm::vec3(1.0, 0.0, 0.0));
			break;

		case 1:
			model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
			axesShader.setInt("yAxis", 1);
			axesShader.setVec3("color", glm::vec3(0.0, 1.0, 0.0));
			break;

		case 2:
			model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			axesShader.setInt("zAxis", 1);
			axesShader.setVec3("color", glm::vec3(0.0, 0.0, 1.0));
			break;
		}

		axesShader.setMat4("model", model);
		glBindVertexArray(unitLine.getVAO());
		glDrawArrays(GL_LINES, 0, 2);
	}
}