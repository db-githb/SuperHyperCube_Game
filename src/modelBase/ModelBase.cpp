#include "ModelBase.h"

ModelBase::ModelBase(Shader &inShader) {
	unitCube = UnitCube();
	wall.shader = inShader;
	object.shader = inShader;
	wall.diffuseMap = wall.shader.loadTexture("res/images/brick2.jpg");
	object.diffuseMap = object.shader.loadTexture("res/images/metal4.jpg");

	speed = 0.03f;

	rows = 1;
	columns = 1;
	planes = 1;

	resetPOS();

	modelBasePosition = glm::vec3(0.0f, 0.5f, 0.0f);
	allocateObjectData();
	allocateWallData();
	renderMode = GL_TRIANGLES;

	textureOn = true;
	borderOn = false;
	movementOn = false;

	ModelBase::colorPalette = new glm::vec3[NUM_COLORS];

	setColorPalette();

}

void ModelBase::resetPOS(){

	scaleFactor = 1.0f;

	xTranslation = 0.0f;
	yTranslation = 0.0f;
	zTranslation = 25.0f;
	prevZ = zTranslation;

	xRotation = 0.0f;
	yRotation = 0.0f;
	zRotation = 0.0f;
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

void ModelBase::draw(Shader* inShader) {
	glm::mat4 model = glm::mat4(1.0f);
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
}

void ModelBase::drawWall(glm::mat4 model) {

	wall.shader.setFloat("specBias", 0.0);
	wall.shader.setBool("textureOn", textureOn);
	wall.shader.setBool("borderOn", false);
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

			wall.shader.setVec3("colour", colorPalette[GRAY]);

			// move unit cube relative to parent base position and pass the model matrix to the vertex shader
			//wall.shader.setMat4("model", glm::translate(model, glm::vec3((float)c, (float)r, 0.0f) + glm::vec3((-columns * 0.5), 0.0f, (-planes / 2))));
			wall.shader.setMat4("model", glm::translate(model, glm::vec3((float)c, (float)r, 0.0f) + glm::vec3((-columns * 0.5), 0.0f, 0.0f)));

			// render the cube
			glDrawArrays(renderMode, 0, 36);
		}
	}
}

void ModelBase::drawObject(glm::mat4 model) {

	object.shader.setFloat("specBias", 8.0);
	object.shader.setBool("textureOn", textureOn);
	object.shader.setBool("borderOn", borderOn);

	// bind texture maps
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, object.diffuseMap);

	glBindVertexArray(unitCube.getVAO());

	if (movementOn) {
		prevZ = zTranslation;

		//TODO: switch to delta time for more smooth translation
		zTranslation -= speed;
	}

	model = glm::translate(model, (glm::vec3(xTranslation, yTranslation, zTranslation)));
	
	model = glm::translate(model, glm::vec3(0.0f, rows/2, planes / 2));
	model = glm::rotate(model, xRotation, glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::translate(model, glm::vec3(-0.5f, -rows/2, 0.0));
	model = glm::rotate(model, yRotation, glm::vec3(0.0f, 1.0f, 0.0));
	model = glm::translate(model, glm::vec3(0.0f, rows/2, -planes / 2));
	model = glm::rotate(model, zRotation, glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::translate(model, glm::vec3(0.5f, -rows/2, 0.0f));

	// compute world position of child cubes
	for (int r = 0; r < rows; r++) {
		for (int c = 0; c < columns; c++) {
			for (int p = 0; p < planes; p++) {

				if (object.modelData[r][c][p] == NONE) {
					continue;
				}

				object.shader.setVec3("colour", colorPalette[object.modelData[r][c][p]]);
					
				// move unit cube relative to parent base position and pass the model matrix to the vertex shader
				//object.shader.setMat4("model", glm::translate(model, glm::vec3((float)c, (float)r, (float)p) + glm::vec3((-columns * 0.5), 0.0f, -planes * 0.5)));
				object.shader.setMat4("model", glm::translate(model, glm::vec3((float)c, (float)r, (float)p) + glm::vec3((-columns * 0.5), 0.0f, 0.0f)));

				// render the cube
				glDrawArrays(renderMode, 0, 36);

			}
		}
	}
}

void ModelBase::setColorPalette() {

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
	ModelBase::colorPalette[GREEN] = glm::vec3(0.349f, 0.553f, 0.243f);
	ModelBase::colorPalette[BROWN] = glm::vec3(0.651f, 0.357f, 0.192f);
	ModelBase::colorPalette[WHITE] = glm::vec3(1.0f, 1.0f, 1.0f);
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

void ModelBase::rotate(int rotation) {

	switch (rotation) {
	case ROTATE_X_CLOCKWISE:
		xRotation = glm::radians((float)(((int)glm::degrees(xRotation) - 90) % 360));
		break;
	case ROTATE_X_COUNTER:
		xRotation = glm::radians((float)(((int)glm::degrees(xRotation) + 90) % 360));
		break;
	case ROTATE_Y_CLOCKWISE:
		yRotation = glm::radians((float)(((int)glm::degrees(yRotation) - 90) % 360));
		break;
	case ROTATE_Y_COUNTER:
		yRotation = glm::radians((float)(((int)glm::degrees(yRotation) + 90) % 360));
		break;
	case ROTATE_Z_CLOCKWISE:
		zRotation = glm::radians((float)(((int)glm::degrees(zRotation) - 90) % 360));
		break;
	case ROTATE_Z_COUNTER:
		zRotation = glm::radians((float)(((int)glm::degrees(zRotation) + 90) % 360));
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

void ModelBase::toggleTexture() {
	textureOn = !textureOn;
}

void ModelBase::toggleBorder() {
	borderOn = !borderOn;
}

void ModelBase::turnMovementOn() {
	movementOn = true;
	movementStartTime = glfwGetTime();
}

void ModelBase::generateRandomModel()
{
	return;
}

void ModelBase::generateOriginalObject() {
	return;
}

bool ModelBase::objectAtWall() {

	//Keep for when we switch to delta time for more smooth translation
	return glm::sign<float>(prevZ) != glm::sign<float>(zTranslation);
}

bool ModelBase::passOrientation() {
	
	return xRotation == 0.0f && yRotation == 0.0f && zRotation == 0.0f;
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