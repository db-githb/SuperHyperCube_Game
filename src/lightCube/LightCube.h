#pragma once
#include "../unitCube/UnitCube.h"

class LightCube {
public:
	LightCube();
	void draw(glm::mat4 projection, glm::mat4 view, glm::vec3 activePosition);

private:
	UnitCube unitCube;
	Shader lightCubeShader;
};
