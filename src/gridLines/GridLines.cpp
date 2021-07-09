#include "GridLines.h"

GridLines::GridLines() {
	unitLine = new UnitLine();
	gridLinesShader = new Shader("res/shaders/gridLineShader.vert", "res/shaders/gridLineShader.frag");
}

void GridLines::draw(Camera camera, glm::mat4 projection, glm::mat4 view, glm::mat4 model) {
	
	gridLinesShader->use();
	gridLinesShader->setMat4("projection", projection);
	gridLinesShader->setMat4("view", view);

	// lines parallel to z-axis
	for (int i = 0; i < 101; i++) {
		model = glm::scale(glm::mat4(1.0f), glm::vec3(0.2f));
		model = glm::translate(model, glm::vec3(-50.0 + (float)i, 0.0f, 0.0f));
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 50.0f));
		model = glm::scale(model, glm::vec3(100.0f, 100.0f, 100.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		gridLinesShader->setMat4("model", model);
		glBindVertexArray(unitLine->getVAO());
		glDrawArrays(GL_LINES, 0, 2);
	}

	// lines perpendicular to z-axis
	for (int i = 0; i < 101; i++) {
		model = glm::scale(glm::mat4(1.0f), glm::vec3(0.2f));
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -50.0 + (float)i));
		model = glm::translate(model, glm::vec3(-50.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(100.0f, 100.0f, 100.0f));
		gridLinesShader->setMat4("model", model);
		glBindVertexArray(unitLine->getVAO());
		glDrawArrays(GL_LINES, 0, 2);
	}
}