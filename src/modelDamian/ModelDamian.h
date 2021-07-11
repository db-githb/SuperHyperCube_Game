#pragma once
#include "../unitCube/UnitCube.h"

#define ROWS 9
#define COLUMNS 7

#define WALL 0
#define BLUE 1
#define RED 2

class ModelDamian {

public:
	ModelDamian();
	void draw(Camera inCam, glm::vec3* dirLight, glm::mat4 projection, glm::mat4 view, glm::mat4 model);

private:
	UnitCube unitCube;
	Shader damiansShader;
	int modelData[ROWS][COLUMNS];
};