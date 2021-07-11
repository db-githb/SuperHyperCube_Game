#pragma once
#include "../unitCube/UnitCube.h"

#define LIGHT_DIRECTION 0 
#define LIGHT_AMBIENT 1
#define LIGHT_DIFFUSE 2
#define LIGHT_SPECULAR 3

class ModelBase {

public:
	UnitCube unitCube;
	Shader baseShader;
	glm::vec3 modelBasePosition;

	ModelBase();
	virtual void initialize();
	virtual void draw(Camera inCam, glm::vec3* dirLight, glm::mat4 projection, glm::mat4 view, glm::mat4 model);

};