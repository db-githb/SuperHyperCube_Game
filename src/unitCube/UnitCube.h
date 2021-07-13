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

class UnitCube {
public:
	UnitCube();
	void createCube();
	GLuint getVAO();
	GLuint getVBO();

private:
	GLuint unitCubeVBO, unitCubeVAO;
};