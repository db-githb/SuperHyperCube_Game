#pragma once
#include "../unitCube/UnitCube.h"

class GridLines {
public:
	GridLines();
	void draw(Camera inCam, glm::mat4 projection, glm::mat4 view, glm::mat4 model);

private:
	UnitCube unitCube;
	Shader gridLinesShader;
};
