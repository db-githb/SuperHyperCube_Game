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

#define LIGHT_DIRECTION 0
#define LIGHT_AMBIENT 1
#define LIGHT_DIFFUSE 2
#define LIGHT_SPECULAR 3

#define POINT_LIGHT_POSITION 0
#define POINT_LIGHT_AMBIENT 1
#define POINT_LIGHT_DIFFUSE 2
#define POINT_LIGHT_SPECULAR 3
#define POINT_LIGHT_ATTENUATION 3


class UnitCube {
public:
	UnitCube();
	void createCube();
	static GLuint getVAO();
	GLuint getVBO();

	// directional lighting values
	static glm::vec3* pointLight;

private:
	static GLuint unitCubeVBO, unitCubeVAO;
};