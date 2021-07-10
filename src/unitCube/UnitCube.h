#pragma once
#include "../main/Main.h"

class UnitCube {
public:
	UnitCube();
	void createCube();
	void draw(Camera inCam, glm::vec3* dirLight, glm::mat4 projection, glm::mat4 view, glm::mat4 model);
	GLuint getVAO();
	GLuint getVBO();

private:
	GLuint unitCubeVBO, unitCubeVAO;
	Shader cubeShader;
};