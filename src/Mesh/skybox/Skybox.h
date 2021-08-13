#pragma once
#include "../../glad/glad.h"

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