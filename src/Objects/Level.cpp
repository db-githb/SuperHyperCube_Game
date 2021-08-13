#include "Level.h"

Level::Level(Shader& inShader)
{
	
	object = new ObjectNode(new Model(inShader));
	wall   = new ObjectNode(new Model(inShader));
	AddChild(object);
	AddChild(wall);
	generateWall();
	generateObject();
	
}

Level::Level(int*** objectPositions, int*** wallPositions)
{
}

void Level::Update(float ms)
{
}

void Level::RotateObject(int direction)
{
}

bool Level::ValidateOrientation()
{
	if (object->transform.GetForwardVector() == wall->transform.GetForwardVector())
	{
		std::cout << "forward vectors match";
		return true;
	}
	else
	{
		std::cout << "forward do not vectors match";
		return false;
	}
}

void Level::generateObject()
{
	for (int z = 1; z < 4; z++)
	{
		for (int x = 0; x < sizeX; x++)
		{
			// E
			objectData[x + 1][1][z] = RED;
			objectData[x + 1][4][z] = RED;
			objectData[x + 1][7][z] = RED;

		}
		for (int y = 1; y < sizeY; y++)
		{
			// E
			objectData[1][y][z] = RED;

		}
	}

	for (int x = 0; x < sizeX; x++)
	{
		for (int y = 0; y < sizeY; y++)
		{
			for (int z = 0; z < sizeZ; z++)
				object->m_model->cubePositions[x][y][z] = objectData[x][y][z];
		}
	}
}

void Level::generateWall()
{
	// Set all walls to solid
	for (int x = 0; x < sizeX; x++)
	{
		for (int y = 0; y < sizeY; y++)
		{
			wallData[x][y][0] = WALL;
		}
	}

	for (int x = 0; x < sizeX; x++)
	{
		for (int y = 0; y < sizeY; y++)
		{
			wall->m_model->cubePositions[x][y][0] = wallData[x][y][0];
		}
	}
	

}