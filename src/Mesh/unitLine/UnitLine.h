#pragma once
//#include "../../Application/Main.h"
#include <iostream>
#include <stdio.h>
#include <string.h>
#include "../../glad/glad.h"
#include "../../lib/glfw-3.3.2.bin.WIN32/include/GLFW/glfw3.h"
#include "../../glm/glm.hpp"
#include "../../glm/gtc/matrix_transform.hpp"
#include "../../glm/gtc/type_ptr.hpp"
#include "../../Shader/Shader.h"
#include "../../Camera/Camera.h"


class UnitLine {
public:
	UnitLine();
	void createLine();
	void draw(Camera inCam, glm::mat4 inProj, glm::mat4 inView, glm::mat4 inModel);
	GLuint getVAO();
	GLuint getVBO();

private:
	GLuint unitLineVBO, unitLineVAO;
	Shader lineShader;
};