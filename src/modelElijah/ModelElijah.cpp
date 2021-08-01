#include "ModelElijah.h"

ModelElijah::ModelElijah(Shader& inShader) : ModelBase(inShader)
{

	transform.position = glm::vec3(-5.0f, 0.5f, -5.0f);

	modelBasePosition = glm::vec3(-15.0f, 0.5f, -15.0f);

	rows = 7;
	columns = 9;
	planes = 7;

	allocateShaderData();

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
					wall.modelData[x][y][z] = WALL;
				}
				else
				{
					object.modelData[x][y][z] = NONE;
				}
			}
		}
	}

	// Create random model
	for (int y = 1; y < ROWS - 1; y++)
	{
		for (int x = 1; x < COLUMNS - 1; x++)
		{
			for (int z = 2; z < PLANES; z++)
			{
				if (rand() % 100 > 80 && z != 0)
				{
					if (rand() % 100 > 50)
						object.modelData[x][y][z] = RED;
					else
						object.modelData[x][y][z] = BLUE;
					
						wall.modelData[x][y][0] = NONE;
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
				if (y == 1 || y == COLUMNS - 2)
				{
					object.modelData[x][y][z] = BLUE;
					wall.modelData[x][y][0] = NONE;
				}
				if ((y == 2 || y == COLUMNS - 3) && (x >=2 && x <= ROWS - 3))
				{
					object.modelData[x][y][z] = BLUE;
					wall.modelData[x][y][0] = NONE;
				}
				if ((y == 3 || y == COLUMNS - 4) && (x >= 3 && x <= ROWS - 4))
				{
					object.modelData[x][y][z] = BLUE;
					wall.modelData[x][y][0] = NONE;
				}
				if ((y == 4 || y == COLUMNS - 5))
				{
					object.modelData[x][y][z] = BLUE;
					wall.modelData[x][y][0] = NONE;
				}

			}
		}	
	}
	
	for (int y = 1; y < COLUMNS - 1; y++)
	{
		for (int x = 1; x < ROWS - 1; x++)
		{
			for (int z = 2; z < PLANES; z++)
			{
				if ((x == 1 || x == ROWS - 2) && z != 4)
					object.modelData[x][y][z] = NONE;
				if ((x == 2 || x == ROWS - 3) && (z == 2 || z == 6))
					object.modelData[x][y][z] = NONE;

			}
		}
	}
	
	for (int y = 1; y < COLUMNS - 1; y++)
	{
		for (int x = 1; x < ROWS - 1; x++)
		{
			for (int z = 2; z < PLANES; z++)
			{
				if((y == 2 || y == 6) && (z == 2 || z == 6))
					object.modelData[x][y][z] = NONE;
				if ((y == 3 || y == 5) && (z == 2 || z == 3 || z == 5 || z == 6))
					object.modelData[x][y][z] = NONE;
				if ((y == 2 || y == 6) && (x == 2 || x == 4) && (z==3 || z==5))
					object.modelData[x][y][z] = NONE;
			}
		}
	}
	
	for (int y = 1; y < COLUMNS - 1; y++)
	{
		for (int x = 1; x < ROWS - 1; x++)
		{
			for (int z = 2; z < PLANES; z++)
			{
				if (modelData[x][y][z] == BLUE && y % 2 == 0)
				{
					object.modelData[x][y][z] = RED;
					wall.modelData[x][y][0] = NONE;
				}
			}
		}
	}
}