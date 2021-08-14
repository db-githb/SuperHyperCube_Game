#include "Level.h"

Level::Level(Shader& inShader)
{
	
	object = new ObjectNode(new Model(inShader));
	wall   = new ObjectNode(new Model(inShader));
	AddChild(object);
	object->AddPosition(glm::vec3(0, 0, 20));
	AddChild(wall);
	//Generate object first, wall second, so that the wall generation function can identify the correct "cutout" for the object
	generateObject();
	generateWall();
	
	
}

Level::Level(int*** objectPositions, int*** wallPositions)
{
}

void Level::Update(float ms)
{

	object->AddPosition(glm::vec3(0, 0, -4 * ms));
	
}

void Level::RotateObject(int direction)
{
}

bool Level::ValidateOrientation()
{
	if (object->transform.GetForwardVector() == wall->transform.GetForwardVector())
	{
		std::cout << "\n forward vectors match";
		return true;
	}
	else
	{
		std::cout << "\n forward do not vectors match";
		return false;
	}
}

void Level::generateObject()
{
	clearObjectModel();
	for (int z = 1; z < 4; z++)
	{
		for (int x = 1; x < sizeX-1; x++)
		{
			// E
			objectData[x][1][z] = RED;
			objectData[x][4][z] = ORANGE;
			objectData[x][7][z] = BLUE;

		}
		for (int y = 1; y < sizeY-1; y++)
		{
			// E
			objectData[6][y][3] = GREEN;

		}
	}


	//transfer object data to ObjectNode child "object"
	for (int x = 1; x < sizeX-1; x++)
	{
		for (int y = 1; y < sizeY-1; y++)
		{
			for (int z = 0; z < sizeZ; z++)
				object->m_model->cubePositions[x][y][z] = objectData[x][y][z];
		}
	}
}

void Level::generateWall()
{
	clearWallModel();
	// Set all walls to solid
	for (int x = 0; x < sizeX; x++)
	{
		for (int y = 0; y < sizeY; y++)
		{
			wallData[x][y][0] = WALL;
		}
	}



	//transfer wall data to ObjectNode child "wall"
	for (int x = 0; x < sizeX; x++)
	{
		for (int y = 0; y < sizeY; y++)
		{
			wall->m_model->cubePositions[x][y][0] = wallData[x][y][0];
		}
	}
	

}

void Level::clearObjectModel()
{
	for (int x = 0; x < sizeX; x++)
	{
		for (int y = 0; y < sizeY; y++)
		{
			for (int z = 0; z < sizeZ; z++)
			objectData[x][y][z] = NONE;
		}
	}
	
	object->m_model->resetObject();
}

void Level::clearWallModel()
{

	for (int x = 0; x < sizeX; x++)
	{
		for (int y = 0; y < sizeY; y++)
		{
			for (int z = 0; z < sizeZ; z++)
				wallData[x][y][z] = NONE;
		}
	}
	wall->m_model->resetObject();
}
