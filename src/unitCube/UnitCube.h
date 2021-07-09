#pragma once
#include "../main/Main.h"

class UnitCube {
public:
	UnitCube();
	void createCube();
	void draw(Camera inCam, glm::mat4 projection, glm::mat4 view, glm::mat4 model);

private:
	GLuint unitCubeVBO, unitCubeVAO;
	Shader cubeShader;
};