#include "ModelElijah.h"

ModelElijah::ModelElijah(Shader& inShader) : ModelBase(inShader)
{

	transform.position = glm::vec3(-5.0f, 0.5f, -5.0f);

	rows = COLUMNS;
	columns = ROWS;
	planes = PLANES;

	allocateWallData();
	allocateObjectData();

	generateOriginalObject();
}

void ModelElijah::generateRandomModel()
{
	// initialize entire model to a wall or none (no unit cube)
	for (int x = 0; x < ROWS; x++)
	{
		for (int y = 0; y < COLUMNS; y++)
		{
			for (int z = 0; z < PLANES; z++)
			{
				if (z == 0)
				{
					wall.modelData[y][x][z] = WALL;
				}
				else
				{
					object.modelData[y][x][z] = NONE;
				}
			}
		}
	}

	// Create random model
	for (int x = 1; x < ROWS - 1; x++)
	{
		for (int y = 1; y < COLUMNS - 1; y++)
		{
			for (int z = 2; z < PLANES; z++)
			{
				if (rand() % 100 > 80 && z != 0)
				{
					if (rand() % 100 > 50)
						object.modelData[y][x][z] = RED;
					else
						object.modelData[y][x][z] = BLUE;
					
					wall.modelData[y][x][0] = NONE;
				}
			}
		}
	}

}

void ModelElijah::generateOriginalObject()
{

	for (int y = 1; y < COLUMNS - 1; y++)
	{
		for (int x = 1; x < ROWS - 1; x++)
		{
			for (int z = 2; z < PLANES; z++)
			{
				if (y == 1) {
					object.modelData[y][3][PLANES - 3] = BLUE;
					object.modelData[y][3][PLANES - 2] = BLUE;
					object.modelData[y][3][PLANES - 1] = BLUE;
					wall.modelData[y][3][0] = NONE;
				}

				if (y == COLUMNS - 3)
				{
					object.modelData[y][x][1] = RED;
					wall.modelData[y][x][0] = NONE;
				}
				if (y == 2 && x < 2)
				{
					object.modelData[y][x][z] = RED;
					wall.modelData[y][x][0] = NONE;
				}
				if ((y == 3 || y == COLUMNS - 4) && (x >= 3 && x <= ROWS - 4))
				{
					object.modelData[y][x][z] = RED;
					wall.modelData[y][x][0] = NONE;
				}
				if ((y == 4 || y == COLUMNS - 5))
				{
					object.modelData[y][x][z] = BLUE;
					wall.modelData[y][x][0] = NONE;
				}
			}
		}	
	}
	
	
}