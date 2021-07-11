#include "ModelBase.h"

ModelBase::ModelBase() {
	unitCube = UnitCube();
	baseShader = Shader("res/shaders/baseShader.vert", "res/shaders/baseShader.frag");
}

void ModelBase::initialize() {
	modelBasePosition = glm::vec3(-5.0f, 0.5f, 0.0f);
	return;
}

void ModelBase::draw(Camera inCam, glm::vec3* dirLight, glm::mat4 projection, glm::mat4 view, glm::mat4 model) {

	baseShader.use();

	baseShader.setVec3("viewPos", inCam.Position);

	baseShader.setVec3("dirLight.direction", dirLight[LIGHT_DIRECTION]);
	baseShader.setVec3("dirLight.ambient", dirLight[LIGHT_AMBIENT]);
	baseShader.setVec3("dirLight.diffuse", dirLight[LIGHT_DIFFUSE]);
	baseShader.setVec3("dirLight.specular", dirLight[LIGHT_SPECULAR]);

	baseShader.setMat4("projection", projection);
	baseShader.setMat4("view", view);

	// world transformation
	model = glm::translate(model, modelBasePosition);
	baseShader.setMat4("model", model);

	// render the cubes
	glBindVertexArray(unitCube.getVAO());

	glDrawArrays(GL_TRIANGLES, 0, 36);
}