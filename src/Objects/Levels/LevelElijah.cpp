#include "LevelElijah.h"

LevelElijah::LevelElijah(Shader& inShader): Level(inShader)
{
	generateObject();
	generateWall();
}

void LevelElijah::generateObject()
{
	clearObjectModel();
	for (int z = 1; z < 4; z++)
	{
		for (int x = 1; x < sizeX - 1; x++)
		{
			// E
			objectData[x][1][z] = PINK;
			objectData[z][2][z] = MINT;
			objectData[z][5][z] = MINT;
			objectData[x][7][z] = CYAN;

		}
		for (int y = 1; y < sizeY - 1; y++)
		{
			// E
			objectData[z][y][3] = VIOLET;

		}
	}


	//transfer object data to ObjectNode child "object"
	for (int x = 1; x < sizeX - 1; x++)
	{
		for (int y = 1; y < sizeY - 1; y++)
		{
			for (int z = 0; z < sizeZ; z++)
				object->m_model->cubes[x][y][z] = objectData[x][y][z];
		}
	}
}
