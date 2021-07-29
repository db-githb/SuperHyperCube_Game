#pragma once
#include "../unitCube/UnitCube.h"
#include "../modelBase/modelBase.h"

class LightCube {
public:
	LightCube();
	void draw(glm::mat4 projection, glm::mat4 view, glm::mat4 model, ModelBase activeModel);

	glm::vec3 position;

private:
	UnitCube unitCube;
	Shader lightCubeShader;
};
