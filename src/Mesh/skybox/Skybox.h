#pragma once
#include "../../glad/glad.h"
#include "../Shader/Shader.h"

class Skybox {
public:
	Skybox();
	void createSkybox();
	GLuint getVAO();
	GLuint getVBO();
	void draw();
private:
	GLuint skyboxVBO, skyboxVAO;
};