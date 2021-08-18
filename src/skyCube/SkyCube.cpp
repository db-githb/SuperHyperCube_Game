#include "SkyCube.h"

SkyCube::SkyCube() {
	unitCube = UnitCube();
	skyCubeShader = Shader("res/shaders/cubeShader.vert", "res/shaders/cubeShader.frag");

	//skyCubeShader.use();
	image = skyCubeShader.loadTexture("res/images/stars2.png");

	positions[0] = glm::vec3(0.0f, 50.0f, -50.0f);
	positions[1] = glm::vec3(50.0f, 50.0f, 0.0f);
	positions[2] = glm::vec3(0.0f, 50.0f, 50.0f);
	positions[3] = glm::vec3(-50.0f, 50.0f, 0.0f);
	positions[4] = glm::vec3(0.0f, 100.0f, 0.0f);

	scaleFactor = 100.0f;
	scaleVec[0] = glm::vec3(1.0f, 1.0f, 0.01f);
	scaleVec[1] = glm::vec3(0.01f, 1.0f, 1.0f);
	scaleVec[2] = glm::vec3(1.0f, 1.0f, 0.01f);
	scaleVec[3] = glm::vec3(0.01f, 1.0f, 1.0f);
	scaleVec[4] = glm::vec3(1.0f, 0.01f, 1.0f);
}

void SkyCube::draw(glm::mat4 projection, glm::mat4 view) {

	skyCubeShader.use();
	skyCubeShader.setMat4("projection", projection);
	skyCubeShader.setMat4("view", view);

	skyCubeShader.setBool("textureOn", true);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, image);
	for (int i = 0; i < 5; i++) {

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, positions[i]);
		model = glm::scale(model, scaleVec[i] * scaleFactor);
		skyCubeShader.setMat4("model", model);

		glBindVertexArray(unitCube.getVAO());
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
	skyCubeShader.setBool("textureOn", false);
}

SkyCube::~SkyCube() {
	delete &unitCube;
	delete &skyCubeShader;
}