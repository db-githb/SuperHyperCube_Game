#include "LightCube.h"

LightCube::LightCube() {
	unitCube = UnitCube();
	lightCubeShader = Shader("res/shaders/cubeShader.vert", "res/shaders/cubeShader.frag");

	lightCubeShader.use();
	lightCubeShader.setVec3("color", glm::vec3(1.0f, 1.0f, 1.0f));
}

void LightCube::draw(glm::mat4 projection, glm::mat4 view, glm::vec3 activePosition) {

	lightCubeShader.use();
	
	lightCubeShader.setMat4("projection", projection);
	lightCubeShader.setMat4("view", view);

	glm::mat4 model = glm::mat4(1.0f);
	// translate each axis line up .05 along the y-axis so they are visible against the grid lines
	model = glm::translate(model, activePosition);

	lightCubeShader.setMat4("model", model);
	glBindVertexArray(unitCube.getVAO());

	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
}