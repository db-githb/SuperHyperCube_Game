#include "ModelBase.h"

ModelBase::ModelBase() {
	unitCube = UnitCube();
	wall.shader = Shader("res/shaders/baseShader.vert", "res/shaders/baseShader.frag");
	object.shader = Shader("res/shaders/baseShader.vert", "res/shaders/baseShader.frag");

	rows = 1;
	columns = 1;
	planes = 1;

	scaleFactor = 0.5f;

	xTranslation = 0.0f;
	yTranslation = 0.0f;
	zTranslation = 0.0f;

	orientation = 0.0f;

	renderMode = GL_TRIANGLES;
}

void ModelBase::allocateObjectData() {

	object.modelData = new int** [rows];

	for (int r = 0; r < rows; r++) {
		object.modelData[r] = new int* [columns];
		for (int c = 0; c < columns; c++) {
			object.modelData[r][c] = new int[planes];
			for (int p = 0; p < planes; p++) {
				object.modelData[r][c][p] = NONE;
			}
		}
	}

	return;
}

void ModelBase::allocateWallData() {

	wall.modelData = new int** [rows];

	for (int r = 0; r < rows; r++) {
		wall.modelData[r] = new int* [columns];
		for (int c = 0; c < columns; c++) {
			wall.modelData[r][c] = new int[1];
			wall.modelData[r][c][0] = GRAY;
		}
	}

	return;
}

void ModelBase::initialize() {
	
	allocateObjectData();
	allocateWallData();
	allocateShaderData();
}

void ModelBase::allocateShaderData() {

	// load textures
	wall.diffuseMap = wall.shader.loadTexture("res/images/brick.png");

	object.diffuseMap = object.shader.loadTexture("res/images/metal.jpg");
	object.specularMap = object.shader.loadTexture("res/images/metal.jpg");

	// shader configuration
	wall.shader.use();
	wall.shader.setInt("material.diffuse", 0);

	object.shader.use();
	object.shader.setInt("material.diffuse", 0);
	object.shader.setInt("material.specular", 1);
}

void ModelBase::draw(Camera inCam, glm::mat4 projection, glm::mat4 view, glm::mat4 model) {


	// compute world position of parent (model<name>)
	model = glm::translate(model, (modelBasePosition + glm::vec3(xTranslation * scaleFactor, yTranslation * scaleFactor, 0.0f)));
	model = glm::rotate(model, orientation, glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0f) * scaleFactor);

	// TODO: move shader set up to scene afterwards
	shaderSetUp(inCam, projection, view, wall);
	drawWall(model);

	shaderSetUp(inCam, projection, view, object);
	drawObject(model);
}

void ModelBase::drawWall(glm::mat4 model) {

	// bind texture maps
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, wall.diffuseMap);

	
	glBindVertexArray(unitCube.getVAO());

	// compute world position of child cubes
	for (int r = 0; r < rows; r++) {
		for (int c = 0; c < columns; c++) {

			if (wall.modelData[r][c][0] == NONE) {
				continue;
			}

				// color value applied via color palette
				wall.shader.setVec3("dirLight.ambient", ModelBase::colorPalette[wall.modelData[r][c][0]]);

				// move unit cube relative to parent base position and pass the model matrix to the vertex shader
				wall.shader.setMat4("model", glm::translate(model, glm::vec3((float)c, (float)r, 0.0f) + glm::vec3((-columns * 0.5), 0.0f, (-planes / 2))));

				// render the cube
				glDrawArrays(renderMode, 0, 36);
		}
	}
}

void ModelBase::drawObject(glm::mat4 model) {

	// bind texture maps
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, object.diffuseMap);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, object.specularMap);

	glBindVertexArray(unitCube.getVAO());

	// compute world position of child cubes
	for (int r = 0; r < rows; r++) {
		for (int c = 0; c < columns; c++) {
			for (int p = 0; p < planes; p++) {

				if (object.modelData[r][c][p] == NONE) {
					continue;
				}

				// color value applied via color palette
				object.shader.setVec3("dirLight.ambient", ModelBase::colorPalette[BLACK]);

				// move unit cube relative to parent base position and pass the model matrix to the vertex shader
				object.shader.setMat4("model", glm::translate(model, glm::vec3((float)c, (float)r, (float)p) + glm::vec3((-columns * 0.5), 0.0f, (-planes / 2))));

				// render the cube
				glDrawArrays(renderMode, 0, 36);

			}
		}
	}
}

// component struct will have the shader and the material will be an attribute of the component struct
void ModelBase::shaderSetUp(Camera inCam, glm::mat4 projection, glm::mat4 view, Component component) {
	// specify the shader being used
	component.shader.use();
	
	component.shader.setVec3("viewPos", inCam.Position);
	
	component.shader.setVec3("dirLight.direction", LIGHT_DIRECTION);
	component.shader.setVec3("dirLight.ambient", LIGHT_AMBIENT);
	component.shader.setVec3("dirLight.diffuse", LIGHT_DIFFUSE);
	component.shader.setVec3("dirLight.specular", LIGHT_SPECULAR);
	
	component.shader.setVec3("pointLight.position", POINT_LIGHT_POSITION);
	component.shader.setVec3("pointLight.ambient", 0.05f, 0.05f, 0.05f);
	component.shader.setVec3("pointLight.diffuse", 0.8f, 0.8f, 0.8f);
	component.shader.setVec3("pointLight.specular", 1.0f, 1.0f, 1.0f);
	component.shader.setFloat("pointLight.constant", 1.0f);
	component.shader.setFloat("pointLight.linear", 0.09f);
	component.shader.setFloat("pointLight.quadratic", 0.032);

	component.shader.setFloat("material.shininess", 32.0f);

	component.shader.setMat4("projection", projection);
	component.shader.setMat4("view", view);
}

void ModelBase::setColorPalette() {

	ModelBase::colorPalette[GRAY] = glm::vec3(0.5f, 0.5f, 0.5f);

	ModelBase::colorPalette[RED] = glm::vec3(.9f, 0.1f, 0.15f);
	ModelBase::colorPalette[BLUE] = glm::vec3(0.15f, 0.1f, 0.9f);
	ModelBase::colorPalette[VIOLET] = glm::vec3(0.25f, 0.1f, 0.85f);
	ModelBase::colorPalette[MINT] = glm::vec3(0.1f, 0.7f, 0.5f);
	ModelBase::colorPalette[PINK] = glm::vec3(1.0f, 0.0f, 1.0f);
	ModelBase::colorPalette[CYAN] = glm::vec3(0.0f, 3.0f, 1.0f);
	ModelBase::colorPalette[YELLOW] = glm::vec3(1.0f, 1.0f, 0.0f);
	ModelBase::colorPalette[ORANGE] = glm::vec3(1.0f, 0.5f, 0.0f);
	ModelBase::colorPalette[BLACK] = glm::vec3(0.0f, 0.0f, 0.0f);
	return;
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

void ModelBase::generateRandomModel()
{
	return;
}

void ModelBase::generateOriginalObject() {
	return;
}

bool ModelBase::boundaryCollision() {
	return false;
}