#pragma once
#include "../unitCube/UnitCube.h"

#define LIGHT_DIRECTION 0 
#define LIGHT_AMBIENT 1
#define LIGHT_DIFFUSE 2
#define LIGHT_SPECULAR 3

#define SCALE_UP 0
#define SCALE_DOWN 1

class ModelBase {

public:
	ModelBase();
	virtual void initialize();
	virtual void draw(Camera inCam, glm::vec3* dirLight, glm::mat4 projection, glm::mat4 view, glm::mat4 model);
	virtual void scale(int scaleDirection);

protected:
	UnitCube unitCube;
	Shader baseShader;
	glm::vec3 modelBasePosition;
	float scaleFactor;
};