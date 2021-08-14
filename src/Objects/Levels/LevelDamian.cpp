#include "LevelDamian.h"

LevelDamian::LevelDamian(Shader& inShader): Level(inShader)
{
	generateObject();
	generateWall();
}

void LevelDamian::generateObject()
{
	clearObjectModel();

	for (int x = 2; x < 7; x++) {
		objectData[x][4][sizeZ-2] = BLUE;
	}
	
	for (int c = 2; c < 7; c++) {

		if (c != 4) {
			objectData[2][c][sizeZ - 2] = BLUE;
			objectData[6][c][sizeZ - 2] = BLUE;
		}

		if (c == 2) {
			objectData[6][c][sizeZ -3] = RED;
			objectData[6][c][sizeZ -2] = RED;

			objectData[2][c][sizeZ -2] = RED;
			objectData[2][c][sizeZ -1] = RED;
		}

		if (c == 6) {
			objectData[6][c][sizeZ -1] = RED;
			objectData[6][c][sizeZ -2] = RED;

			objectData[2][c][sizeZ -2] = RED;
			objectData[2][c][sizeZ -3] = RED;
		}

		if (c == 3 || c == 5) {
			objectData[4][c][sizeZ -2] = BLUE;

			if (c == 3) {
				objectData[4][c][sizeZ -2] = BLUE;
				objectData[4][c][sizeZ -1] = GREEN;
			}

			if (c == 5) {
				objectData[4][c][sizeZ -3] = GREEN;
				objectData[4][c][sizeZ -2] = BLUE;
			}
		}
	
	}

	//transfer object data to ObjectNode child "object"
	for (int x = 1; x < sizeX - 1; x++)
	{
		for (int y = 1; y < sizeY - 1; y++)
		{
			for (int z = 0; z < sizeZ; z++)
				object->m_model->cubePositions[x][y][z] = objectData[x][y][z];
		}
	}
}
