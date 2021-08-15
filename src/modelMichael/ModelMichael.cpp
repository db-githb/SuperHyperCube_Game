#include "ModelMichael.h"

ModelMichael::ModelMichael(Shader& inShader) : ModelBase(inShader) {

	rows = 9;
	columns = 7;
	planes = 7;

	allocateWallData();
	allocateObjectData();
	generateOriginalObject();

}

void ModelMichael::generateOriginalObject()
{
	// initialize entire model to a wall or none (no unit cube)

	// reset unitCubes in the model to their respective colors
	resetUnitCubes();
}

void ModelMichael::generateRandomModel() 
{
	resetModel();
	//Generate a random number of cubes
	int numCubes = rand() % 25 + 3;
	for (int i = 0; i < numCubes; i++)
	{
		generateCube(rand() % 7 + 1, rand() % 7 + 1, rand() % 5 + 1, rand() % 5 + 1, rand() % 5 + 1, rand() % 5 + 1, rand() % 2 + 1);
	}
}

void ModelMichael::resetModel()
{
	for (int r = 0; r < rows; r++) {
		for (int c = 0; c < columns; c++) {
			for (int p = 0; p < planes; p++)
				if (p == 0) {
					wall.modelData[r][c][p] = WALL;
				}
				else {
					object.modelData[r][c][p] = NONE;
				}
		}
	}
}

void ModelMichael::generateCube(int rowStart, int rowEnd, int columnStart, int columnEnd, int planeStart, int planeEnd, int color)
{
	//Validating cube values
	if (!((rowStart > rowEnd) || (columnStart > columnEnd) || (planeStart > planeEnd))) {
		for (int c = columnStart; c < columnEnd+1; c++) {
			for (int r = rowStart; r < rowEnd+1; r++) {
				for (int p = planeStart; p < planeEnd+1; p++) {
					object.modelData[r][c][planes - p] = color;
				}
				//Make hole
				wall.modelData[r][c][0] = NONE;
			}
		}
	}
}

void ModelMichael::resetUnitCubes()
{
	generateCube(5, 7, 1, 2, 3, 4, RED);
	generateCube(2, 2, 1, 5, 2, 2, BLUE);
	generateCube(3, 3, 4, 4, 2, 3, RED);
	generateCube(4, 5, 3, 3, 1, 1, BLUE);
}