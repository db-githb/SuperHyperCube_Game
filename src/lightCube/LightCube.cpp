#include "LightCube.h"

LightCube::LightCube() {
	unitCube = UnitCube();
	lightCubeShader = Shader("res/shaders/cubeShader.vert", "res/shaders/cubeShader.frag");

	position = UnitCube::pointLight[POINT_LIGHT_POSITION];

	lightCubeShader.use();
	lightCubeShader.setVec3("color", glm::vec3(1.0f, 1.0f, 1.0f));
}

void LightCube::draw(glm::mat4 projection, glm::mat4 view, glm::mat4 model, ModelBase activeModel) {

	lightCubeShader.use();
	
	lightCubeShader.setMat4("projection", projection);
	lightCubeShader.setMat4("view", view);

	// translate each axis line up .05 along the y-axis so they are visible against the grid lines
	model = glm::translate(model, activeModel.modelBasePosition + glm::vec3(0.0f, 30.0f, 0.0f));

	lightCubeShader.setMat4("model", model);
	glBindVertexArray(unitCube.getVAO());

	glDrawArrays(GL_TRIANGLES, 0, 36);
}