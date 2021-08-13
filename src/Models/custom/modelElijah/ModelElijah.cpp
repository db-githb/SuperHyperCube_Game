#include "ModelElijah.h"

ModelElijah::ModelElijah(Shader& inShader) : Model(inShader)
{

	modelBasePosition = glm::vec3(0.0f, 0.5f, 0.0f);

	rows = 9;
	columns = 7;
	planes = 7;

	//allocateWallData();
	//allocateObjectData();

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
					data.cubePositions[y][x][z] = WALL;
				}
				else
				{
					data.cubePositions[y][x][z] = NONE;
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
						data.cubePositions[y][x][z] = RED;
					else
						data.cubePositions[y][x][z] = BLUE;
					
					data.cubePositions[y][x][0] = NONE;
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
					data.cubePositions[y][x][z] = BLUE;
					data.cubePositions[y][x][0] = NONE;
				}
				if ((y == 2 || y == COLUMNS - 3) && (x >=2 && x <= ROWS - 3))
				{
					data.cubePositions[y][x][z] = BLUE;
					data.cubePositions[y][x][0] = NONE;
				}
				if ((y == 3 || y == COLUMNS - 4) && (x >= 3 && x <= ROWS - 4))
				{
					data.cubePositions[y][x][z] = BLUE;
					data.cubePositions[y][x][0] = NONE;
				}
				if ((y == 4 || y == COLUMNS - 5))
				{
					data.cubePositions[y][x][z] = BLUE;
					data.cubePositions[y][x][0] = NONE;
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
					data.cubePositions[y][x][z] = NONE;
				if ((x == 2 || x == ROWS - 3) && (z == 2 || z == 6))
					data.cubePositions[y][x][z] = NONE;

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
					data.cubePositions[y][x][z] = NONE;
				if ((y == 3 || y == 5) && (z == 2 || z == 3 || z == 5 || z == 6))
					data.cubePositions[y][x][z] = NONE;
				if ((y == 2 || y == 6) && (x == 2 || x == 4) && (z==3 || z==5))
					data.cubePositions[y][x][z] = NONE;
			}
		}
	}
	
	for (int y = 1; y < COLUMNS - 1; y++)
	{
		for (int x = 1; x < ROWS - 1; x++)
		{
			for (int z = 2; z < PLANES; z++)
			{
				if (modelData[y][x][z] == BLUE && y % 2 == 0)
				{
					data.cubePositions[y][x][z] = RED;
					data.cubePositions[y][x][0] = NONE;
				}
			}
		}
	}
}