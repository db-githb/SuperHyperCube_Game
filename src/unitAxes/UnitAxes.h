#pragma once

#include <iostream>
#include <stdio.h>
#include <string.h>
#include "../../glad/glad.h"
#include "../../lib/glfw-3.3.2.bin.WIN32/include/GLFW/glfw3.h"
#include "../../glm/glm.hpp"
#include "../../glm/gtc/matrix_transform.hpp"
#include "../../glm/gtc/type_ptr.hpp"
#include "../shader/Shader.h"
#include "../camera/Camera.h"

#include "../unitLine/UnitLine.h"

class UnitAxes {
public:
	UnitAxes();
	void draw(Camera inCam, glm::mat4 projection, glm::mat4 view);

private:
	UnitLine unitLine;
	Shader axesShader;
};