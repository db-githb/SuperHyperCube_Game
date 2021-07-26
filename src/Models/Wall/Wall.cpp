#include "Wall.h"

Wall::Wall()
{
	transform = Transform();
	/*transform.SetPosition(glm::vec3(0,0,0));
	transform.SetRotation(glm::vec3(0,0,0));
	transform.SetScale(glm::vec3(1.0f,1.0f,1.0f));*/

	generateWall();
}

void Wall::Draw(Shader& shader)
{
	// Set the world position of the model
	transform.SetPosition(glm::vec3(xTranslation * scaleFactor, yTranslation * scaleFactor + 0.5f, -7.0f));

	// activate the shader
	shader.use();

	// world transformation: glm::translate moves the model around the world
	for (int c = 0; c < sizeX; c++)
	{
		for (int r = 0; r < sizeY; r++)
		{
			
				if (wall[c][r] == NONE)
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

				if (wall[c][r] == WALL)
					shader.setVec3("dirLight.ambient", glm::vec3(0.5f *  (c%7)/7.0f, 0.5f, 0.5f)); // shader colors the wall unit cube grey
				else
				{
					// if-else statement colors the object cubes either red or blue
					if (wall[c][r] == RED)
					{
						shader.setVec3("dirLight.ambient", glm::vec3(0.9f, 0.7f, 0.5f));
					}
					else
					{
						shader.setVec3("dirLight.ambient", glm::vec3(0.5f, 0.1f, 0.5f));
					}
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



void Wall::generateWall()
{
	// Set all walls to solid
	for (int x = 0; x < sizeX; x++)
	{
		for (int y = 0; y < sizeY; y++)
		{
			wall[x][y] = WALL;
		}
	}

	//Horizontal lines in E and A and Bottom row L J
	for (int x = 0; x < 5; x++)
	{
		// E
		wall[x+1][1] = NONE;
		wall[x+1][4] = NONE;
		wall[x+1][7] = NONE;
		// L
		wall[x+8][1] = NONE;
		// J
		wall[x+22][1] = NONE;
		// A
		wall[x+29][4] = NONE;
		wall[x+29][7] = NONE;
	}
	// Vertical lines in E,L,I,J,A
	for (int y = 1; y < 8; y++)
	{
		// E
		wall[1][y] = NONE;
		// L
		wall[8][y] = NONE;
		// I
		wall[17][y] = NONE;
		// J
		wall[26][y] = NONE;
		// A
		wall[29][y] = NONE;
		wall[33][y] = NONE;
		
	}
	// Serifs in J
	wall[25][7] = NONE;
	wall[22][2] = NONE;
}