#pragma once
#include "../unitCube/UnitCube.h"

class ModelDamian {
public:
	ModelDamian();
	void draw(Camera inCam, glm::vec3* dirLight, glm::mat4 projection, glm::mat4 view, glm::mat4 model);

private:
	UnitCube unitCube;
	Shader damiansShader;
};