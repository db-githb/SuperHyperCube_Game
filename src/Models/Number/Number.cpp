#include "Number.h"

Number::Number(Shader& inShader) : ModelBase(inShader)
{



	

	sizeY = 7;
	sizeX = 23;
	modelBasePosition = glm::vec3(-(float(sizeX)/4), 0.5f, 0.0f);
	generateOriginalObject();
}


void Number::generateOriginalObject()
{
	for (int y = 0; y < sizeY; y++)
	{
		for (int x = 0; x < sizeX; x++)
			modelData[x][y] = NONE;
	}

	for (int y = 0; y < sizeY; y++)
	{
		for (int x = 0; x < sizeX; x++)
		{
			if (y == 6)
			{
				if (x == 0 || x == 4 || (x >= 6 && x <= 10) || (x >= 12 && x <= 16) || x >= 18)
					modelData[x][y] = BLUE;
			}
			if (y == 5 || y == 4)
			{
				if (x == 0 || x == 4 || x == 6 || x == 10 || x == 12 || x == 16 || x == 18 || x == 22)
					modelData[x][y] = BLUE;
			}
			if (y == 3)
			{
				if (x <= 4 || x == 6 || x == 8 || x == 10 || x == 12 || x == 16 || (x >= 19 && x <= 21))
					modelData[x][y] = BLUE;
			}
			if (y == 2 || y == 1)
			{
				if (x == 4 || x == 6 || x == 10 || x == 16 || x == 18 || x == 22)
					modelData[x][y] = BLUE;
			}
			if (y == 0)
			{
				if ( x == 4 || (x >= 6 && x <= 10) || x == 16 || x >= 18)
					modelData[x][y] = BLUE;
			}
		}
	}
}

void Number::draw(Shader* inShader)
{
	(*inShader).use();
	(*inShader).setBool("isTextured", false);
	(*inShader).setVec3("colour", glm::vec3(1.0f, 0.5f, 0.3f));
	glBindVertexArray(unitCube.getVAO());

	// compute world position of child cubes
	for (int x = 0; x < sizeX; x++) {
		for (int y = 0; y < sizeY; y++) {
			if (modelData[x][y] == NONE) {
				continue;
			}

			if (x >= 6)
				(*inShader).setVec3("colour", glm::vec3(0.5f, 0.5f, 1.0f));
			if (x >= 12)
				(*inShader).setVec3("colour", glm::vec3(0.8f, 0.2f, 0.3f));
			if (x >= 18)
				(*inShader).setVec3("colour", glm::vec3(0.2f, 0.9f, 0.5f));
			// move unit cube relative to parent base position and pass the model matrix to the vertex shader
			glm::mat4 model = transform->GetModel(parentTransform->GetModel());
			model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
			model = glm::translate(model, glm::vec3((float)x, (float)y, 0.0f) + glm::vec3((0.3f + (-columns * 0.5)), 0.0f, 0.0f));
			(*inShader).setMat4("model", model);

			// render the cube
			glDrawArrays(renderMode, 0, 36);
		}
	}
}

// void Number::draw(Shader& inShader)
// {
//
// 	inShader.use();
// 	inShader.setBool("isTextured", false);
// 	inShader.setVec3("colour", glm::vec3(1.0f, 0.5f, 0.3f));
// 	glBindVertexArray(unitCube.getVAO());
//
// 	// compute world position of child cubes
// 	for (int r = 0; r < rows; r++) {
// 		for (int c = 0; c < columns; c++) {
// 				if (modelData[r][c] == NONE) {
// 					continue;
// 				}
//
//
// 				// move unit cube relative to parent base position and pass the model matrix to the vertex shader
// 				inShader.setMat4("model", glm::translate(transform->GetModel(parentTransform->GetModel()), glm::vec3((float)c, (float)r, 0.0f) + glm::vec3((0.3f + (-columns * 0.5)), 0.0f, 0.0f)));
//
// 				// render the cube
// 				glDrawArrays(renderMode, 0, 36);
// 		}
// 	}
// }
