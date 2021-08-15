#include "LevelThomas.h"

LevelThomas::LevelThomas(Shader& inShader) : Level(inShader) 
{
	generateObject();
	generateWall();
}

void LevelThomas::generateObject()
{
	clearObjectModel();

	for (int r = 2; r < 8; r++) {
		objectData[r][1][4] = YELLOW;
	}

	for (int c = 1; c < 6; c++) {
		objectData[1][c][4] = YELLOW;
	}

	for (int r = 2; r < 8; r++) {
		objectData[r][1][5] = YELLOW;
	}

	for (int c = 1; c < 6; c++) {
		objectData[1][c][5] = YELLOW;
	}

	for (int c = 1; c < 5; c++) {
		objectData[7][c][4] = YELLOW;
	}

	for (int c = 1; c < 5; c++) {
		objectData[7][c][5] = YELLOW;
	}

	for (int p = 3; p < 7; p++) {
		objectData[2][2][p] = ORANGE;
	}

	for (int p = 3; p < 7; p++) {
		objectData[5][2][p] = ORANGE;
	}

	for (int r = 2; r < 6; r++) {
		objectData[r][1][6] = ORANGE;
	}

	//transfer object data to ObjectNode child "object"
	for (int x = 1; x < sizeX - 1; x++)
	{
		for (int y = 1; y < sizeY - 1; y++) 
		{
			for (int z = 0; z < sizeZ; z++) {
				object->m_model->cubePositions[x][y][z] = objectData[x][y][z];
			}
		}
	}

}