#include "UnitAxes.h"

UnitAxes::UnitAxes() {
	unitLine = UnitLine();
	axesShader =  Shader("res/shaders/axisShader.vert", "res/shaders/axisShader.frag");
}

void UnitAxes::draw(Camera camera, glm::mat4 projection, glm::mat4 view, glm::mat4 model) {
	
	axesShader.use();

	axesShader.setMat4("projection", projection);
	axesShader.setMat4("view", view);

	model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
	// translate each axis line up .05 along the y-axis so they are visible against the grid lines
	for (int i = 0; i < 3; i++) {

		switch (i) {
		case 0:
			axesShader.setInt("xAxis", 1);
			axesShader.setVec3("color", glm::vec3(1.0, 0.05, 0.0));
			break;

		case 1:
			model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
			axesShader.setInt("yAxis", 1);
			axesShader.setVec3("color", glm::vec3(0.0, 1.05, 0.0));
			break;

		case 2:
			model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			axesShader.setInt("zAxis", 1);
			axesShader.setVec3("color", glm::vec3(0.0, 0.05, 1.0));
			break;
		}

		axesShader.setMat4("model", model);
		glBindVertexArray(unitLine.getVAO());
		glDrawArrays(GL_LINES, 0, 2);
	}
}