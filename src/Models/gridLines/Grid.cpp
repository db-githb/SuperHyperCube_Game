#include "Grid.h"

Grid::Grid() {
	unitLine = UnitLine();
	gridShader =  Shader("res/shaders/gridLineShader.vert", "res/shaders/gridLineShader.frag");
}

void Grid::draw(Camera camera, glm::mat4 projection, glm::mat4 view, glm::mat4 model) {
	
	gridShader.use();
	gridShader.setMat4("projection", projection);
	gridShader.setMat4("view", view);

	// lines parallel to z-axis
	for (int i = 0; i < 101; i++) {
		if (i % 5 == 0)
			gridShader.setVec4("Color", glm::vec4(1, 0, 1, 1));
		else
			gridShader.setVec4("Color", glm::vec4(0.5f, 1, 0.5f, 1));
		model = glm::scale(glm::mat4(1.0f), glm::vec3(0.2f));
		model = glm::translate(model, glm::vec3(-50.0 + (float)i, 0.0f, 0.0f));
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 50.0f));
		model = glm::scale(model, glm::vec3(100.0f, 100.0f, 100.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		gridShader.setMat4("model", model);
		glBindVertexArray(unitLine.getVAO());
		glDrawArrays(GL_LINES, 0, 2);
	}

	// lines perpendicular to z-axis
	for (int i = 0; i < 101; i++) {
		if (i % 5 == 0)
			gridShader.setVec4("Color", glm::vec4(1, 0, 1, 1));
		else
			gridShader.setVec4("Color", glm::vec4(0.5f, 1, 0.5f, 1));
		model = glm::scale(glm::mat4(1.0f), glm::vec3(0.2f));
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -50.0 + (float)i));
		model = glm::translate(model, glm::vec3(-50.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(100.0f, 100.0f, 100.0f));
		gridShader.setMat4("model", model);
		glBindVertexArray(unitLine.getVAO());
		glDrawArrays(GL_LINES, 0, 2);
	}
}