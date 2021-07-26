#include "Letter.h"

Letter::Letter()
{
	transform = Transform();
	/*transform.SetPosition(glm::vec3(0,0,0));
	transform.SetRotation(glm::vec3(0,0,0));
	transform.SetScale(glm::vec3(1.0f,1.0f,1.0f));*/
	GenerateLetter();

}

void Letter::Draw(Shader& shader)
{
	// Set the world position of the model
	transform.SetPosition(glm::vec3(xTranslation * scaleFactor, yTranslation * scaleFactor + 0.5f, zTranslation * scaleFactor) + initialPosition);

	// activate the shader
	shader.use();

	// world transformation: glm::translate moves the model around the world
	for (int c = 0; c < sizeX; c++)
	{
		for (int r = 0; r < sizeY; r++)
		{
			
				if (letter[c][r] == NONE)
				{
					continue;
				}

				// scale position of each unitCube
				float x = (float)c * scaleFactor;
				float y = (float)r * scaleFactor;
				float z = 0.0f;//(float)p * scaleFactor;

				// The XYZ coordinate vector of a given cube relative to the model's root/origin
				glm::vec3 translation = glm::vec3(x, y, z);
				//transform.matrix = glm::scale(transform.matrix, glm::vec3(1.0f) * scaleFactor);
				// Set the model's origin relative to the scene origin
				glm::mat4 model = glm::mat4(1.0f);
				// Apply rotation to a given unit cube relative to the whole model's origin
				model = glm::rotate(transform.GetModel(), orientation, glm::vec3(0.0f, 1.0f, 0.0f));

				switch (colorMode) {
				case ColorMode::col1:
					shader.setVec3("dirLight.ambient", glm::vec3(0.9f, 0.7f, 0.5f));
					break;
				case ColorMode::col2:
					shader.setVec3("dirLight.ambient", glm::vec3(0.5f, 0.7f, 1.0f));
					break;
				case ColorMode::col3:
					shader.setVec3("dirLight.ambient", glm::vec3(0.2f, 0.2f, 0.1f));
					break;
				case ColorMode::col4:
					shader.setVec3("dirLight.ambient", glm::vec3(0.7f, 1.0f, 0.5f));
					break;
				case ColorMode::col5:
					shader.setVec3("dirLight.ambient", glm::vec3(0.3f, 0.3f, 0.8f));
					break;

				}

				// translation vector to move unit cube from base position
				model = glm::translate(model, translation + glm::vec3(scaleFactor * (-sizeX / 2), 0.0f, scaleFactor * (-sizeZ / 2)));

				// Scale the size of each cube uniformly
				model = glm::scale(model, glm::vec3(1.0f) * scaleFactor);


				// pass the model matrix to the vertex shader
				shader.setMat4("model", model);

				// render the cube
				glBindVertexArray(unitCube.getVAO());
				glDrawArrays(renderMode, 0, 36);

				glBindVertexArray(unitCube.getVAO());
				/*baseShader.setMat4("model", transform.matrix);
				baseShader.setVec3("dirLight.ambient", glm::vec3(1.0f, 1.0f, 1.0f));
				glDrawArrays(renderMode, 0, 36);*/


		}
	}
}



void Letter::GenerateLetter()
{
	//Set all walls to solid
	for (int x = 0; x < sizeX; x++)
	{
		for (int y = 0; y < sizeY; y++)
		{
		letter[x][y] = NONE;
		}
	}

	//Horizontal lines in E and A and Bottom row L J
	//for (int x = 0; x < 5; x++)
	//{
	//	// L
	//	letter[x+8][1] = RED;
	//	// J
	//	letter[x+22][1] = RED;
	//	// A
	//	letter[x+29][4] = RED;
	//	letter[x+29][7] = RED;
	//}
	//// Vertical lines in E,L,I,J,A
	//for (int y = 1; y < 8; y++)
	//{
	//	// L
	//	letter[8][y] = RED;
	//	// I
	//	letter[17][y] = RED;
	//	// J
	//	letter[26][y] = RED;
	//	// A
	//	letter[29][y] = RED;
	//	letter[33][y] = RED;
	//	
	//}
	//// Serifs in J
	//letter[4][7] = RED;
	//letter[1][2] = RED;
}

void Letter::GenerateE()
{
	initialPosition = glm::vec3(-7.0f, 0, -6.0f);
	colorMode = ColorMode::col1;
	for (int x = 0; x < 5; x++)
	{
		// E
		letter[x + 1][1] = RED;
		letter[x + 1][4] = RED;
		letter[x + 1][7] = RED;
		
	}
	for (int y = 1; y < 8; y++)
	{
		// E
		letter[1][y] = RED;

	}
}

void Letter::GenerateL()
{
	initialPosition = glm::vec3(-3.5f, 0, -6.0f);
	colorMode = ColorMode::col2;
	//Horizontal lines in E and A and Bottom row L J
	for (int x = 0; x < 5; x++)
	{
		// L
		letter[x+1][1] = RED;

	}
	// Vertical lines in E,L,I,J,A
	for (int y = 1; y < 8; y++)
	{
		// L
		letter[1][y] = RED;
	}
}

void Letter::GenerateI()
{
	initialPosition = glm::vec3(0.0f, 0, -6.0f);
	colorMode = ColorMode::col3;

	// Vertical lines in I
	for (int y = 1; y < 8; y++)
	{
		// I
		letter[3][y] = RED;
		
	}
}

void Letter::GenerateJ()
{
	initialPosition = glm::vec3(3.5f, 0, -6.0f);
	colorMode = ColorMode::col4;
	//Horizontal lines in J
	for (int x = 0; x < 5; x++)
	{

		// J
		letter[x+1][1] = RED;

	}
	// Vertical lines in J
	for (int y = 1; y < 8; y++)
	{

		// J
		letter[5][y] = RED;

		
	}
	// Serifs in J
	letter[4][7] = RED;
	letter[1][2] = RED;
}

void Letter::GenerateA()
{
	initialPosition = glm::vec3(7.0f, 0, -6.0f);
	colorMode = ColorMode::col5;
	for (int x = 0; x < 5; x++)
	{
		// A
		letter[x+1][4] = RED;
		letter[x+1][7] = RED;
	}
	// Vertical lines in E,L,I,J,A
	for (int y = 1; y < 8; y++)
	{
		// A
		letter[1][y] = RED;
		letter[5][y] = RED;
		
	}
}
