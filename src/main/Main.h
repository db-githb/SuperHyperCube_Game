#include <iostream>
#include <stdio.h>
#include <string.h>
#include "../../glad/glad.h"
#include <glfw/glfw3.h>
#include "../../glm/glm.hpp"
#include "../../glm/gtc/matrix_transform.hpp"
#include "../../glm/gtc/type_ptr.hpp"
#include "../shader/Shader.h"
#include "../camera/Camera.h"

//settings
const GLint WIDTH = 800, HEIGHT = 600;

GLuint letterCubeVBO, letterCubeVAO, lineVAO, lineVBO, gridLinesVAO, gridLinesVBO;

// camera
Camera camera(glm::vec3(0.0f, 1.0f, 5.0f));

float lastX = WIDTH / 2.0f;
float lastY = HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;