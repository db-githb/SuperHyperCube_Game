#pragma once
#include "../unitCube/UnitCube.h"

class LightCube {
public:
	LightCube();
	void draw(glm::mat4 projection, glm::mat4 view, glm::mat4 model, glm::vec3 activePosition);

	glm::vec3 position;

private:
	UnitCube unitCube;
	Shader lightCubeShader;
};
