#include "WorldCube.h"

WorldCube::WorldCube()
{
	transform.SetPosition(glm::vec3(0, 0, 0));
	transform.SetScale(glm::vec3(50, 50, 50));
}

void WorldCube::Draw(Shader& shader)
{
	shader.use();
	// Set colour to "Sky Blue"
	shader.setVec3("dirLight.ambient", glm::vec3(0.53f, 0.81f, 0.92f));
	shader.setMat4("model", transform.GetModel());
	glBindVertexArray(unitCube.getVAO());
	glDrawArrays(renderMode, 0, 36);
}