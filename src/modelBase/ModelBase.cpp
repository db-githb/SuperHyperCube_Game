#include "ModelBase.h"

ModelBase::ModelBase() {
}

ModelBase::ModelBase(Shader &inShader) {
	unitCube = UnitCube();
	wall.shader = inShader;
	object.shader = inShader;

	rows = 1;
	columns = 1;
	planes = 1;

	scaleFactor = 1.0f;

	xTranslation = 0.0f;
	yTranslation = 0.0f;
	zTranslation = 0.0f;

	xRotation = 0.0f;
	yRotation = 0.0f;
	zRotation = 0.0f;

	renderMode = GL_TRIANGLES;
}

void ModelBase::allocateObjectData() {

	object.modelData = new int** [rows];

	for (int r = 0; r < rows; r++) {
		object.modelData[r] = new int* [columns];
		for (int c = 0; c < columns; c++) {
			object.modelData[r][c] = new int[planes];
			for (int p = 0; p < planes; p++) {
				object.modelData[r][c][p] = GRAY;
			}
		}
	}

	return;
}

void ModelBase::resetObject() {
	for (int r = 0; r < rows; r++) {
		for (int c = 0; c < columns; c++) {
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
	
	wall.diffuseMap = wall.shader.loadTexture("res/images/brick.png");
	object.diffuseMap = object.shader.loadTexture("res/images/metal.png");

	modelBasePosition = glm::vec3(0.0f, 0.5f, 0.0f);

	allocateObjectData();
	allocateWallData();
	allocateShaderData();
}

void ModelBase::allocateShaderData() {

	/*
	// load textures
	wall.diffuseMap = wall.shader.loadTexture("res/images/brick.png");
	wall.specularMap = wall.shader.loadTexture("res/images/brick_spec_map.png");

	object.diffuseMap = object.shader.loadTexture("res/images/metal.png");
	object.specularMap = object.shader.loadTexture("res/images/metal_spec_map.jpg");

	// shader configuration
	wall.shader.use();
	wall.shader.setInt("material.diffuse", 1);
	wall.shader.setInt("material.specular", 2);

	
	object.shader.use();
	object.shader.setInt("material.diffuse", 1);
	object.shader.setInt("material.specular", 2);
	*/
}

void ModelBase::draw(glm::mat4 model, Shader* inShader) {

	model = glm::translate(model, modelBasePosition);
	model = glm::scale(model, glm::vec3(1.0f) * scaleFactor);

	if (inShader == NULL) {
		wall.shader.use();
		drawWall(model);

		object.shader.use();
		drawObject(model);
	}
	else {
		inShader->use();
		drawWall(model);
		drawObject(model);
	}
	

	// TODO: move shader set up to scene afterwards
	//shaderSetUp(inCam, projection, view, wall);
	


	/*
	model = glm::mat4(1.0f);
	model = glm::translate(model, (modelBasePosition + glm::vec3(xTranslation * scaleFactor, yTranslation * scaleFactor, zTranslation * scaleFactor)));

	model = glm::translate(model, glm::vec3(0.0f, 2.0f, 0.0f));
	model = glm::rotate(model, xRotation, glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, yRotation, glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, zRotation, glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::translate(model, glm::vec3(0.0f, -2.0f, 0.0f));

	model = glm::scale(model, glm::vec3(1.0f) * scaleFactor);

	shaderSetUp(inCam, projection, view, object);
	drawObject(model, shadowMapShader);
	*/
}

void ModelBase::drawWall(glm::mat4 model) {

	// bind texture maps
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, wall.diffuseMap);

	//glActiveTexture(GL_TEXTURE2);
	//glBindTexture(GL_TEXTURE_2D, wall.specularMap);


	// compute world position of child cubes
	for (int r = 0; r < rows; r++) {
		for (int c = 0; c < columns; c++) {

			if (wall.modelData[r][c][0] == NONE) {
				continue;
			}

			wall.shader.setMat4("model", glm::translate(model, glm::vec3((float)c, (float)r, 0.0f) + glm::vec3((-columns * 0.5), 0.0f, (-planes / 2))));
			
			// render the cube
			glBindVertexArray(unitCube.getVAO());
			glDrawArrays(renderMode, 0, 36);
		}
	}
	glBindVertexArray(0);
}

void ModelBase::drawObject(glm::mat4 model) {

	// bind texture maps
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, object.diffuseMap);

	//glActiveTexture(GL_TEXTURE2);
	//glBindTexture(GL_TEXTURE_2D, object.specularMap);

	

	// compute world position of child cubes
	for (int r = 0; r < rows; r++) {
		for (int c = 0; c < columns; c++) {
			for (int p = 0; p < planes; p++) {

				if (object.modelData[r][c][p] == NONE) {
					continue;
				}

				object.shader.setMat4("model", glm::translate(model, glm::vec3((float)c+3.0f, (float)r, (float)p) + glm::vec3((0.3f + (-columns * 0.5)), 0.0f, (-0.3f + (-planes * 0.5)))));
				
				// render the cube
				glBindVertexArray(unitCube.getVAO());
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

	component.shader.setVec3("pointLight.position", UnitCube::pointLight[POINT_LIGHT_POSITION]);
	component.shader.setVec3("pointLight.ambient", UnitCube::pointLight[POINT_LIGHT_AMBIENT]);
	component.shader.setVec3("pointLight.diffuse", UnitCube::pointLight[POINT_LIGHT_DIFFUSE]);
	component.shader.setVec3("pointLight.specular", UnitCube::pointLight[POINT_LIGHT_SPECULAR]);
	component.shader.setFloat("pointLight.constant", UnitCube::pointLight[POINT_LIGHT_SPECULAR].x);
	component.shader.setFloat("pointLight.linear", UnitCube::pointLight[POINT_LIGHT_SPECULAR].y);
	component.shader.setFloat("pointLight.quadratic", UnitCube::pointLight[POINT_LIGHT_SPECULAR].z);

	//component.shader.setFloat("material.shininess", 32.0f);

	//component.shader.setMat4("projection", projection);
	//component.shader.setMat4("view", view);
}

void ModelBase::setColorPalette() {

	ModelBase::colorPalette = new glm::vec3[NUM_COLORS];

	ModelBase::colorPalette[GRAY] = glm::vec3(0.5f, 0.5f, 0.5f);
	ModelBase::colorPalette[RED] = glm::vec3(0.9f, 0.1f, 0.15f);
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
			break;
		case TRANS_FORWARD:
			zTranslation -= 0.1f;
			break;
		case TRANS_BACKWARD:
			zTranslation += 0.1f;
			break;
		}
	}
}

void ModelBase::rotate(int rotation) {

	switch (rotation) {
	case ROTATE_X_CLOCKWISE:
		xRotation -= glm::radians(5.0f);
		break;
	case ROTATE_X_COUNTER:
		xRotation += glm::radians(5.0f);
		break;
	case ROTATE_Y_CLOCKWISE:
		yRotation -= glm::radians(5.0f);
		break;
	case ROTATE_Y_COUNTER:
		yRotation += glm::radians(5.0f);
		break;
	case ROTATE_Z_CLOCKWISE:
		zRotation -= glm::radians(5.0f);
		break;
	case ROTATE_Z_COUNTER:
		zRotation += glm::radians(5.0f);
		break;
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

ModelBase::~ModelBase() {
	for (int r = 0; r < rows; r++) {
		for (int c = 0; c < columns; c++) {
			delete[] object.modelData[r][c];
			delete[] wall.modelData[r][c];
		}
		delete[] object.modelData[r];
		delete[] wall.modelData[r];
	}
	delete[] object.modelData;
	delete[] wall.modelData;
}