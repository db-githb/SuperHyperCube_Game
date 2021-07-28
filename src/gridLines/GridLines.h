#pragma once
#include "../unitLine/UnitLine.h"

class GridLines {
public:
	GridLines();
	void draw(Camera inCam, glm::mat4 projection, glm::mat4 view, glm::mat4 model);

private:
	UnitLine unitLine;
	Shader gridLinesShader;
};
