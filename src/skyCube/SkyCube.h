#pragma once
#include "../unitCube/UnitCube.h"

class SkyCube {
public:
	SkyCube();
	void draw(glm::mat4 projection, glm::mat4 view);
	~SkyCube();

private:
	UnitCube unitCube;
	Shader skyCubeShader;
	unsigned int image;
	glm::vec3 positions[5];
	glm::vec3 scaleVec[5];
	float scaleFactor;
};
