#include "ModelElijah.h"

     ModelElijah::ModelElijah()
	{
		transform.position = glm::vec3(-5.0f, 0.5f, -5.0f);
	}

void ModelElijah::initialize() {

	modelBasePosition = glm::vec3(-5.0f, 0.5f, -5.0f);

	generateOriginalObject();

}

void ModelElijah::generateRandomModel()
{
	// initialize entire model to a wall or none (no unit cube)
	for (int x = 0; x < sizeX; x++)
	{
		for (int y = 0; y < sizeY; y++)
		{
			for (int z = 0; z < sizeZ; z++)
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
	for (int y = 1; y < sizeY - 1; y++)
	{
		for (int x = 1; x < sizeX - 1; x++)
		{
			for (int z = 2; z < sizeZ; z++)
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
// initialize entire model to a wall or none (no unit cube)
	for (int x = 0; x < sizeX; x++) 
	{
		for (int y = 0; y < sizeY; y++) 
		{
			for (int z = 0; z < sizeZ; z++)
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

	for (int y = 1; y < sizeY - 1; y++)
	{
		for (int x = 1; x < sizeX - 1; x++)
		{
			for (int z = 2; z < sizeZ; z++)
			{
				if (y == 1 || y == sizeY - 2)
				{
					object.modelData[x][y][z] = BLUE;
					wall.modelData[x][y][0] = NONE;
				}
				if ((y == 2 || y == sizeY - 3) && (x >=2 && x <= sizeX - 3))
				{
					object.modelData[x][y][z] = BLUE;
					wall.modelData[x][y][0] = NONE;
				}
				if ((y == 3 || y == sizeY - 4) && (x >= 3 && x <= sizeX - 4))
				{
					object.modelData[x][y][z] = BLUE;
					wall.modelData[x][y][0] = NONE;
				}
				if ((y == 4 || y == sizeY - 5))
				{
					object.modelData[x][y][z] = BLUE;
					wall.modelData[x][y][0] = NONE;
				}

			}
		}	
	}

	for (int y = 1; y < sizeY - 1; y++)
	{
		for (int x = 1; x < sizeX - 1; x++)
		{
			for (int z = 2; z < sizeZ; z++)
			{
				if ((x == 1 || x == sizeX - 2) && z != 4)
					modelData[x][y][z] = NONE;
				if ((x == 2 || x == sizeX - 3) && (z == 2 || z == 6))
					modelData[x][y][z] = NONE;

			}
		}
	}
	
	for (int y = 1; y < sizeY - 1; y++)
	{
		for (int x = 1; x < sizeX - 1; x++)
		{
			for (int z = 2; z < sizeZ; z++)
			{
				if((y == 2 || y == 6) && (z == 2 || z == 6))
					modelData[x][y][z] = NONE;
				if ((y == 3 || y == 5) && (z == 2 || z == 3 || z == 5 || z == 6))
					modelData[x][y][z] = NONE;
				if ((y == 2 || y == 6) && (x == 2 || x == 4) && (z==3 || z==5))
					modelData[x][y][z] = NONE;
			}
		}
	}

	for (int y = 1; y < sizeY - 1; y++)
	{
		for (int x = 1; x < sizeX - 1; x++)
		{
			for (int z = 2; z < sizeZ; z++)
			{
				if (modelData[x][y][z] == BLUE && y % 2 == 0)
				{
					modelData[x][y][z] = RED;
					modelData[x][y][0] = NONE;
				}
			}
		}
	}
}