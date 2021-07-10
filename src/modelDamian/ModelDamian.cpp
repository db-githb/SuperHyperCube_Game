#include "ModelDamian.h"

ModelDamian::ModelDamian() {
	unitCube = UnitCube();
	damiansShader = Shader("res/shaders/modelDamian.vert", "res/shaders/modelDamian.frag");
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

	for (int i = 0; i < 1; i++) {
		model = glm::translate(model, glm::vec3(1.0f, 0.5f, 2.0f));
		damiansShader.setMat4("model", model);
		glBindVertexArray(unitCube.getVAO());
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
}