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

#include "UnitLine.h"

UnitLine::UnitLine() {
		createLine();
}

GLuint UnitLine::getVAO() {
	return unitLineVAO;
}

GLuint UnitLine::getVBO() {
	return unitLineVBO;
}

void UnitLine::createLine()
{
	float vertices[] = {
		// position      
		0.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f
	};

	// line VAO and VBO
	glGenVertexArrays(1, &unitLineVAO);

	glGenBuffers(1, &unitLineVBO);

	glBindBuffer(GL_ARRAY_BUFFER, unitLineVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindVertexArray(unitLineVAO);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

}

void UnitLine::draw(Camera inCam, glm::mat4 inProj, glm::mat4 inView, glm::mat4 inModel) {
	return;
}