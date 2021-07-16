#include "ModelBase.h"

ModelBase::ModelBase() {
	unitCube = UnitCube();
	baseShader = Shader("res/shaders/baseShader.vert", "res/shaders/baseShader.frag");

	scaleFactor = 1.0f;

	xTranslation = 0.0f;
	yTranslation = 0.0f;

	orientation = 0.0f;

	renderMode = GL_TRIANGLES;
}

void ModelBase::initialize() {
	modelBasePosition = glm::vec3(-5.0f, 0.5f, 0.0f);
	return;
}

void ModelBase::draw(Camera inCam, glm::vec3* dirLight, glm::mat4 projection, glm::mat4 view, glm::mat4 model) {

	baseShader.use();

	baseShader.setVec3("viewPos", inCam.Position);

	baseShader.setVec3("dirLight.direction", dirLight[LIGHT_DIRECTION]);
	baseShader.setVec3("dirLight.ambient", dirLight[LIGHT_AMBIENT]);
	baseShader.setVec3("dirLight.diffuse", dirLight[LIGHT_DIFFUSE]);
	baseShader.setVec3("dirLight.specular", dirLight[LIGHT_SPECULAR]);

	baseShader.setMat4("projection", projection);
	baseShader.setMat4("view", view);

	// world transformation
	// model = glm::scale(model, glm::vec3(1.0f * scaleFactor, 1.0f * scaleFactor, 1.0f));
	model = glm::translate(model, modelBasePosition);
	model = glm::translate(model, glm::vec3(xTranslation, yTranslation, 0.0f));
	model = glm::scale(model, glm::vec3(1.0f) * scaleFactor);

	baseShader.setMat4("model", model);

	// render the cubes
	glBindVertexArray(unitCube.getVAO());

	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void ModelBase::scale(int scaleDirection) {
	if (scaleDirection == SCALE_UP && scaleFactor < SCALE_MAX) {
		scaleFactor += 0.1f;
	}
	else if (scaleDirection == SCALE_DOWN && scaleFactor > SCALE_MIN) {
		scaleFactor -= 0.1f;
	}
}

void ModelBase::translate(int translationDirection) {
	
	if (inBound(translationDirection)) {

		switch (translationDirection) {
		case TRANS_RIGHT:
			xTranslation += 0.1f;
			break;
		case TRANS_LEFT:
			xTranslation -= 0.1f;
			break;
		case TRANS_UP:
			yTranslation += 0.1f;
			break;
		case TRANS_DOWN:
			yTranslation -= 0.1f;
		}
	}

}

void ModelBase::rotate(int rotation) {
	if (rotation == ROTATE_LEFT) {
		orientation += glm::radians(5.0f);
	}
	else {
		orientation -= glm::radians(5.0f);
	}
}


void ModelBase::setRenderMode(int mode) {
	
	switch (mode) {
		case GL_TRIANGLES:
			renderMode = GL_TRIANGLES;
			break;
		case GL_LINES:
			renderMode = GL_LINES;
			break;
		case GL_POINTS:
			renderMode = GL_POINTS;
	}
};

bool ModelBase::inBound(int direction) {

	switch (direction) {
	case TRANS_RIGHT:
		return modelBasePosition.x + xTranslation < BOUND_X_MAX;
	case TRANS_LEFT:
		return modelBasePosition.x + xTranslation > BOUND_X_MIN;
	case TRANS_UP:
		return true; // no y max let user rise to infinity
	case TRANS_DOWN:
		return modelBasePosition.y + yTranslation > BOUND_Y_MIN;
	}

	return true;
}

int* ModelBase::generateRandomModel(int rows, int columns, int planes)
{
	int result[] = { 1,2,3 };
	return result; 
}

void ModelBase::generateOriginalObject() {
	return;
}