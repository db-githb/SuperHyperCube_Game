#pragma once
#include "../../Application/Main.h"

class Grid {
public:
	Grid();
	void draw(Camera inCam, glm::mat4 projection, glm::mat4 view, glm::mat4 model);

private:
	UnitLine unitLine;
	Shader gridShader;
};
