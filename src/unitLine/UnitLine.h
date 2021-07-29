#pragma once

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