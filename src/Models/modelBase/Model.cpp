#include "Model.h"


Model::Model(Shader &inShader) {
	unitCube = UnitCube();
	data.shader = inShader;
	//data.shader = inShader;
	//data.shader = inShader;
	// data.diffuseMap = data.shader.loadTexture("res/images/brick2.jpg");
	// data.diffuseMap = data.shader.loadTexture("res/images/metal4.jpg");
	resetObject();
	
	modelBasePosition = glm::vec3(0.0f, 0.5f, 0.0f);

	// Create a new transform component and set it's position to the modelBasePosition
	transform = new Transform();
	transform->SetPosition(modelBasePosition);
	// for(int x = 0; x < sizeX; x++)
	// {
	// 	for(int y = 0; y < sizeY; y++)
	// 	{
	// 		for(int z = 0; z < sizeY; z++)
	// 		{
	// 			cubePositions[x][y][z] =  Transform(*transform);
	// 		}
	// 	}
	// }

	allocateModelData();

	renderMode = GL_TRIANGLES;

	textureOn = true;
	borderOn = false;
	continuousOn = false;

	Model::colorPalette = new glm::vec3[NUM_COLORS];

	setColorPalette();
}

/// <summary>
/// Sets all values within the cubes array to NONE.
/// </summary>
void Model::resetObject() {
	for (int r = 0; r < sizeX; r++) {
		for (int c = 0; c < sizeY; c++) {
			for (int p = 0; p < sizeZ; p++) {
				cubes[r][c][p] = NONE;
			}
		}
	}
	return;
}


/// <summary>
/// Draws the model specified by the cubes array at the Transform.
/// </summary>
/// <param name="inShader"> The shader used to render the model.</param>
void Model::draw(Shader* inShader) {
		inShader->use();


	// bind texture maps
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(unitCube.getVAO());
	
	
	glm::mat4 modelOrigin = transform->GetModel(parentTransform->GetModel());

	// Iterate through the cubes array and draws unitCubes at a position offset from the modelOrigin (transform relative to parent)
	for (int r = 0; r < sizeX; r++) {
		for (int c = 0; c < sizeY; c++) {
			for (int p = 0; p < sizeZ; p++) {

				// Skip drawing if cubePosition contains "NONE"
				if (cubes[r][c][p] == NONE) {
					continue;
				}

				// Sends a colour uniform to the shader according to the value at an arbitrary cubes index
				inShader->setVec3("colour", colorPalette[cubes[r][c][p]]);

				// Produces a transformation matrix for each cube in the model relative to the modelOrigin
				// Offsets the cubes such that the modelOrigin is the center of the entire model
				glm::vec3 positionalOffset = glm::vec3((float)c, (float)r, (float)p);
				glm::vec3 centerPointOffset = glm::vec3(ceil(float(-sizeX) * 0.5f), ceil(float(-sizeY) * 0.5f), ceil(float(-sizeZ) * 0.5f));
				glm::mat4 cubeMatrix = glm::translate(modelOrigin, positionalOffset + centerPointOffset);

				inShader->setMat4("model", cubeMatrix);
				
				// draw the cube
				glDrawArrays(renderMode, 0, 36);
	
				//cubePositions[r][c][p].AddPosition(positionalOffset + centerPointOffset);
			}
		}
	}
}

/// <summary>
/// Draws a single unitCube primitive.
/// </summary>
/// <param name="inShader"></param>
void Model::drawCube(Shader& inShader)
{
	glm::mat4 modelOrigin = transform->GetModel(parentTransform->GetModel());
	inShader.setMat4("model", modelOrigin);
	inShader.setVec3("colour", colorPalette[BLUE]);
	glDrawArrays(renderMode, 0, 36);
}

/// <summary>
/// Defines a colour palette to be used when drawing the model.
/// </summary>
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


/// <summary>
/// Assings a value of NONE to each index of the cubes array.
/// </summary>
void Model::allocateModelData()
{
	for(int x = 0; x < sizeX; x++)
	{
		for(int y = 0; y < sizeY; y++)
		{
			for(int z = 0; z < sizeZ; z++)
			{
				cubes[x][y][z] = NONE;
				cubePositions[x][y][x] = glm::vec3(0);
			}
		}
	}
}


/// <summary>
/// Sets the render mode of the model.
/// Options: GL_TRIANGLES, GL_LINES, GL_POINTS
/// </summary>
/// <param name="mode"></param>
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



Model::~Model() {
	for (int r = 0; r < sizeX; r++) {
		for (int c = 0; c < sizeY; c++) {
			delete[] cubes[r][c];
			delete[] cubes[r][c];
		}
		delete[] cubes[r];
		delete[] cubes[r];
	}
	delete[] cubes;
	delete[] cubes;
}

/// <summary>
/// Called once per frame.
/// </summary>
/// <param name="ms"> Time in milliseconds between frames.</param>
void Model::Update(float ms)
{
}

/// <summary>
/// Assigns the root transform of the model.
/// </summary>
/// <param name="trans">Pointer to the desired root transform.</param>
void Model::SetTransform(Transform* trans)
{
	transform = trans;
}


