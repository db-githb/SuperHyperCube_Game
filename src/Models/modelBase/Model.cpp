#include "Model.h"

Model::Model(Data modelData)
{
	data = modelData;
}

Model::Model(Shader &inShader) {
	unitCube = UnitCube();
	data.shader = inShader;
	//data.shader = inShader;
	//data.shader = inShader;
	// data.diffuseMap = data.shader.loadTexture("res/images/brick2.jpg");
	// data.diffuseMap = data.shader.loadTexture("res/images/metal4.jpg");
	resetPOS();

	modelBasePosition = glm::vec3(0.0f, 0.5f, 0.0f);
	transform = new Transform();
	transform->SetPosition(modelBasePosition);
	allocateModelData();
	//allocateObjectData();
	//allocateWallData();
	renderMode = GL_TRIANGLES;

	textureOn = true;
	borderOn = false;
	continuousOn = false;

	Model::colorPalette = new glm::vec3[NUM_COLORS];

	setColorPalette();
}


void Model::resetPOS(){

	scaleFactor = 1.0f;

	xTranslation = 0.0f;
	yTranslation = 0.0f;
	zTranslation = 0.0f;

	xRotation = 0.0f;
	yRotation = 0.0f;
	zRotation = 0.0f;
}

// void Model::allocateWallData() {
//
// 	data.cubePositions = new int** [rows];
//
// 	for (int r = 0; r < rows; r++) {
// 		data.cubePositions[r] = new int* [columns];
// 		for (int c = 0; c < columns; c++) {
// 			data.cubePositions[r][c] = new int[1];
// 			data.cubePositions[r][c][0] = GRAY;
// 		}
// 	}
//
// 	return;
// }
//
// void Model::allocateObjectData() {
//
// 	data.cubePositions = new int** [rows];
//
// 	for (int r = 0; r < rows; r++) {
// 		data.cubePositions[r] = new int* [columns];
// 		for (int c = 0; c < columns; c++) {
// 			data.cubePositions[r][c] = new int[planes];
// 			for (int p = 0; p < planes; p++) {
// 				data.cubePositions[r][c][p] = NONE;
// 			}
// 		}
// 	}
//
// 	return;
// }

void Model::resetObject() {
	for (int r = 0; r < sizeX; r++) {
		for (int c = 0; c < sizeY; c++) {
			for (int p = 0; p < sizeZ; p++) {
				cubePositions[r][c][p] = NONE;
			}
		}
	}

	return;
}



void Model::draw(Shader* inShader) {
		inShader->use();
		//drawWall(*inShader);
		//drawObject(*inShader);
		//drawCube(*inShader);

	// bind texture maps
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(unitCube.getVAO());
	
	//glm::mat4 modelOrigin = gameObject->transform.GetModel();
	
	// compute world position of child cubes
	for (int r = 0; r < sizeX; r++) {
		for (int c = 0; c < sizeY; c++) {
			for (int p = 0; p < sizeZ; p++) {

				if (cubePositions[r][c][p] == NONE) {
					continue;
				}
				
				inShader->setVec3("colour", colorPalette[GRAY]);
				//
				// move unit cube relative to parent base position and pass the model matrix to the vertex shader
				 inShader->setMat4("model", glm::translate(transform->GetModel(parentTransform->GetModel()), glm::vec3((float)c, (float)r, (float)p) + glm::vec3((0.3f +(-sizeY * 0.5)), 0.0f, (-0.3f +(-sizeZ * 0.5)))));
				//inShader.setMat4("model", glm::translate(modelOrigin, glm::vec3((float)c, (float)r, (float)p) + glm::vec3((0.3f + (-columns * 0.5)), 0.0f, (-0.3f + (-planes * 0.5)))));

				
				// render the cube
				glDrawArrays(renderMode, 0, 36);

			}
		}
	}

}

// void Model::drawWall(Shader& inShader) {
//
// 	// bind texture maps
// 	glActiveTexture(GL_TEXTURE0);
//
// 	//glActiveTexture(GL_TEXTURE2);
// 	//glBindTexture(GL_TEXTURE_2D, data.specularMap);
// 	
// 	glBindVertexArray(unitCube.getVAO());
//
// 	//glm::mat4 modelOrigin = gameObject->transform.GetModel();
//
// 	// compute world position of child cubes
// 	for (int r = 0; r < rows; r++) {
// 		for (int c = 0; c < columns; c++) {
//
// 			if (data.cubePositions[r][c][0] == NONE) {
// 				continue;
// 			}
//
// 			data.shader.setVec3("colour", colorPalette[GRAY]);
//
// 			// move unit cube relative to parent base position and pass the model matrix to the vertex shader
// 			inShader.setMat4("model", glm::translate(transform->GetModel(parentTransform->GetModel()), glm::vec3((float)c, (float)r, 0.0f) + glm::vec3((-columns * 0.5), 0.0f, (-planes / 2))));
// 			//inShader.setMat4("model", glm::translate(modelOrigin, glm::vec3((float)c, (float)r, 0.0f) + glm::vec3((-columns * 0.5), 0.0f, (-planes / 2))));
//
// 			
// 			// render the cube
// 			glDrawArrays(renderMode, 0, 36);
// 		}
// 	}
// }
//
// void Model::drawObject(Shader& inShader) {
//
//
// 	// bind texture maps
// 	glActiveTexture(GL_TEXTURE0);
//
// 	// glActiveTexture(GL_TEXTURE1);
// 	// glBindTexture(GL_TEXTURE_2D, data.specularMap);
//
// 	glBindVertexArray(unitCube.getVAO());
//
// 	if (continuousOn) {
//
// 		zTranslation = (float)(sin(glfwGetTime()-continuousStartTime) * 7);
// 	}
//
// 	/*model = glm::translate(model, (glm::vec3(xTranslation, yTranslation, zTranslation)));
// 	
// 	model = glm::rotate(model, xRotation, glm::vec3(1.0f, 0.0f, 0.0f));
// 	model = glm::rotate(model, yRotation, glm::vec3(0.0f, 1.0f, 0.0f));
// 	model = glm::rotate(model, zRotation, glm::vec3(0.0f, 0.0f, 1.0f));*/
//
// 	//glm::mat4 modelOrigin = gameObject->transform.GetModel();
// 	
// 	// compute world position of child cubes
// 	for (int r = 0; r < rows; r++) {
// 		for (int c = 0; c < columns; c++) {
// 			for (int p = 0; p < planes; p++) {
//
// 				if (data.cubePositions[r][c][p] == NONE) {
// 					continue;
// 				}
// 				
// 					
// 				// move unit cube relative to parent base position and pass the model matrix to the vertex shader
// 				 inShader.setMat4("model", glm::translate(transform->GetModel(parentTransform->GetModel()), glm::vec3((float)c, (float)r, (float)p) + glm::vec3((0.3f +(-columns * 0.5)), 0.0f, (-0.3f +(-planes * 0.5)))));
// 				//inShader.setMat4("model", glm::translate(modelOrigin, glm::vec3((float)c, (float)r, (float)p) + glm::vec3((0.3f + (-columns * 0.5)), 0.0f, (-0.3f + (-planes * 0.5)))));
//
// 				
// 				// render the cube
// 				glDrawArrays(renderMode, 0, 36);
//
// 			}
// 		}
// 	}
// }

void Model::drawCube(Shader& inShader)
{
	//glm::mat4 modelOrigin = gameObject->transform.GetModel();
	inShader.setMat4("model", transform->GetModel(parentTransform->GetModel()));
	inShader.setVec3("colour", colorPalette[BLUE]);
	glDrawArrays(renderMode, 0, 36);
}


void Model::setColorPalette() {

	Model::colorPalette[GRAY] = glm::vec3(0.5f, 0.5f, 0.5f);
	Model::colorPalette[RED] = glm::vec3(0.9f, 0.1f, 0.15f);
	Model::colorPalette[BLUE] = glm::vec3(0.15f, 0.1f, 0.9f);
	Model::colorPalette[VIOLET] = glm::vec3(0.25f, 0.1f, 0.85f);
	Model::colorPalette[MINT] = glm::vec3(0.1f, 0.7f, 0.5f);
	Model::colorPalette[PINK] = glm::vec3(1.0f, 0.0f, 1.0f);
	Model::colorPalette[CYAN] = glm::vec3(0.0f, 3.0f, 1.0f);
	Model::colorPalette[YELLOW] = glm::vec3(1.0f, 1.0f, 0.0f);
	Model::colorPalette[ORANGE] = glm::vec3(1.0f, 0.5f, 0.0f);
	Model::colorPalette[BLACK] = glm::vec3(0.0f, 0.0f, 0.0f);
	Model::colorPalette[GREEN] = glm::vec3(0.349f, 0.553f, 0.243f);
	Model::colorPalette[BROWN] = glm::vec3(0.651f, 0.357f, 0.192f);
	Model::colorPalette[WHITE] = glm::vec3(1.0f, 1.0f, 1.0f);
	return;
}

void Model::allocateModelData()
{
	for(int x = 0; x < sizeX; x++)
	{
		for(int y = 0; y < sizeY; y++)
		{
			for(int z = 0; z < sizeZ; z++)
			{
				cubePositions[x][y][z] = NONE;
			}
		}
	}
}

//
// void Model::scale(int scaleDirection) {
// 	if (scaleDirection == SCALE_UP && scaleFactor < SCALE_MAX) {
// 		scaleFactor += 0.1f;
// 	}
// 	else if (scaleDirection == SCALE_DOWN && scaleFactor > SCALE_MIN) {
// 		scaleFactor -= 0.1f;
// 	}
// }
//
// void Model::translate(int translationDirection) {
//
// 	switch (translationDirection) {
// 		case TRANS_RIGHT:
// 			xTranslation += 0.1f;
// 			break;
// 		case TRANS_LEFT:
// 			xTranslation -= 0.1f;
// 			break;
// 		case TRANS_UP:
// 			yTranslation += 0.1f;
// 			break;
// 		case TRANS_DOWN:
// 			yTranslation -= 0.1f;
// 			break;
// 		case TRANS_FORWARD:
// 			zTranslation -= 0.1f;
// 			break;
// 		case TRANS_BACKWARD:
// 			zTranslation += 0.1f;
// 			break;
// 	}
// }
//
// void Model::rotate(int rotation) {
//
// 	switch (rotation) {
// 	case ROTATE_X_CLOCKWISE:
// 		xRotation -= glm::radians(5.0f);
// 		break;
// 	case ROTATE_X_COUNTER:
// 		xRotation += glm::radians(5.0f);
// 		break;
// 	case ROTATE_Y_CLOCKWISE:
// 		yRotation -= glm::radians(5.0f);
// 		break;
// 	case ROTATE_Y_COUNTER:
// 		yRotation += glm::radians(5.0f);
// 		break;
// 	case ROTATE_Z_CLOCKWISE:
// 		zRotation -= glm::radians(5.0f);
// 		break;
// 	case ROTATE_Z_COUNTER:
// 		zRotation += glm::radians(5.0f);
// 		break;
// 	}
// }


void Model::setRenderMode(int mode) {
	
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

void Model::toggleTexture() {

	textureOn = !textureOn;

}

void Model::toggleBorder() {
	borderOn = !borderOn;
}

void Model::toggleContinuous() {

	continuousOn = !continuousOn;

	continuousStartTime = glfwGetTime();
}

void Model::generateRandomModel()
{
	return;
}

void Model::generateOriginalObject() {
	return;
}

Model::~Model() {
	for (int r = 0; r < sizeX; r++) {
		for (int c = 0; c < sizeY; c++) {
			delete[] cubePositions[r][c];
			delete[] cubePositions[r][c];
		}
		delete[] cubePositions[r];
		delete[] cubePositions[r];
	}
	delete[] cubePositions;
	delete[] cubePositions;
}

void Model::Update(float ms)
{
}

void Model::SetTransform(Transform* trans)
{
	transform = trans;
}


